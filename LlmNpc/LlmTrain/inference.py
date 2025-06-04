import torch
from transformers import AutoTokenizer, AutoModelForCausalLM, BitsAndBytesConfig
from llm_summarization.supervised_fine_tuning import get_instruction_prompt 
from peft import PeftModel

# ── A) 베이스 모델이 quantization(4bit/8bit)으로 학습되었다면, 동일하게 로드
bnb_config = BitsAndBytesConfig(
    load_in_4bit=True,
    bnb_4bit_quant_type="nf4",
    bnb_4bit_compute_dtype=torch.bfloat16,
    bnb_4bit_use_double_quant=True,
    bnb_4bit_quant_storage=torch.bfloat16,
)
model_name = "EleutherAI/polyglot-ko-5.8b"

model = AutoModelForCausalLM.from_pretrained(
    model_name,
    quantization_config=bnb_config,
    device_map={'': f'cuda:{0}'}
)
model = PeftModel.from_pretrained(model, "distributed_output/checkpoint-7400")
original_model = AutoModelForCausalLM.from_pretrained(
    'beomi/KoAlpaca-Polyglot-5.8B',
    quantization_config=bnb_config,
    device_map={'': f'cuda:{0}'}
)


tokenizer = AutoTokenizer.from_pretrained(model_name)

prompt = f"### 명령어: {get_instruction_prompt()}\n\n###맥락: 뒤로 빼야 돼\n\n### 답변: "  

inputs = tokenizer(
    prompt,
    return_tensors="pt",
    padding=False,
    truncation=True,
    return_token_type_ids=False
).to(model.device)


outputs = model.generate(
    **inputs,
    max_new_tokens=64,
    do_sample=False,
    eos_token_id=2,
    output_scores=True,
    return_dict_in_generate=True,
    early_stopping=True
)

generated_ids = outputs.sequences
generated_text = tokenizer.decode(generated_ids[0], skip_special_tokens=True)
print(f"\nGenerated ID sequence: {generated_ids[0].tolist()}")
print(f"Generated text: {generated_text}")

eos_string = "<|endoftext|>"
eos_token_id_from_string = tokenizer.encode(eos_string, add_special_tokens=False)
print(f"'{eos_string}' is tokenized to: {eos_token_id_from_string}")
print(f"Tokenizer's eos_token_id: {tokenizer.eos_token_id}")

sample_completion = '뒤로 이동<|endoftext|>'
tokenized_completion = tokenizer.encode(sample_completion, add_special_tokens=False)
print(f"'{sample_completion}' is tokenized to {len(tokenized_completion)} tokens: {tokenized_completion}")

for comp in tokenized_completion:
    print(tokenizer.decode(comp))



eos_token_id = 2
target_step_for_second_token_being_eos = 3 # 두 번째 생성 토큰 (인덱스 1)

if len(outputs.scores) > target_step_for_second_token_being_eos:
    logits_for_second_token = outputs.scores[target_step_for_second_token_being_eos][0] # batch_size 0 선택
    probabilities_for_second_token = torch.softmax(logits_for_second_token, dim=-1)
    eos_prob_at_second_token = probabilities_for_second_token[eos_token_id].item()
    print(f"\n--- [경우 1] 두 번째 생성 토큰이 EOS일 확률 ---")
    print(f"두 번째 생성 토큰 위치의 EOS (ID: {eos_token_id}) 확률: {eos_prob_at_second_token:.4f}")

    # 해당 단계에서 가장 확률 높은 토큰들도 확인
    top_k_probs, top_k_indices = torch.topk(probabilities_for_second_token, k=5)
    print("Top 5 예상 토큰 (두 번째 생성 위치):")
    for i in range(top_k_indices.size(0)):
        token_id = top_k_indices[i].item()
        token_prob = top_k_probs[i].item()
        token_str = tokenizer.decode([token_id])
        print(f"  - 토큰: '{token_str}' (ID: {token_id}), 확률: {token_prob:.4f}")
else:
    print(f"\n[경우 1] 모델이 {target_step_for_second_token_being_eos + 1}개 미만의 토큰을 생성했습니다.")



output2 = original_model.generate(
    **inputs,
    max_new_tokens=64,
    do_sample=True,
    early_stopping=True,
    eos_token_id=2
)

generated = tokenizer.decode(output2[0], skip_special_tokens=True)
print(generated)


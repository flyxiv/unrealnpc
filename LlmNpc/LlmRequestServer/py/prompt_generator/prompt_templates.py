from py.util import get_resource_dir

prompt_dir = get_resource_dir() / 'prompts'
prompts = {}
with open(prompt_dir / 'TaskClassificationPrompt.txt', 'r', encoding='utf-8') as f:
    prompts['TaskClassificationPrompt'] = f.read()

with open(prompt_dir / 'ActionPrompt.txt', 'r', encoding='utf-8') as f:
    prompts['ActionPrompt'] = f.read()

with open(prompt_dir / 'DialoguePrompt.txt', 'r', encoding='utf-8') as f:
    prompts['DialoguePrompt'] = f.read()



from .util import get_resources_dir

def generate_response_prompt():
    with open(get_resources_dir() / 'ResponsePrompt.txt', 'r', encoding='utf-8') as f:
        full_prompt = f.readlines()

        system_prompt = full_prompt[0] 
        user_prompt = full_prompt[1:]

    return [{
        "role": "system",
        "content": system_prompt
    }, {
        "role": "user",
        "content": ''.join(user_prompt)
    }]

print (generate_response_prompt())
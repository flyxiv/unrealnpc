from py.util import get_resources_dir

def generate_action_prompt():
    with open(get_resources_dir() / 'ActionPrompt.txt', 'r', encoding='utf-8') as f:
        user_prompt = f.read() 

    return [{
        "role": "user",
        "content": user_prompt
    }]

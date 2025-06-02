import os
from flask import Flask, request, jsonify
from openai import OpenAI

app = Flask(__name__)

API_KEY = os.environ.get('OPENAI_API_KEY')
client = OpenAI(api_key=API_KEY)
model = "gpt-4.1-nano-2025-04-14"

@app.route('/llmrequest', methods=['POST'])
def llmrequest():
    prompt = request.get_json()['prompt']
    print(prompt)

    response = client.chat.completions.create(
        model=model,
        messages=[
            {"role": "user", "content": prompt}
        ]
    )

    llm_generated_text = response.choices[0].message.content

    response_to_client = {
        "Response": llm_generated_text
    }
    
    print(f"LLM Generated Text: {llm_generated_text}") # Flask 서버 로그에 출력
    return jsonify(response_to_client), 200

if __name__ == '__main__':  
   app.run('127.0.0.1',port=23456,debug=True)
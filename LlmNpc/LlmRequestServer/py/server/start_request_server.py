import logging
import uvicorn

from py.prompt_generator.prompt_templates import prompts

from fastapi import FastAPI

from py.langgraph.states import graph
from pydantic import BaseModel

HOST_URL = '0.0.0.0'
PORT = 23456
app = FastAPI()

class LLMRequest(BaseModel):
    text: str

@app.post('/api/v1/llmrequest')
async def llmrequest(request: LLMRequest):
    text = request.text
    task_prompt = prompts['TaskClassificationPrompt']
    task_prompt = task_prompt.replace('[UserInput]', text)

    for event in graph.stream({'messages': [{'role': 'user', 'content': task_prompt}]}):
        for value in event.values():
            print(value['messages'][-1].content)


if __name__ == '__main__':  
    logging.info(f"Starting LLM Request Server on port {PORT}")
    uvicorn.run("py.server.start_request_server:app", host=HOST_URL, port=PORT)
    logging.info(f"Loading action sLM")
import logging
import uvicorn


from fastapi import FastAPI

from py.langgraph.states import graph
from pydantic import BaseModel
from langchain_core.messages import HumanMessage

HOST_URL = '0.0.0.0'
PORT = 23456
app = FastAPI()

class LLMRequest(BaseModel):
    text: str

@app.post('/api/v1/llmrequest')
async def llmrequest(request: LLMRequest):
    for event in graph.stream({'messages': [HumanMessage(content=request.text)]}, stream_mode='values'):
        event['messages'][-1].pretty_print()

    return {
        'task': event['task'],
        'content': event['messages'][-1].content,
    }


if __name__ == '__main__':  
    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S"
    )

    logging.info(f"Starting LLM Request Server on port {PORT}")
    uvicorn.run("py.server.start_request_server:app", host=HOST_URL, port=PORT)
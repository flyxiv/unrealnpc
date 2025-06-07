import os
import getpass

from enum import Enum
from langchain.chat_models import init_chat_model

class LLMModel(Enum):
    GPT_4_1 = "openai:gpt-4.1"
    GPT_4_1_NANO = "openai:gpt-4.1-nano"
    GPT_O3_MINI = "openai:gpt-o3-mini"

if not (OPENAI_API_KEY := os.environ.get('OPENAI_API_KEY')):
    OPENAI_API_KEY = getpass.getpass("Enter your OpenAI API key: ")

print(f"loading model {LLMModel.GPT_4_1_NANO.value}")
LLM = init_chat_model(model=LLMModel.GPT_4_1_NANO.value, api_key = OPENAI_API_KEY)

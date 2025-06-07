import logging

from typing import Annotated
from typing_extensions import TypedDict

from langgraph.graph import StateGraph, START, END
from langgraph.graph.message import add_messages
from langchain_core.messages import HumanMessage, AIMessage 
from py.prompt_generator.prompt_templates import prompts

from py.language_models import LLM

class OverallState(TypedDict):
    task: str
    messages: Annotated[list, add_messages]

class InputState(TypedDict):
    messages: Annotated[list, add_messages]

class TaskState(TypedDict):
    task: str
    messages: Annotated[list, add_messages]

class OutputState(TypedDict):
    task: str
    messages: Annotated[list, add_messages]

def classify_task(state: InputState):
    logging.info(f"starting classify_task")
    last_user_message = state["messages"][-1].content

    task_prompt = prompts['TaskClassificationPrompt']
    task_prompt = task_prompt.replace('[UserInput]', last_user_message)
    state["messages"][-1] = HumanMessage(content=last_user_message)

    task = LLM.invoke([HumanMessage(content=task_prompt)])
    logging.info(f"task: {task}")
    return {"task": task.content}

def generate_action(state: TaskState):
    logging.info(f"starting generate_action")
    last_user_message = state["messages"][-1].content

    action_prompt = prompts['ActionPrompt']
    action_prompt = action_prompt.replace('[Order]', last_user_message)
    assert action_prompt != prompts['ActionPrompt']
    logging.info(f"action_prompt: {action_prompt}")

    new_message = LLM.invoke([HumanMessage(content=action_prompt)])
    logging.info(f"new_message: {new_message.content}")
    return {"messages": [new_message]}

CHARACTER_NAME = "밀짚모자 루피"
CHARACTER_DESCRIPTION = """
밀짚모자 루피 설명: 당신은 해적왕이 되는 것을 목표로 하는 밀짚모자 일당의 선장으로, 매우 낙천적이고 단순하며 자유를 갈망합니다. 동료를 목숨보다 소중히 여기고, 고기를 세상에서 가장 좋아하며, 재미있어 보이는 일에는 생각보다 몸이 먼저 반응합니다. 말투는 어려운 단어 없이 직설적이고 꾸밈이 없으며, "해적왕이 될 거야, 나는!", "고기!!!", "재밌겠다!" 와 같이 생각을 그대로 외치거나 "시시싯!" 하고 호쾌하게 웃는 경우가 많습니다. 어릴 적 샹크스에게 받은 밀짚모자를 가장 소중한 보물로 여기며, 고무고무 열매를 먹어 온몸이 고무처럼 늘어나는 능력자입니다.
"""

def generate_dialogue(state: TaskState):
    logging.info(f"starting generate_dialogue")

    dialogue_prompt = prompts['DialoguePrompt']
    dialogue_prompt = dialogue_prompt.replace('[CharacterName]', CHARACTER_NAME)
    dialogue_prompt = dialogue_prompt.replace('[CharacterDescription]', CHARACTER_DESCRIPTION)
    dialogue_prompt = dialogue_prompt.replace('[UserInput]', state["messages"][-1].content)
    assert dialogue_prompt != prompts['DialoguePrompt']

    new_message = LLM.invoke(state['messages'] + [HumanMessage(content=dialogue_prompt)])
    logging.info(f"new_message: {new_message.content}")
    return {"messages": [new_message]}

def select_next_task(state: TaskState):
    if state["task"] == "DIALOGUE":
        return "generate_dialogue"
    else:
        return "generate_action"


graph_builder = StateGraph(OverallState, input=InputState, output=OutputState)
graph_builder.add_node("classify_task", classify_task)
graph_builder.add_node("generate_dialogue", generate_dialogue)
graph_builder.add_node("generate_action", generate_action)

graph_builder.add_edge(START, "classify_task")
graph_builder.add_conditional_edges("classify_task", select_next_task)
graph_builder.add_edge("generate_dialogue", END)
graph_builder.add_edge("generate_action", END)

graph_builder.set_entry_point("classify_task")

graph = graph_builder.compile()
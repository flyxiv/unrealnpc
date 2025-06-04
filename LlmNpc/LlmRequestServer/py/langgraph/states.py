from typing import Annotated

from typing_extensions import TypedDict

from langgraph.graph import StateGraph, START
from langgraph.graph.message import add_messages

from py.language_models import LLM

class MessageState(TypedDict):
    messages: Annotated[list, add_messages]

def select_task(state: MessageState):
    return {"messages": [LLM.invoke(state["messages"])]}


graph_builder = StateGraph(MessageState)
graph_builder.add_node("select_task", select_task)
graph_builder.set_entry_point("select_task")

graph = graph_builder.compile()
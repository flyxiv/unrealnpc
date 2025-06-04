"""RAG Database for saving user conversation with NPC

This conversation history will be fetched by the Langchain Agent to generate NPC response 
that takes into account user's previous conversations.
"""

from langchain_community.vectorstores import FAISS
from langchain_community.vectorstores.utils import DistanceStrategy
from langchain_community.embeddings import HuggingFaceEmbeddings

device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')

embeddings_model = HuggingFaceEmbeddings(
    model_name='jhgan/ko-sbert-nli',
    model_kwargs={'device': device},
    encode_kwargs={'normalize_embeddings':True},
)

class ConversationHistoryRAG:
    def __init__(self, max_conversations: int = 100, k: int = 10):
        self.rag_db = FAISS.from_documents(
            documents=list(),
            embedding=embeddings_model,
        ) 

    def add_conversation(self, conversation: list[dict]):
        for conv in conversation:
            self.rag_db.add_documents([conv])

    def get_conversation(self, query: str):
        return self.rag_db.similarity_search(query)

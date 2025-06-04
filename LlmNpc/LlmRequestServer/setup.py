from setuptools import setup

requirements = [
    'faiss-gpu',
    'langchain[openai]',
    'fastapi',
    'langgraph',
    'uvicorn'
]

setup(
    name='LlmRequestServer',
    version='0.1',
    author='Jun Yeop Na',
    author_email='junyeopna4@gmail.com',
    description='',
    install_requires=requirements,
)
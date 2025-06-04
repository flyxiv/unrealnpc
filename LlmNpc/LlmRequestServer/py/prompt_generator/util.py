import os
from pathlib import Path

def get_resources_dir():
    return Path(os.getcwd(), 'resources')
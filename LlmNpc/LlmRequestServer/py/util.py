import os
from pathlib import Path

def get_resource_dir():
    return Path(os.getcwd()) / 'resources'

"""Test script for the LLM Request Server

Make sure to run start_request_server.py first.

Usage:
    python test_server.py <text>
"""

import argparse
import requests

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('text', type=str, default='Hello, world!')
    return parser.parse_args()

def main():
    args = parse_args()
    url = f'http://localhost:23456/api/v1/llmrequest'
    response = requests.post(url, json={'text': args.text})
    print(response.json())

if __name__ == '__main__':
    main()
import json
import os

filename = os.path.join("..", "expected", "005_simple.json")

with open(filename) as file:
    data = json.load(file)

print(len(data))


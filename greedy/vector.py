import json
import random as rn


data = []
for i in range(20):
    x = rn.uniform(-0.1,1)
    y = rn.uniform(x, 1.1)
    data.append((x,y))

with open("data_file.json", "w") as write_file:
    json.dump(data, write_file)


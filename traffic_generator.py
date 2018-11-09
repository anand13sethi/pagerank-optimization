import random

n = 25
with open(str(n)+"_traffic.txt", "w") as f:
    for i in range(n):
        f.write(str(i) + " " + str(random.randint(100, 700)) + "\n")

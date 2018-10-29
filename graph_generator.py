import random

with open("1000_nodes.txt", 'w') as fopen:
    for i in range(0, 499500):
        a = random.randint(1, 1000)
        b = random.randint(1, 1000)
        if a == b:
            b += 1
            fopen.write(str(a) + " " + str(b) + "\n")
        else:
            fopen.write(str(a) + " " + str(b) + "\n")

import random

no_of_nodes = 500
no_of_edges = 499*250


with open("100_nodes.txt", 'w') as fopen:
    for i in range(0, no_of_edges):
        a = random.randint(0, no_of_nodes-1)
        b = random.randint(0, no_of_nodes-1)
        if a == b:
            b = (b+1)%no_of_nodes;
            fopen.write(str(a) + " " + str(b) + "\n")
        else:
            fopen.write(str(a) + " " + str(b) + "\n")

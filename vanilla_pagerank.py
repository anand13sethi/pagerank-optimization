n = 1000
list_of_list = {}

with open("1000_nodes.txt", 'r') as fopen:
    for line in fopen:
        a, b = line.split()
        # list_of_list.keys().append(b)
        # print(a, b)
        if b not in list_of_list.keys():
            list_of_list[b] = [a]
        else:
            list_of_list[b].append(a)


with open("dict_output.txt", 'w') as fout:
    for item in list_of_list:
        fout.write(item + " - " + " ".join(list_of_list[item]) + "\n")


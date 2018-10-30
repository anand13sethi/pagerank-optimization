n = 1000
list_of_list = {}
outdegree = [0]*1001
rank = [1]*1001
with open("1000_nodes.txt", 'r') as fopen:
    for line in fopen:
        a, b = map(int, line.split())
        outdegree[a] += 1
        if b not in list_of_list.keys():
            list_of_list[b] = [a]
        else:
            list_of_list[b].append(a)

#
# with open("dict_output.txt", 'w') as fout:
#     for item in list_of_list:
#         fout.write(item + " - " + " ".join(list_of_list[item]) + "\n")
sum = 0
d = 0.85
for i in range(0, n+1):
    # print(list_of_list[i])
    if i in list_of_list.keys():
        for item in list_of_list[i]:
            sum += rank[item]/outdegree[item]
    rank[i] = (1-d) + d*sum
    sum = 0

[print(i) for i in rank]

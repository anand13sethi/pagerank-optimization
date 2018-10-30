n = 999
init_rank = 1/(n+1)
list_of_list = {}
outdegree = [0]*(n+1)
rank = [init_rank]*(n+1)
new_rank = [0]*(n+1)
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
while True:
    for i in range(0, n+1):
        if i in list_of_list.keys():
            for item in list_of_list[i]:
                donation = rank[item]/outdegree[item]
                sum += donation
        rank[i] = (1-d) + d*sum
        sum = 0

    x = 0

    for i in rank :
        x += i

    if round(x/(n+1),3) == 1:
        break

    

[print(i) for i in rank]


print("Average = ",x/(n+1))
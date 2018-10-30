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
for j in range (0,100):
    for i in range(0, n+1):
        # print(list_of_list[i])
        if i in list_of_list.keys():
            # print(" i = " , i)
            for item in list_of_list[i]:
                # print ("item = " ,item,rank[item],outdegree[item])
                donation = rank[item]/outdegree[item]
                # print (donation)
                sum += donation
                # rank[item] -= donation
        rank[i] = (1-d) + d*sum
        # print("sum = ", sum);
        sum = 0

    # for i in range(0,n+1):
    #     rank[i] = new_rank[i]

    # print (j)
    # [print(i) for i in new_rank]


[print(i) for i in rank]

sum = 0

for i in rank :
    sum += i


print ("sum =", sum)
print(sum/(n+1))
import random
m = 5
n = m*m

with open(str(n)+"_regions.txt", "w") as f:
    for i in range(n):
        # right
        if i < n-1 and (i+1) % m != 0:
            x = random.randint(5, 50)
            f.write(str(i) + " " + str(i+1) + " " + str(x) + "\n")
        # left
        if i > 0 and i % m != 0:
            x = random.randint(5, 50)
            f.write(str(i) + " " + str(i-1) + " " + str(x) + "\n")
        # up
        if i >= m:
            x = random.randint(5, 50)
            f.write(str(i) + " " + str(i-m) + " " + str(x) + "\n")
        # down
        if i < n-m:
            x = random.randint(5, 50)
            f.write(str(i) + " " + str(i+m) + " " + str(x) + "\n")
        # right bottom
        if i < n-m-1 and (i+1) % m != 0:
            x = random.randint(5, 50)
            f.write(str(i) + " " + str(i+m+1) + " " + str(x) + "\n")
        # left bottom
        if i < n-m+1 and i % m != 0:
            x = random.randint(5, 50)
            f.write(str(i) + " " + str(i+m-1) + " " + str(x) + "\n")
        # right top
        if i >= m and (i+1) % m != 0:
            x = random.randint(5, 50)
            f.write(str(i) + " " + str(i-m+1) + " " + str(x) + "\n")
        # left top
        if i >= m and i % m != 0:
            x = random.randint(5, 50)
            f.write(str(i) + " " + str(i-m-1) + " " + str(x) + "\n")
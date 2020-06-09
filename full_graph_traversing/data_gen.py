import random

n = 16

p = []
for _ in range(n):
    p.append((random.uniform(-10, 10), random.uniform(-10, 10)))

print(n)
for i in range(n):
    for j in range(i, n):
        if i != j:
            print(f"{i} {j} {((p[i][0] - p[j][0]) ** 2 + (p[i][1] - p[j][1]) ** 2)**0.5}")

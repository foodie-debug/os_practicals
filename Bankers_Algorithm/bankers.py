n = 5
m = 3
available = [3, 3, 2]
allocation = [
    [0, 1, 0],
    [2, 0, 0],
    [3, 0, 2],
    [2, 1, 1],
    [0, 0, 2]
]
maximum = [
    [7, 5, 3],
    [3, 2, 2],
    [9, 0, 2],
    [2, 2, 2],
    [4, 3, 3]
]
need = []
for i in range(n):
    row = []
    for j in range(m):
        row.append(maximum[i][j] - allocation[i][j])
    need.append(row)
print("Need Matrix:")
for i in range(n):
    print("P" + str(i), ":", need[i])
work = available.copy()
finished = [False] * n
safe_sequence = []
while len(safe_sequence) < n:
    found = False
    for i in range(n):
        if not finished[i]:
            possible = True
            for j in range(m):
                if need[i][j] > work[j]:
                    possible = False
                    break
            if possible:
                for j in range(m):
                    work[j] += allocation[i][j]
                finished[i] = True
                safe_sequence.append(i)
                found = True
    if not found:
        break
if len(safe_sequence) == n:
    print("\nSystem is in SAFE state")
    print("Safe Sequence:", " -> ".join("P" + str(i) for i in safe_sequence))
else:
    print("\nSystem is in UNSAFE state")

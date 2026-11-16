import matplotlib.pyplot as plt

head = 2150
requests = [2069, 1212, 2296, 2800, 544, 1618, 356, 1523, 4965, 3681]
disk_size = 5000   # cylinders 0 to 4999

movement = 0
current = head
sequence = [head]

left = sorted([r for r in requests if r < head])
right = sorted([r for r in requests if r >= head])

# service requests towards higher cylinders
for r in right:
    movement += abs(current - r)
    current = r
    sequence.append(r)

if left:
    # go to the last cylinder
    movement += abs(current - (disk_size - 1))
    current = disk_size - 1
    sequence.append(current)

    # jump back to cylinder 0 (counted in head movement)
    movement += disk_size - 1
    current = 0
    sequence.append(current)

    # continue servicing towards higher cylinders
    for r in left:
        movement += abs(current - r)
        current = r
        sequence.append(r)

print("Service Order:", sequence)
print("Total Head Movement:", movement)

steps = range(1, len(sequence) + 1)

plt.plot(sequence, steps, marker='o')
plt.scatter(head, 1, color='red', label='Starting Point', zorder=3)

for x, y in zip(sequence, steps):
    plt.text(x, y, str(x))

plt.title("C-SCAN Disk Scheduling")
plt.xlabel("Cylinder")
plt.ylabel("Step")
plt.grid(True)
plt.gca().invert_yaxis()
plt.legend()
plt.show()

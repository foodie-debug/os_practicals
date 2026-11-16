import matplotlib.pyplot as plt
head = 2150
requests = [2069, 1212, 2296, 2800, 544, 1618, 356, 1523, 4965, 3681]
movement = 0
current = head
sequence = [head]
for r in requests:
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
plt.title("FCFS Disk Scheduling")
plt.xlabel("Cylinder")
plt.ylabel("Step")
plt.grid(True)
plt.gca().invert_yaxis()
plt.legend()
plt.show()

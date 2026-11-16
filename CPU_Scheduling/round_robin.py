# Round Robin CPU Scheduling (Preemptive, fixed time quantum)
from collections import deque

class Process:
    def __init__(self, pid, arrival, burst):
        self.pid = pid
        self.arrival = arrival
        self.burst = burst
        self.remaining = burst
        self.completion = 0
        self.turnaround = 0
        self.waiting = 0


gantt = []   # list of [pid, start, end]; pid = -1 means CPU idle


def add_to_gantt(pid, start, end):
    """Adds a block to the Gantt chart, merges consecutive blocks of the
    same process and inserts an IDLE block if the CPU was free."""
    last_end = gantt[-1][2] if gantt else 0
    if start > last_end:
        gantt.append([-1, last_end, start])
    if gantt and gantt[-1][0] == pid and gantt[-1][2] == start:
        gantt[-1][2] = end
    else:
        gantt.append([pid, start, end])


def finish(p, time):
    p.completion = time
    p.turnaround = p.completion - p.arrival
    p.waiting = p.turnaround - p.burst


def round_robin(processes, quantum):
    n = len(processes)
    time = completed = 0
    for p in processes:
        p.remaining = p.burst
    q = deque()
    added = [False] * n

    def add_arrived():
        # push every process that has arrived by 'time', in arrival order
        arrived = [i for i in range(n)
                   if not added[i] and processes[i].arrival <= time]
        arrived.sort(key=lambda i: processes[i].arrival)
        for i in arrived:
            q.append(i)
            added[i] = True

    while completed < n:
        add_arrived()
        if not q:              # CPU idle until next arrival
            time += 1
            continue
        idx = q.popleft()
        p = processes[idx]
        start = time
        run_time = min(quantum, p.remaining)
        p.remaining -= run_time
        time += run_time
        add_to_gantt(p.pid, start, time)

        # processes that arrived during this time slice enter the queue
        # before the current process is put back at the end
        add_arrived()

        if p.remaining == 0:
            finish(p, time)
            completed += 1
        else:
            q.append(idx)


def print_gantt_chart():
    if not gantt:
        return
    print("\n\nGANTT CHART\n")
    print("--------" * len(gantt) + "-")
    row = ""
    for pid, start, end in gantt:
        row += "| IDLE  " if pid == -1 else "|  P" + str(pid).ljust(4)
    print(row + "|")
    print("--------" * len(gantt) + "-")
    times = str(gantt[0][1])
    for pid, start, end in gantt:
        times += "\t" + str(end)
    print(times)


def print_table(processes):
    processes = sorted(processes, key=lambda x: x.pid)
    print("\nPID\tAT\tBT\tCT\tTAT\tWT")
    total_tat = total_wt = 0
    for x in processes:
        print("P" + str(x.pid), x.arrival, x.burst, x.completion,
              x.turnaround, x.waiting, sep="\t")
        total_tat += x.turnaround
        total_wt += x.waiting
    print("\nAverage Turnaround Time =", round(total_tat / len(processes), 2))
    print("Average Waiting Time    =", round(total_wt / len(processes), 2))


def read_processes():
    n = int(input("Enter number of processes: "))
    if n <= 0:
        print("Number of processes must be positive.")
        exit()
    processes = []
    for i in range(1, n + 1):
        arrival = int(input("Arrival Time P" + str(i) + ": "))
        burst = int(input("Burst Time P" + str(i) + ": "))
        processes.append(Process(i, arrival, burst))
    return processes


processes = read_processes()
quantum = int(input("Enter time quantum: "))
if quantum <= 0:
    print("Time quantum must be positive.")
    exit()
round_robin(processes, quantum)
print_gantt_chart()
print_table(processes)

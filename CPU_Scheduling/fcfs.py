# FCFS (First Come First Serve) CPU Scheduling - Non-Preemptive

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


def fcfs(processes):
    # sorted() is stable, so processes with equal arrival keep input order
    order = sorted(processes, key=lambda x: x.arrival)
    time = 0
    for p in order:
        if time < p.arrival:
            time = p.arrival
        start = time
        time += p.burst
        finish(p, time)
        add_to_gantt(p.pid, start, time)


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
fcfs(processes)
print_gantt_chart()
print_table(processes)

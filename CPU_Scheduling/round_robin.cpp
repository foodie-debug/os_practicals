// Round Robin CPU Scheduling (Preemptive, fixed time quantum)
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining = 0;
    int completion = 0;
    int turnaround = 0;
    int waiting = 0;
};

struct Gantt {
    int pid;   // -1 means CPU idle
    int start;
    int end;
};

vector<Gantt> gantt;

// Adds a block to the Gantt chart; merges consecutive blocks of the same
// process and inserts an IDLE block if the CPU was free
void addToGantt(int pid, int start, int end) {
    int lastEnd = gantt.empty() ? 0 : gantt.back().end;
    if (start > lastEnd)
        gantt.push_back({-1, lastEnd, start});
    if (!gantt.empty() && gantt.back().pid == pid && gantt.back().end == start)
        gantt.back().end = end;
    else
        gantt.push_back({pid, start, end});
}

void RoundRobin(vector<Process>& p, int quantum) {
    int n = p.size();
    int time = 0, completed = 0;
    for (int i = 0; i < n; i++)
        p[i].remaining = p[i].burst;
    queue<int> q;
    vector<bool> added(n, false);

    // pushes every process that has arrived by 'time' (in arrival order)
    auto addArrived = [&]() {
        vector<int> order;
        for (int i = 0; i < n; i++)
            if (!added[i] && p[i].arrival <= time) order.push_back(i);
        stable_sort(order.begin(), order.end(), [&](int a, int b) {
            return p[a].arrival < p[b].arrival;
        });
        for (int i : order) {
            q.push(i);
            added[i] = true;
        }
    };

    while (completed < n) {
        addArrived();
        if (q.empty()) {   // CPU idle until next arrival
            time++;
            continue;
        }
        int idx = q.front();
        q.pop();
        int start = time;
        int runTime = min(quantum, p[idx].remaining);
        p[idx].remaining -= runTime;
        time += runTime;
        addToGantt(p[idx].pid, start, time);

        // processes that arrived during this time slice enter the queue
        // before the current process is put back at the end
        addArrived();

        if (p[idx].remaining == 0) {
            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            completed++;
        } else {
            q.push(idx);
        }
    }
}

void printGanttChart() {
    if (gantt.empty()) return;
    cout << "\n\nGANTT CHART\n\n";
    for (size_t i = 0; i < gantt.size(); i++) cout << "--------";
    cout << "-\n";
    for (auto& g : gantt) {
        if (g.pid == -1) cout << "| IDLE  ";
        else             cout << "|  P" << g.pid << (g.pid < 10 ? "   " : "  ");
    }
    cout << "|\n";
    for (size_t i = 0; i < gantt.size(); i++) cout << "--------";
    cout << "-\n";
    cout << gantt[0].start;
    for (auto& g : gantt) cout << "\t" << g.end;
    cout << "\n";
}

void printTable(const vector<Process>& p) {
    double totalTAT = 0, totalWT = 0;
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto& x : p) {
        cout << "P" << x.pid << "\t" << x.arrival << "\t" << x.burst << "\t"
             << x.completion << "\t" << x.turnaround << "\t" << x.waiting << "\n";
        totalTAT += x.turnaround;
        totalWT += x.waiting;
    }
    cout << "\nAverage Turnaround Time = " << totalTAT / p.size();
    cout << "\nAverage Waiting Time    = " << totalWT / p.size() << "\n";
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    if (n <= 0) {
        cout << "Number of processes must be positive.\n";
        return 0;
    }
    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Arrival Time P" << i + 1 << ": ";
        cin >> p[i].arrival;
        cout << "Burst Time P" << i + 1 << ": ";
        cin >> p[i].burst;
    }

    int quantum;
    cout << "Enter time quantum: ";
    cin >> quantum;
    if (quantum <= 0) {
        cout << "Time quantum must be positive.\n";
        return 0;
    }
    RoundRobin(p, quantum);
    printGanttChart();
    printTable(p);
    return 0;
}

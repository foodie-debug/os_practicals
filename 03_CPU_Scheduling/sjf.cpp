// SJF (Shortest Job First) CPU Scheduling
// 1. Non-Preemptive SJF
// 2. Preemptive SJF (SRTF - Shortest Remaining Time First)
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
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

void SJF_NonPreemptive(vector<Process>& p) {
    int n = p.size();
    int time = 0, completed = 0;
    vector<bool> done(n, false);
    while (completed < n) {
        int idx = -1;
        int shortest = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time && p[i].burst < shortest) {
                shortest = p[i].burst;
                idx = i;
            }
        }
        if (idx == -1) {   // no process has arrived yet
            time++;
            continue;
        }
        int start = time;
        time += p[idx].burst;
        p[idx].completion = time;
        p[idx].turnaround = p[idx].completion - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;
        done[idx] = true;
        completed++;
        addToGantt(p[idx].pid, start, time);
    }
}

void SJF_Preemptive(vector<Process>& p) {
    int n = p.size();
    int time = 0, completed = 0;
    for (int i = 0; i < n; i++)
        p[i].remaining = p[i].burst;
    while (completed < n) {
        int idx = -1;
        int shortest = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < shortest) {
                shortest = p[i].remaining;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        // run the selected process for 1 time unit
        p[idx].remaining--;
        addToGantt(p[idx].pid, time, time + 1);
        time++;
        if (p[idx].remaining == 0) {
            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            completed++;
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

    int choice;
    cout << "\n1. SJF Non-Preemptive";
    cout << "\n2. SJF Preemptive (SRTF)";
    cout << "\nEnter choice: ";
    cin >> choice;

    switch (choice) {
        case 1: SJF_NonPreemptive(p); break;
        case 2: SJF_Preemptive(p); break;
        default:
            cout << "Invalid choice\n";
            return 0;
    }
    printGanttChart();
    printTable(p);
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Process {
    int pid;
    int arrival;
    int burst;
    int completion = 0;
    int turnaround = 0;
    int waiting = 0;
};
struct Gantt {
    int pid;   
    int start;
    int end;
};
vector<Gantt> gantt;
void addToGantt(int pid, int start, int end) {
    int lastEnd = gantt.empty() ? 0 : gantt.back().end;
    if (start > lastEnd)
        gantt.push_back({-1, lastEnd, start});
    gantt.push_back({pid, start, end});
}
void FCFS(vector<Process>& p) {
    stable_sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival;
    });
    int time = 0;
    for (size_t i = 0; i < p.size(); i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;
        int start = time;
        time += p[i].burst;
        p[i].completion = time;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        addToGantt(p[i].pid, start, time);
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
void printTable(vector<Process> p) {
    sort(p.begin(), p.end(), [](const Process& a, const Process& b) { return a.pid < b.pid; });
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
    FCFS(p);
    printGanttChart();
    printTable(p);
    return 0;
}
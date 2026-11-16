// Banker's Algorithm - Deadlock Avoidance (Safety Algorithm)
#include <iostream>
#include <vector>
using namespace std;

int main() {
    const int n = 5;   // number of processes
    const int m = 3;   // number of resource types (A, B, C)

    vector<int> available = {3, 3, 2};

    vector<vector<int>> allocation = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    vector<vector<int>> maximum = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Need = Maximum - Allocation
    vector<vector<int>> need(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];

    cout << "Need Matrix:\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i << " : [";
        for (int j = 0; j < m; j++)
            cout << need[i][j] << (j < m - 1 ? ", " : "");
        cout << "]\n";
    }

    vector<int> work = available;
    vector<bool> finished(n, false);
    vector<int> safeSequence;

    while ((int)safeSequence.size() < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finished[i]) {
                bool possible = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }
                if (possible) {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];
                    finished[i] = true;
                    safeSequence.push_back(i);
                    found = true;
                }
            }
        }
        if (!found)
            break;
    }

    if ((int)safeSequence.size() == n) {
        cout << "\nSystem is in SAFE state\n";
        cout << "Safe Sequence: ";
        for (int i = 0; i < n; i++)
            cout << "P" << safeSequence[i] << (i < n - 1 ? " -> " : "\n");
    } else {
        cout << "\nSystem is in UNSAFE state\n";
    }
    return 0;
}

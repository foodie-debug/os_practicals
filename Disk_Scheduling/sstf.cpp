// SSTF (Shortest Seek Time First) Disk Scheduling
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <climits>
using namespace std;

int SSTF(const vector<int>& requests, int head)
{
    ofstream file("SSTF.csv");
    file << "Step,Cylinder\n";
    int totalMovement = 0;
    int step = 0;
    file << step++ << "," << head << "\n";
    int n = requests.size();
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) {
        int minDistance = INT_MAX;
        int index = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(requests[j] - head) < minDistance) {
                minDistance = abs(requests[j] - head);
                index = j;
            }
        }
        totalMovement += minDistance;
        head = requests[index];
        visited[index] = true;
        file << step++ << "," << head << "\n";
    }
    file.close();
    return totalMovement;
}

int main()
{
    int n;
    cout << "Enter number of requests: ";
    cin >> n;
    if (n <= 0) {
        cout << "Number of requests must be positive." << endl;
        return 0;
    }
    vector<int> requests(n);
    cout << "Enter the disk requests:\n";
    for (int i = 0; i < n; i++)
        cin >> requests[i];
    int head;
    cout << "Enter initial head position: ";
    cin >> head;
    int movement = SSTF(requests, head);
    cout << "\n========== SSTF ==========\n";
    cout << "Total Head Movement = " << movement << endl;
    cout << "CSV file generated successfully: SSTF.csv" << endl;
    return 0;
}

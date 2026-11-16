// C-SCAN (Circular SCAN) Disk Scheduling - head moves towards higher cylinders
// The jump from the last cylinder back to cylinder 0 is counted in head movement.
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
using namespace std;

int CSCAN(const vector<int>& requests, int head, int diskSize)
{
    ofstream file("CSCAN.csv");
    file << "Step,Cylinder\n";
    int totalMovement = 0;
    int step = 0;
    file << step++ << "," << head << "\n";
    vector<int> left, right;
    for (int r : requests) {
        if (r < head) left.push_back(r);
        else          right.push_back(r);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // service requests towards higher cylinders
    for (int r : right) {
        totalMovement += abs(head - r);
        head = r;
        file << step++ << "," << head << "\n";
    }

    if (!left.empty()) {
        // go to the last cylinder
        totalMovement += abs(head - (diskSize - 1));
        head = diskSize - 1;
        file << step++ << "," << head << "\n";

        // jump back to cylinder 0
        totalMovement += diskSize - 1;
        head = 0;
        file << step++ << "," << head << "\n";

        // continue servicing towards higher cylinders
        for (int r : left) {
            totalMovement += abs(head - r);
            head = r;
            file << step++ << "," << head << "\n";
        }
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
    int diskSize;
    cout << "Enter disk size (number of cylinders): ";
    cin >> diskSize;
    if (head < 0 || head >= diskSize) {
        cout << "Head position must be between 0 and " << diskSize - 1 << endl;
        return 0;
    }
    for (int r : requests) {
        if (r < 0 || r >= diskSize) {
            cout << "Request " << r << " is outside the disk (0 to " << diskSize - 1 << ")" << endl;
            return 0;
        }
    }
    int movement = CSCAN(requests, head, diskSize);
    cout << "\n========== C-SCAN ==========\n";
    cout << "Total Head Movement = " << movement << endl;
    cout << "CSV file generated successfully: CSCAN.csv" << endl;
    return 0;
}

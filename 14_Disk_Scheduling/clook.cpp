// C-LOOK (Circular LOOK) Disk Scheduling - head moves towards higher cylinders
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
using namespace std;

int CLOOK(const vector<int>& requests, int head)
{
    ofstream file("CLOOK.csv");
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

    // jump to the lowest pending request and continue upwards
    for (int r : left) {
        totalMovement += abs(head - r);
        head = r;
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
    int movement = CLOOK(requests, head);
    cout << "\n========== C-LOOK ==========\n";
    cout << "Total Head Movement = " << movement << endl;
    cout << "CSV file generated successfully: CLOOK.csv" << endl;
    return 0;
}

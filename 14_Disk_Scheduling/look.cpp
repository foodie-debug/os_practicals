// LOOK Disk Scheduling - head first moves towards higher cylinders
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
using namespace std;

int LOOK(const vector<int>& requests, int head)
{
    ofstream file("LOOK.csv");
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

    // reverse at the last request (not at the end of the disk)
    for (int i = (int)left.size() - 1; i >= 0; i--) {
        totalMovement += abs(head - left[i]);
        head = left[i];
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
    int movement = LOOK(requests, head);
    cout << "\n========== LOOK ==========\n";
    cout << "Total Head Movement = " << movement << endl;
    cout << "CSV file generated successfully: LOOK.csv" << endl;
    return 0;
}

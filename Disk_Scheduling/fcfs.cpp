#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
using namespace std;
int FCFS(const vector<int>& requests, int head)
{
    ofstream file("FCFS.csv");
    file << "Step,Cylinder\n";
    int totalMovement = 0;
    int step = 0;
    file << step++ << "," << head << "\n";
    for (int request : requests) {
        totalMovement += abs(request - head);
        head = request;
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
    int movement = FCFS(requests, head);
    cout << "\n========== FCFS ==========\n";
    cout << "Total Head Movement = " << movement << endl;
    cout << "CSV file generated successfully: FCFS.csv" << endl;
    return 0;
}

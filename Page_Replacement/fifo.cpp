// FIFO Page Replacement
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isPresent(const vector<int>& frames, int page) {
    return find(frames.begin(), frames.end(), page) != frames.end();
}

void fifo(const vector<int>& pages, int capacity, int& faults, int& hits) {
    vector<int> frames;
    int pointer = 0;
    faults = hits = 0;
    for (int page : pages) {
        if (isPresent(frames, page)) {
            hits++;
        } else {
            faults++;
            if ((int)frames.size() < capacity) {
                frames.push_back(page);
            } else {
                frames[pointer] = page;            // replace the oldest page
                pointer = (pointer + 1) % capacity;
            }
        }
    }
}

int main() {
    vector<int> pages = {2, 2, 3, 4, 3, 5, 1, 4, 3, 1, 4, 5, 1, 2, 3, 1};
    int capacity = 3;

    int faults, hits;
    fifo(pages, capacity, faults, hits);

    cout << "FIFO Page Replacement\n";
    cout << "Reference String: [";
    for (size_t i = 0; i < pages.size(); i++)
        cout << pages[i] << (i + 1 < pages.size() ? ", " : "]\n");
    cout << "Frames: " << capacity << "\n";
    cout << "Page Faults: " << faults << "\n";
    cout << "Page Hits: " << hits << "\n";
    return 0;
}

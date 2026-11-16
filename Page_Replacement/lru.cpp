#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool isPresent(const vector<int>& frames, int page) {
    return find(frames.begin(), frames.end(), page) != frames.end();
}
void lru(const vector<int>& pages, int capacity, int& faults, int& hits) {
    vector<int> frames;
    vector<int> recent;
    faults = hits = 0;
    for (int page : pages) {
        if (isPresent(frames, page)) {
            hits++;
            recent.erase(find(recent.begin(), recent.end(), page));
        } else {
            faults++;
            if ((int)frames.size() == capacity) {
                int old = recent.front();
                recent.erase(recent.begin());
                frames.erase(find(frames.begin(), frames.end(), old));
            }
            frames.push_back(page);
        }
        recent.push_back(page);
    }
}
int main() {
    vector<int> pages = {2, 2, 3, 4, 3, 5, 1, 4, 3, 1, 4, 5, 1, 2, 3, 1};
    int capacity = 3;
    int faults, hits;
    lru(pages, capacity, faults, hits);
    cout << "LRU Page Replacement\n";
    cout << "Reference String: [";
    for (size_t i = 0; i < pages.size(); i++)
        cout << pages[i] << (i + 1 < pages.size() ? ", " : "]\n");
    cout << "Frames: " << capacity << "\n";
    cout << "Page Faults: " << faults << "\n";
    cout << "Page Hits: " << hits << "\n";
    return 0;
}

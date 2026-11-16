// Optimal Page Replacement
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isPresent(const vector<int>& frames, int page) {
    return find(frames.begin(), frames.end(), page) != frames.end();
}

void optimal(const vector<int>& pages, int capacity, int& faults, int& hits) {
    vector<int> frames;
    faults = hits = 0;
    int n = pages.size();
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        if (isPresent(frames, page)) {
            hits++;
        } else {
            faults++;
            if ((int)frames.size() < capacity) {
                frames.push_back(page);
            } else {
                // replace the page that will be used farthest in the future
                int replaceIdx = 0, farthest = -1;
                for (int f = 0; f < (int)frames.size(); f++) {
                    int nextUse = n;   // n means "never used again"
                    for (int j = i + 1; j < n; j++) {
                        if (pages[j] == frames[f]) {
                            nextUse = j;
                            break;
                        }
                    }
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        replaceIdx = f;
                    }
                }
                frames[replaceIdx] = page;
            }
        }
    }
}

int main() {
    vector<int> pages = {2, 2, 3, 4, 3, 5, 1, 4, 3, 1, 4, 5, 1, 2, 3, 1};
    int capacity = 3;

    int faults, hits;
    optimal(pages, capacity, faults, hits);

    cout << "Optimal Page Replacement\n";
    cout << "Reference String: [";
    for (size_t i = 0; i < pages.size(); i++)
        cout << pages[i] << (i + 1 < pages.size() ? ", " : "]\n");
    cout << "Frames: " << capacity << "\n";
    cout << "Page Faults: " << faults << "\n";
    cout << "Page Hits: " << hits << "\n";
    return 0;
}

#include "heapsort.hpp"
#include <algorithm>

void heapify(std::vector<LogEntry>& logs, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && logs[l].timestamp > logs[largest].timestamp)
        largest = l;

    if (r < n && logs[r].timestamp > logs[largest].timestamp)
        largest = r;

    if (largest != i) {
        std::swap(logs[i], logs[largest]);
        heapify(logs, n, largest);
    }
}

void heapsort(std::vector<LogEntry>& logs) {
    int n = logs.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(logs, n, i);
    for (int i = n - 1; i > 0; i--) {
        std::swap(logs[0], logs[i]);
        heapify(logs, i, 0);
    }
}
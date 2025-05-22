#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include <vector>
#include "logentry.hpp"

void heapify(std::vector<LogEntry>& logs, int n, int i);
void heapsort(std::vector<LogEntry>& logs);

#endif
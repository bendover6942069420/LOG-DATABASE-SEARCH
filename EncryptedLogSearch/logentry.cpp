#include "logentry.hpp"
#include <iostream>

// Initializes a log entry with a timestamp and event description
LogEntry::LogEntry(std::string t, std::string e) : timestamp(t), event(e) {}

//displays the log entry in a formatted manner
// This function prints the timestamp and event to the console
void LogEntry::display() const {
    std::cout << timestamp << ": " << event << std::endl;
}
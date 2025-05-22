#ifndef LOGENTRY_HPP
#define LOGENTRY_HPP

#include <string>

class LogEntry {
public:
    std::string timestamp;
    std::string event;

    LogEntry(std::string t, std::string e);
    void display() const;
};

#endif
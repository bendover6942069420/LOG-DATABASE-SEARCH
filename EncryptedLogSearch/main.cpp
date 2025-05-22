#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "logentry.hpp"
#include "heapsort.hpp"
#include "boyermoore.hpp"
#include "encryption.hpp"

void encryptLogFile(const std::string& inputPath, const std::string& outputPath, const std::string& keyFile) {
    // Generate a new encryption key
    std::string key = Encryption::generateKey(32);
    
    // Save the key
    std::ofstream keyOut(keyFile);
    if (!keyOut.is_open()) {
        std::cerr << "Error: Could not create key file" << std::endl;
        return;
    }
    keyOut << key;
    keyOut.close();

    std::ifstream in(inputPath);
    if (!in.is_open()) {
        std::cerr << "Error: Could not open input file: " << inputPath << std::endl;
        return;
    }

    std::ofstream out(outputPath);
    if (!out.is_open()) {
        std::cerr << "Error: Could not open output file: " << outputPath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string timestamp, event;
        std::getline(ss, timestamp, '|');
        std::getline(ss, event);

        out << Encryption::xorEncryptDecrypt(timestamp, key) << '|' 
            << Encryption::xorEncryptDecrypt(event, key) << '\n';
    }
}

std::string loadKey(const std::string& keyFile) {
    std::ifstream keyIn(keyFile);
    if (!keyIn.is_open()) {
        throw std::runtime_error("Could not open key file");
    }
    std::string key;
    std::getline(keyIn, key);
    return key;
}

int main() {
    const std::string KEY_FILE = "encryption.key";
    const std::string ENCRYPTED_FILE = "encrypted_logs.txt";
    
    try {
        // First, encrypt the original log file
        encryptLogFile("logs.txt", ENCRYPTED_FILE, KEY_FILE);
        std::string key = loadKey(KEY_FILE);

        std::vector<LogEntry> logs;
        std::ifstream infile(ENCRYPTED_FILE);
        
        if (!infile.is_open()) {
            std::cerr << "Error: Could not open encrypted logs file" << std::endl;
            return 1;
        }

        std::string line;
        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string timestamp, event;
            std::getline(ss, timestamp, '|');
            std::getline(ss, event);
            logs.emplace_back(
                Encryption::xorEncryptDecrypt(timestamp, key),
                Encryption::xorEncryptDecrypt(event, key)
            );
        }

        // Sort logs by timestamp
        heapsort(logs);

        // Search functionality with multiple search support
        while (true) {
            std::string keyword;
            std::cout << "\nEnter keyword to search (or 'exit' to quit): ";
            std::getline(std::cin, keyword);

            if (keyword == "exit") break;

            std::cout << "\nSearch Results:\n";
            bool found = false;
            for (const auto& log : logs) {
                if (boyerMooreSearch(log.event, keyword) != -1) {
                    log.display();
                    found = true;
                }
            }
            
            if (!found) {
                std::cout << "No matches found.\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
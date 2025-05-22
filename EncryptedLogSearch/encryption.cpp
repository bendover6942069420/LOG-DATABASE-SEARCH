#include "encryption.hpp"
#include <random>
#include <chrono>

std::string Encryption::xorEncryptDecrypt(const std::string& input, const std::string& key) {
    if (input.empty() || key.empty()) return input;
    
    std::vector<unsigned char> expandedKey = expandKey(key, input.length());
    std::string output = input;
    
    for (size_t i = 0; i < input.length(); ++i) {
        output[i] = input[i] ^ expandedKey[i];
    }
    
    return output;
}

std::string Encryption::generateKey(size_t length) {
    std::string key;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(33, 126); // Printable ASCII characters
    
    for (size_t i = 0; i < length; ++i) {
        key += static_cast<char>(dis(gen));
    }
    
    return key;
}

std::vector<unsigned char> Encryption::expandKey(const std::string& key, size_t length) {
    std::vector<unsigned char> expandedKey(length);
    for (size_t i = 0; i < length; ++i) {
        expandedKey[i] = key[i % key.length()];
    }
    return expandedKey;
}
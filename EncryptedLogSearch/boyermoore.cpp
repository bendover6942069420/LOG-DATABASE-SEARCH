#include "boyermoore.hpp"
#include <vector>
#include <algorithm>
#include <cctype>

int boyerMooreSearch(const std::string& text, const std::string& pattern) {
    if (pattern.empty() || text.empty()) return -1;
    
    int m = pattern.length();
    int n = text.length();
    std::vector<int> badChar(256, -1);

    // Convert pattern to lowercase for case-insensitive search
    std::string lowerPattern = pattern;
    std::transform(lowerPattern.begin(), lowerPattern.end(), lowerPattern.begin(), ::tolower);

    // Preprocess the pattern for bad character heuristic
    for (int i = 0; i < m; i++) {
        badChar[(unsigned char)std::tolower(lowerPattern[i])] = i;
    }

    int s = 0;  // s is the shift of the pattern
    while (s <= (n - m)) {
        int j = m - 1;

        // Check current window from right to left
        while (j >= 0 && std::tolower(text[s + j]) == std::tolower(lowerPattern[j])) {
            j--;
        }

        if (j < 0) {
            // Pattern found
            return s;
        } else {
            // Calculate shift using bad character rule
            char textChar = std::tolower(text[s + j]);
            s += std::max(1, j - badChar[(unsigned char)textChar]);
        }
    }
    return -1;
}
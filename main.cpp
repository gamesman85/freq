#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>

// Comparison function for sorting
bool compareFrequency(const std::pair<char, int>& a, const std::pair<char, int>& b) {
    return a.second > b.second;
}

int main() {
    std::string filename;
    std::cout << "Enter the filename to analyze: ";
    std::cin >> filename;
    
    // Open the file
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }
    
    // Map to store the frequency of each letter
    std::map<char, int> frequency;
    
    // Initialize frequency count for all letters to zero
    for (char c = 'a'; c <= 'z'; c++) {
        frequency[c] = 0;
    }
    
    // Read the file character by character
    char c;
    int totalLetters = 0;
    
    while (file.get(c)) {
        // Convert to lowercase
        c = std::tolower(c);
        
        // Only count alphabetic characters
        if (c >= 'a' && c <= 'z') {
            frequency[c]++;
            totalLetters++;
        }
    }
    
    // Close the file
    file.close();
    
    // Create a vector of pairs for sorting
    std::vector<std::pair<char, int> > frequencyVector;
    for (const auto& pair : frequency) {
        frequencyVector.push_back(pair);
    }
    
    // Sort by frequency (descending)
    std::sort(frequencyVector.begin(), frequencyVector.end(), compareFrequency);
    
    // Output the results
    std::cout << "\nFrequency Analysis Results:\n";
    std::cout << "-------------------------\n";
    
    for (const auto& pair : frequencyVector) {
        // Calculate percentage with 2 decimal precision
        double percentage = 0.0;
        if (totalLetters > 0) {
            percentage = static_cast<double>(pair.second) * 100.0 / totalLetters;
        }
        
        // Only display letters that actually appear in the text
        if (pair.second > 0) {
            std::cout << pair.first << " - " << std::fixed << std::setprecision(2) << percentage << "%" << std::endl;
        }
    }
    
    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> parseLineBySpaces(std::string line) {
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string word;
    
    while (ss >> word) {
        result.push_back(word);
    }
    
    return result;
}

void runShell() {
    std::string line;
    
    while (true) {
        std::cout << "system-lab> ";
        
        // Read entire line from user
        if (!std::getline(std::cin, line)) {
            // Ctrl+D pressed (EOF)
            std::cout << std::endl;
            break;
        }
        
        // Check if user entered "exit"
        if (line == "exit") {
            break;
        }
        
        // Parse the input line and get words
        std::vector<std::string> words = parseLineBySpaces(line);
        
        // Display parsed words
        std::cout << "Parsed words: ";
        for (const auto& word : words) {
            std::cout << word << "-";
        }
        std::cout << std::endl;
    }
}

int main() {
    runShell();
    return 0;
}

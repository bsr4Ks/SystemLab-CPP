#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

std::vector<std::string> parseLineBySpaces(std::string line) {
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string word;
    
    while (ss >> word) {
        result.push_back(word);
    }
    
    return result;
}

bool handleBuiltInCommand(std::vector<std::string>& args) {
    if (args.empty()) {
        return false;
    }
    
    // Handle "cd" command
    if (args[0] == "cd") {
        if (args.size() < 2) {
            std::cerr << "cd: missing argument" << std::endl;
        } else {
            if (chdir(args[1].c_str()) != 0) {
                std::cerr << "cd: cannot change directory to " << args[1] << std::endl;
            }
        }
        return true;
    }
    
    return false;
}

void executeCommand(std::vector<std::string>& args) {
    if (args.empty()) {
        return;
    }
    
    // Check for built-in commands first
    if (handleBuiltInCommand(args)) {
        return;
    }
    
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        // Convert vector<string> to char* array for execvp
        char* argv[args.size() + 1];
        for (size_t i = 0; i < args.size(); i++) {
            argv[i] = (char*)args[i].c_str();
        }
        argv[args.size()] = nullptr;
        
        // Execute the command
        execvp(argv[0], argv);
        
        // If execvp returns, an error occurred
        std::cerr << "Error executing command: " << args[0] << std::endl;
        exit(1);
    } else if (pid > 0) {
        // Parent process - wait for child to finish
        int status;
        waitpid(pid, &status, 0);
    } else {
        // Fork failed
        std::cerr << "Fork failed" << std::endl;
    }
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
        
        // Execute the command
        executeCommand(words);
    }
}

int main() {
    runShell();
    return 0;
}

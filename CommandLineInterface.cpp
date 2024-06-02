#include "CommandLineInterface.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

// 파일에서 명령어 읽기
std::vector<std::string> CommandLineInterface::readCommandsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> commands;
    std::string line;
    while (std::getline(file, line)) {
        commands.push_back(line);
    }
    return commands;
}

// 명령어 파싱
std::vector<std::string> CommandLineInterface::parseCommand(const std::string& command) {
    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// 명령어 실행
void CommandLineInterface::executeCommand(const std::vector<std::string>& args) {
    if (args.empty()) return;

    const std::string& cmd = args[0];

    if (cmd == "echo") {
        std::cout << "Executing command: " << cmd;
        for (size_t i = 1; i < args.size(); ++i) {
            std::cout << " " << args[i];
        }
        std::cout << std::endl;
        for (size_t i = 1; i < args.size(); ++i) {
            std::cout << args[i] << " ";
        }
        std::cout << std::endl;
    }
    else if (cmd == "sum") {
        if (args.size() >= 3) {
            try {
                int a = std::stoi(args[1]);
                int b = std::stoi(args[2]);
                std::cout << "Sum: " << sum(a, b) << std::endl;
            }
            catch (...) {
                std::cerr << "Invalid arguments for sum command" << std::endl;
            }
        }
    }
    else if (cmd == "gcd") {
        if (args.size() >= 3) {
            try {
                int a = std::stoi(args[1]);
                int b = std::stoi(args[2]);
                std::cout << "GCD: " << gcd(a, b) << std::endl;
            }
            catch (...) {
                std::cerr << "Invalid arguments for gcd command" << std::endl;
            }
        }
    }
    else if (cmd == "dummy") {
        std::cout << "Executing dummy command with argument: " << args[1] << std::endl;
    }
    else {
        std::cerr << "Unknown command: " << cmd << std::endl;
    }
}

// 명령어 기능 구현
int CommandLineInterface::sum(int a, int b) {
    return a + b;
}

int CommandLineInterface::gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// 명령어 실행 루프
void CommandLineInterface::run(const std::string& filename, int interval) {
    std::vector<std::string> commands = readCommandsFromFile(filename);

    for (const auto& command : commands) {
        std::this_thread::sleep_for(std::chrono::seconds(interval));
        std::vector<std::string> args = parseCommand(command);
        executeCommand(args);
    }
}


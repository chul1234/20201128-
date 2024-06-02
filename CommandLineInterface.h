#ifndef COMMANDLINEINTERFACE_H
#define COMMANDLINEINTERFACE_H

#include <string>
#include <vector>

class CommandLineInterface {
public:
    void run(const std::string& filename, int interval);
private:
    std::vector<std::string> readCommandsFromFile(const std::string& filename);
    std::vector<std::string> parseCommand(const std::string& command);
    void executeCommand(const std::vector<std::string>& args);
    int sum(int a, int b);
    int gcd(int a, int b);
};

#endif // COMMANDLINEINTERFACE_H



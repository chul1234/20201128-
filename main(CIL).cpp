#include "CommandLineInterface.h"

int main() {
    CommandLineInterface cli;
    cli.run("commands.txt", 2);
    return 0;
}

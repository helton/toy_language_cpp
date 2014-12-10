#ifndef REPL_HPP
#define REPL_HPP

#include <string>

class REPL {
public:
    REPL(std::string repl_text) : repl_text(repl_text) {}
    REPL() : REPL("repl") {}
    void run();
private:
    int command_count = 1;
    std::string repl_text;

    void execute(std::string command);
    void print_welcome();
    void print_repl();
};

#endif // REPL_HPP

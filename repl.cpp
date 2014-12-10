#include "repl.hpp"
#include "parser.hpp"
#include "ast.hpp"
#include "interpreter.hpp"

void REPL::run() {
    print_welcome();
    std::string line;
    while (std::cin.good()) {
        print_repl();
        std::getline(std::cin, line);
        if (!line.empty())
            execute(line);
    }
    std::cout << "Exiting... bye!\n";
}

void REPL::execute(std::string command) {
    std::stringstream iss(command);
    Lexer lexer(iss);
    Parser parser(lexer);
    std::shared_ptr<ASTNode> tree = parser.parse();
    Interpreter interpreter;
    std::cout << "=> " << interpreter.evaluate(tree)->to_string() << std::endl;
    command_count++;
}

void REPL::print_welcome() {
    std::cout << "=================================================\n";
    std::cout << "Welcome to the REPL of a toy programming language\n";
    std::cout << "=================================================\n";
}

void REPL::print_repl() {
    std::cout << repl_text << "(" << command_count << ")> ";
}

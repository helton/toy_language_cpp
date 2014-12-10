#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "ast.hpp"
#include "object.hpp"
#include <memory>
#include <map>

class Memory {
public:
    std::shared_ptr<Double> get_value(std::string variable_name) {
        return memory[variable_name];
    }
    void store_value(std::string variable_name, std::shared_ptr<Double> value) {
        memory[variable_name] = value;
    }
private:
    std::map<std::string, std::shared_ptr<Double>> memory;
};

class Interpreter {
public:
    std::shared_ptr<Object> evaluate(std::shared_ptr<ASTNode> tree);
private:
    Memory memory;
};

#endif // INTERPRETER_HPP

#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"
#include "matcher_function_builder.hpp"
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

class Lexer {
public:
    Lexer(std::istream& input) : input(input) {}
    std::vector<std::shared_ptr<Token>> tokenize();
private:
    std::istream& input;
    std::vector<std::shared_ptr<Token>> tokens;
    TextPosition text_position;

    bool read_if(MatcherFunction matcher, std::string& lexeme);
    void read_while(MatcherFunction matcher, std::string& lexeme);
    void skip_spaces();
    std::shared_ptr<Token> read_float();
    std::shared_ptr<Token> read_unsigned_int();
    std::shared_ptr<Token> read_identifier();
    std::shared_ptr<Token> read_symbols();
    std::shared_ptr<Token> get_token();
};

#endif // LEXER_HPP

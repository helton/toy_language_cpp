#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"
#include "ast.hpp"
#include <cstdlib>

/*
    EBNF Grammar

    <program> ::= <expression> {';' <expression> }
    <expression> ::= ['-'] <term> {['+'|'-'] <term>}
    <term> ::= <factor> {['*'|'/'] <factor>}
    <factor> ::= UNSIGNED_INT | IDENTIFIER ['=' <expression>] | '(' <expression> ')'
*/

class Parser {
public:
    Parser(Lexer& lexer) : lexer(lexer) {}
    std::shared_ptr<ASTNode> parse();
private:
    Lexer& lexer;
    std::vector<std::shared_ptr<Token>> tokens;
    std::shared_ptr<Token> lookahead;

    static void report_error(const std::string& message);
    std::shared_ptr<Token> get_token();
    bool is_match(TokenType expected_type) const;
    void match(TokenType expected_type);
    std::shared_ptr<ASTNode> program();
    std::shared_ptr<ASTNode> expression();
    std::shared_ptr<ASTNode> term();
    std::shared_ptr<ASTNode> factor();
};

#endif // PARSER_HPP

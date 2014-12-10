#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "text_position.hpp"

enum class TokenType  {
    IDENTIFIER,
    UNSIGNED_INT,
    FLOAT,
    EQUALS,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    COMMA,
    COLON,
    DOT,
    SEMICOLON,
    PLUS,
    MINUS,
    TIMES,
    DIVIDE
};

class Token {
public:
    Token(TokenType type, std::string lexeme, TextPosition text_position) : type(type), lexeme(lexeme), text_position(TextPosition(text_position.line, text_position.column - lexeme.length())) {}
    static std::string get_type_as_string(TokenType token_type);
    std::string get_type_as_string() const;
    const TokenType& get_type() const;
    const std::string& get_lexeme() const;
    const TextPosition& get_text_position() const;
    std::string to_string() const;
private:
    TokenType type;
    std::string lexeme;
    TextPosition text_position;
};

#endif // TOKEN_HPP

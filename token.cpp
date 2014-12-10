#include "token.hpp"
#include <map>

std::string Token::get_type_as_string(TokenType token_type) {
    static std::map<TokenType, std::string> token_type_map = {
        { TokenType::IDENTIFIER,    "IDENTIFIER" },
        { TokenType::UNSIGNED_INT,  "UNSIGNED_INT"},
        { TokenType::FLOAT,         "FLOAT"},
        { TokenType::EQUALS,        "EQUALS"},
        { TokenType::LEFT_PAREN,    "LEFT_PAREN"},
        { TokenType::RIGHT_PAREN,   "RIGHT_PAREN"},
        { TokenType::LEFT_BRACKET,  "LEFT_BRACKET"},
        { TokenType::RIGHT_BRACKET, "RIGHT_BRACKET"},
        { TokenType::COMMA,         "COMMA"},
        { TokenType::COLON,         "COLON"},
        { TokenType::DOT,           "DOT"},
        { TokenType::SEMICOLON,     "SEMICOLON"},
        { TokenType::PLUS,          "PLUS"},
        { TokenType::MINUS,         "MINUS"},
        { TokenType::TIMES,         "TIMES"},
        { TokenType::DIVIDE,        "DIVIDE"}
    };
    return token_type_map[token_type];
}

std::string Token::get_type_as_string() const {
    return get_type_as_string(type);
}

const TokenType& Token::get_type() const {
    return type;
}

const std::string& Token::get_lexeme() const {
    return lexeme;
}

const TextPosition& Token::get_text_position() const {
    return text_position;
}

std::string Token::to_string() const {
    return "TokenType: <" + get_type_as_string() + ">, Lexeme: <" + get_lexeme() + ">";
}

#include "lexer.hpp"

std::vector<std::shared_ptr<Token>> Lexer::tokenize() {
    std::shared_ptr<Token> token;
    while (token = get_token())
        tokens.push_back(token);
    return tokens;
}

bool Lexer::read_if(MatcherFunction matcher, std::string& lexeme) {
    bool is_match = false;
    if (input.good()) {
        char ch;
        input.get(ch);
        is_match = matcher(ch);
        if (is_match) {
            lexeme += ch;
            if (ch == '\n') {
                text_position.line++;
                text_position.column = 1;
            }
            else
                text_position.column++;
        }
        else
            input.unget();
    }
    return is_match;
}

void Lexer::read_while(MatcherFunction matcher, std::string& lexeme) {
    while (read_if(matcher, lexeme));
}

void Lexer::skip_spaces() {
    std::string lexeme;
    read_while(MatcherFunctionBuilder::is_space(), lexeme);
}


std::shared_ptr<Token> Lexer::read_float() {
    /*std::string lexeme;
    read_while(MatcherFunctionBuilder::is_digit(), lexeme);
    if (!lexeme.empty())
        return std::make_shared<Token>(TokenType::FLOAT, lexeme);*/
    return nullptr;
}

std::shared_ptr<Token> Lexer::read_unsigned_int() {
    std::string lexeme;
    read_while(MatcherFunctionBuilder::is_digit(), lexeme);
    if (!lexeme.empty())
        return std::make_shared<Token>(TokenType::UNSIGNED_INT, lexeme, text_position);
    return nullptr;
}

std::shared_ptr<Token> Lexer::read_identifier() {
    std::string lexeme;
    if (read_if(MatcherFunctionBuilder::is_id_prefix(), lexeme)) {
        read_while(MatcherFunctionBuilder::is_id_suffix(), lexeme);
        if (!lexeme.empty())
            return std::make_shared<Token>(TokenType::IDENTIFIER, lexeme, text_position);
    }
    return nullptr;
}

std::shared_ptr<Token> Lexer::read_symbols() {
    std::string lexeme;
    if (read_if(MatcherFunctionBuilder::is_char('='), lexeme))
        return std::make_shared<Token>(TokenType::EQUALS, lexeme, text_position);
    else if (read_if(MatcherFunctionBuilder::is_char('('), lexeme))
        return std::make_shared<Token>(TokenType::LEFT_PAREN, lexeme, text_position);
    else if (read_if(MatcherFunctionBuilder::is_char(')'), lexeme))
        return std::make_shared<Token>(TokenType::RIGHT_PAREN, lexeme, text_position);
    else if (read_if(MatcherFunctionBuilder::is_char('{'), lexeme))
        return std::make_shared<Token>(TokenType::LEFT_BRACKET, lexeme, text_position);
    else if (read_if(MatcherFunctionBuilder::is_char('}'), lexeme))
        return std::make_shared<Token>(TokenType::RIGHT_BRACKET, lexeme, text_position);
    else if (read_if(MatcherFunctionBuilder::is_char(','), lexeme))
        return std::make_shared<Token>(TokenType::COMMA, lexeme, text_position);
    else if (read_if(MatcherFunctionBuilder::is_char(':'), lexeme))
        return std::make_shared<Token>(TokenType::COLON, lexeme, text_position);
    else if (read_if(MatcherFunctionBuilder::is_char('.'), lexeme))
        return std::make_shared<Token>(TokenType::DOT, lexeme, text_position);
    else if (read_if(MatcherFunctionBuilder::is_char(';'), lexeme))
        return std::make_shared<Token>(TokenType::SEMICOLON, lexeme, text_position);
    else if (read_if(MatcherFunctionBuilder::is_char('+'), lexeme))
        return std::make_shared<Token>(TokenType::PLUS, lexeme, text_position);
    else if (read_if(MatcherFunctionBuilder::is_char('-'), lexeme))
        return std::make_shared<Token>(TokenType::MINUS, lexeme, text_position);
    else if (read_if(MatcherFunctionBuilder::is_char('*'), lexeme))
        return std::make_shared<Token>(TokenType::TIMES, lexeme, text_position);
    else if (read_if(MatcherFunctionBuilder::is_char('/'), lexeme))
        return std::make_shared<Token>(TokenType::DIVIDE, lexeme, text_position);
    return nullptr;
}

std::shared_ptr<Token> Lexer::get_token() {
    std::shared_ptr<Token> token = nullptr;
    skip_spaces();
    token = read_symbols();
    if (!token)
        token = read_float();
    if (!token)
        token = read_unsigned_int();
    if (!token)
        token = read_identifier();
    return token;
}

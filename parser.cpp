#include "parser.hpp"

std::shared_ptr<ASTNode> Parser::parse() {
    tokens = lexer.tokenize();
    lookahead = get_token();
    std::shared_ptr<ASTNode> node = program();
    if (!tokens.empty())
        report_error("Syntax error. There are remaining text not parsed!");
    return node;
}

void Parser::report_error(const std::string& message) {
    std::cerr << message << std::endl;
    exit(EXIT_FAILURE);
}

std::shared_ptr<Token> Parser::get_token() {
    if (!tokens.empty()) {
        std::shared_ptr<Token> token = tokens.front();
        tokens.erase(tokens.begin());
        return token;
    }
    return nullptr;
}

bool Parser::is_match(TokenType expected_type) const {
    return lookahead && (lookahead->get_type() == expected_type);
}

void Parser::match(TokenType expected_type) {
    if (is_match(expected_type))
        lookahead = get_token();
    else
        report_error(lookahead->get_text_position().to_string() + " Syntax error. Expected <" + Token::get_type_as_string(expected_type) + "> but got <" + lookahead->get_type_as_string() + ">");
}

std::shared_ptr<ASTNode> Parser::program() {
    std::shared_ptr<ASTExpressionListNode> node = std::make_shared<ASTExpressionListNode>();

    node->add_node(expression());
    while (is_match(TokenType::SEMICOLON)) {
        match(TokenType::SEMICOLON);
        node->add_node(expression());
    }

    return node;
}

std::shared_ptr<ASTNode> Parser::expression() {
    bool is_negate;
    std::shared_ptr<ASTNode> node, term_expr;

    is_negate = is_match(TokenType::MINUS);
    if (is_negate)
        match(TokenType::MINUS);
    term_expr = term();
    if (is_negate)
        node = std::make_shared<ASTNegateNode>(term_expr);
    else
        node = term_expr;
    while (is_match(TokenType::PLUS) || is_match(TokenType::MINUS)) {
        TokenType token_type = lookahead->get_type();
        match(token_type);
        term_expr = term();
        if (token_type == TokenType::PLUS)
            node = std::make_shared<ASTAddNode>(node, term_expr);
        else
            node = std::make_shared<ASTSubtractNode>(node, term_expr);
    }

    return node;
}

std::shared_ptr<ASTNode> Parser::term() {
    std::shared_ptr<ASTNode> node, factor_expr;

    node = factor();
    while (is_match(TokenType::TIMES) || is_match(TokenType::DIVIDE)) {
        TokenType token_type = lookahead->get_type();
        match(token_type);
        factor_expr = factor();
        if (token_type == TokenType::TIMES)
            node = std::make_shared<ASTMultiplyNode>(node, factor_expr);
        else
            node = std::make_shared<ASTDivideNode>(node, factor_expr);
    }

    return node;
}

std::shared_ptr<ASTNode> Parser::factor() {
    std::shared_ptr<ASTNode> node;

    switch (lookahead->get_type()) {
        case TokenType::UNSIGNED_INT: {
            node = std::make_shared<ASTDoubleNode>(lookahead->get_lexeme());
            match(TokenType::UNSIGNED_INT);
            break;
        }
        case TokenType::IDENTIFIER: {
            std::string variable_name = lookahead->get_lexeme();
            match(TokenType::IDENTIFIER);
            if (is_match(TokenType::EQUALS)) {
                match(TokenType::EQUALS);
                node = std::make_shared<ASTAssignmentNode>(variable_name, expression());
            }
            else
                node = std::make_shared<ASTIdentifierNode>(variable_name);
            break;
        }
        default: {
            match(TokenType::LEFT_PAREN);
            node = std::make_shared<ASTParenthesizedExpressionNode>(expression());
            match(TokenType::RIGHT_PAREN);
        }
    }

    return node;
}

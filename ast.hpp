#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <vector>
#include "object.hpp"

enum class ASTNodeType {
    VALUE,
    IDENTIFIER,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    NEGATE,
    PARENTHESIZED_EXPRESSION,
    ASSIGNMENT,
    EXPRESSION_LIST
};

class ASTNode {
public:
    ASTNode(ASTNodeType node_type) : node_type(node_type) {}
    ASTNodeType get_node_type() const;virtual std::string to_string() const = 0;
private:
    ASTNodeType node_type;
};

class ASTNodeList : public ASTNode {
public:
    ASTNodeList(ASTNodeType node_type) : ASTNode(node_type) {}
    void add_node(std::shared_ptr<ASTNode> node);
    const std::vector<std::shared_ptr<ASTNode>>& get_nodes() const;
protected:
    std::vector<std::shared_ptr<ASTNode>> nodes;
};

class ASTExpressionListNode : public ASTNodeList {
public:
    ASTExpressionListNode() : ASTNodeList(ASTNodeType::EXPRESSION_LIST) {}
    std::string to_string() const override;
};

class ASTDoubleNode : public ASTNode {
public:
    ASTDoubleNode(double value) : ASTNode(ASTNodeType::VALUE), value(std::make_shared<Double>(value)) {}
    ASTDoubleNode(std::string value) : ASTDoubleNode(std::stod(value)) {}
    std::string to_string() const override;
    std::shared_ptr<Double> get_value() const;
protected:
    std::shared_ptr<Double> value;
};

class ASTIdentifierNode : public ASTNode {
public:
    ASTIdentifierNode(std::string identifier) : ASTNode(ASTNodeType::IDENTIFIER), identifier(identifier) {}
    std::string to_string() const override;
    const std::string& get_identifier() const;
protected:
    std::string identifier;
};

class ASTUnaryNode : public ASTNode {
public:
    ASTUnaryNode(ASTNodeType node_type, std::shared_ptr<ASTNode> node) : ASTNode(node_type), node(node) {}
    std::shared_ptr<ASTNode> get_node() const;
protected:
    std::shared_ptr<ASTNode> node;
};

class ASTBinaryNode : public ASTNode {
public:
    ASTBinaryNode(ASTNodeType node_type, std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right) : ASTNode(node_type), left(left), right(right) {}
    std::shared_ptr<ASTNode> get_left() const;
    std::shared_ptr<ASTNode> get_right() const;
protected:
    std::shared_ptr<ASTNode> left;
    std::shared_ptr<ASTNode> right;
};

class ASTParenthesizedExpressionNode : public ASTUnaryNode {
public:
    ASTParenthesizedExpressionNode(std::shared_ptr<ASTNode> node) : ASTUnaryNode(ASTNodeType::PARENTHESIZED_EXPRESSION, node) {}
    std::string to_string() const override;
};

class ASTNegateNode : public ASTUnaryNode {
public:
    ASTNegateNode(std::shared_ptr<ASTNode> node) : ASTUnaryNode(ASTNodeType::NEGATE, node) {}
    std::string to_string() const override;
};

class ASTAddNode : public ASTBinaryNode {
public:
    ASTAddNode(std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right) : ASTBinaryNode(ASTNodeType::ADD, left, right) {}
    std::string to_string() const override;
};

class ASTSubtractNode : public ASTBinaryNode {
public:
    ASTSubtractNode(std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right) : ASTBinaryNode(ASTNodeType::SUBTRACT, left, right) {}
    std::string to_string() const override;
};

class ASTMultiplyNode : public ASTBinaryNode {
public:
    ASTMultiplyNode(std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right) : ASTBinaryNode(ASTNodeType::MULTIPLY, left, right) {}
    std::string to_string() const override;
};

class ASTDivideNode : public ASTBinaryNode {
public:
    ASTDivideNode(std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right) : ASTBinaryNode(ASTNodeType::DIVIDE, left, right) {}
    std::string to_string() const override;
};

class ASTAssignmentNode : public ASTNode {
public:
    ASTAssignmentNode(std::string variable_name, std::shared_ptr<ASTNode> expression) : ASTNode(ASTNodeType::ASSIGNMENT), variable_name(variable_name), expression(expression) {}
    std::string to_string() const override;
    const std::string& get_variable_name();
    const std::shared_ptr<ASTNode>& get_expression();
private:
    std::string variable_name;
    std::shared_ptr<ASTNode> expression;
};

#endif // AST_HPP

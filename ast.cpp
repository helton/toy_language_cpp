#include "ast.hpp"

ASTNodeType ASTNode::get_node_type() const {
    return node_type;
}

void ASTNodeList::add_node(std::shared_ptr<ASTNode> node) {
    nodes.push_back(node);
}

const std::vector<std::shared_ptr<ASTNode>>& ASTNodeList::get_nodes() const {
    return nodes;
}

std::string ASTExpressionListNode::to_string() const {
    std::string str;
    for (std::shared_ptr<ASTNode> node : nodes)
        str += (str.empty() ? "" : ";\n") + node->to_string();
    return str;
}

std::string ASTDoubleNode::to_string() const {
    return std::to_string(value->get_value());
}

std::shared_ptr<Double> ASTDoubleNode::get_value() const {
    return value;
}

std::string ASTIdentifierNode::to_string() const {
    return identifier;
}

const std::string& ASTIdentifierNode::get_identifier() const {
    return identifier;
}

std::shared_ptr<ASTNode> ASTUnaryNode::get_node() const {
    return node;
}

std::shared_ptr<ASTNode> ASTBinaryNode::get_left() const {
    return left;
}

std::shared_ptr<ASTNode> ASTBinaryNode::get_right() const {
    return right;
}

std::string ASTParenthesizedExpressionNode::to_string() const {
    return "(" + node->to_string() + ")";
}

std::string ASTNegateNode::to_string() const {
    return "-" + node->to_string();
}

std::string ASTAddNode::to_string() const {
    return left->to_string() + " + " + right->to_string();
}

std::string ASTSubtractNode::to_string() const {
    return left->to_string() + " - " + right->to_string();
}

std::string ASTMultiplyNode::to_string() const {
    return left->to_string() + " * " + right->to_string();
}

std::string ASTDivideNode::to_string() const {
    return left->to_string() + " / " + right->to_string();
}

std::string ASTAssignmentNode::to_string() const {
    return variable_name + " = " + expression->to_string();
}

const std::string& ASTAssignmentNode::get_variable_name() {
    return variable_name;
}

const std::shared_ptr<ASTNode>& ASTAssignmentNode::get_expression() {
    return expression;
}

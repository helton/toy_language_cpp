#include "interpreter.hpp"
#include <memory>

std::shared_ptr<Object> Interpreter::evaluate(std::shared_ptr<ASTNode> tree) {
    switch(tree->get_node_type()) {
        case ASTNodeType::VALUE: {
            std::shared_ptr<ASTDoubleNode> node = std::static_pointer_cast<ASTDoubleNode>(tree);
            return node->get_value();
        }
        case ASTNodeType::IDENTIFIER: {
            std::shared_ptr<ASTIdentifierNode> node = std::static_pointer_cast<ASTIdentifierNode>(tree);
            return memory.get_value(node->get_identifier());
        }
        case ASTNodeType::ADD: {
            std::shared_ptr<ASTAddNode> node = std::static_pointer_cast<ASTAddNode>(tree);
            std::shared_ptr<Double> left_object = std::static_pointer_cast<Double>(evaluate(node->get_left()));
            std::shared_ptr<Double> right_object = std::static_pointer_cast<Double>(evaluate(node->get_right()));
            double left_value = left_object->get_value();
            double right_value = right_object->get_value();
            return std::make_shared<Double>(left_value + right_value);
        }
        case ASTNodeType::SUBTRACT: {
            std::shared_ptr<ASTSubtractNode> node = std::static_pointer_cast<ASTSubtractNode>(tree);
            std::shared_ptr<Double> left_object = std::static_pointer_cast<Double>(evaluate(node->get_left()));
            std::shared_ptr<Double> right_object = std::static_pointer_cast<Double>(evaluate(node->get_right()));
            double left_value = left_object->get_value();
            double right_value = right_object->get_value();
            return std::make_shared<Double>(left_value - right_value);
        }
        case ASTNodeType::MULTIPLY: {
            std::shared_ptr<ASTMultiplyNode> node = std::static_pointer_cast<ASTMultiplyNode>(tree);
            std::shared_ptr<Double> left_object = std::static_pointer_cast<Double>(evaluate(node->get_left()));
            std::shared_ptr<Double> right_object = std::static_pointer_cast<Double>(evaluate(node->get_right()));
            double left_value = left_object->get_value();
            double right_value = right_object->get_value();
            return std::make_shared<Double>(left_value * right_value);
        }
        case ASTNodeType::DIVIDE: {
            std::shared_ptr<ASTDivideNode> node = std::static_pointer_cast<ASTDivideNode>(tree);
            std::shared_ptr<Double> left_object = std::static_pointer_cast<Double>(evaluate(node->get_left()));
            std::shared_ptr<Double> right_object = std::static_pointer_cast<Double>(evaluate(node->get_right()));
            double left_value = left_object->get_value();
            double right_value = right_object->get_value();
            return std::make_shared<Double>(left_value / right_value);
        }
        case ASTNodeType::NEGATE: {
            std::shared_ptr<ASTNegateNode> node = std::static_pointer_cast<ASTNegateNode>(tree);
            std::shared_ptr<Double> object = std::static_pointer_cast<Double>(evaluate(node->get_node()));
            return std::make_shared<Double>(-object->get_value());
        }
        case ASTNodeType::PARENTHESIZED_EXPRESSION: {
            std::shared_ptr<ASTParenthesizedExpressionNode> node = std::static_pointer_cast<ASTParenthesizedExpressionNode>(tree);
            std::shared_ptr<Double> object = std::static_pointer_cast<Double>(evaluate(node->get_node()));
            return std::make_shared<Double>(object->get_value());
        }
        case ASTNodeType::ASSIGNMENT: {
            std::shared_ptr<ASTAssignmentNode> node = std::static_pointer_cast<ASTAssignmentNode>(tree);
            std::shared_ptr<Double> object = std::static_pointer_cast<Double>(evaluate(node->get_expression()));
            memory.store_value(node->get_variable_name(), object);
            return std::make_shared<Double>(object->get_value());
        }
        case ASTNodeType::EXPRESSION_LIST: {
            std::shared_ptr<ASTExpressionListNode> node = std::static_pointer_cast<ASTExpressionListNode>(tree);
            std::shared_ptr<Double> object;
            for (std::shared_ptr<ASTNode> n : node->get_nodes())
                object = std::static_pointer_cast<Double>(evaluate(n));
            return std::make_shared<Double>(object->get_value());
        }
    }
    return 0;
}

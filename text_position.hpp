#ifndef TEXT_POSITION_HPP
#define TEXT_POSITION_HPP

#include <string>

struct TextPosition {
    int line;
    int column;

    TextPosition(int line, int column) : line(line), column(column) {}
    TextPosition() : TextPosition(1, 1) {}

    std::string to_string() const {
        return "[Line: " + std::to_string(line) + ", Column: " + std::to_string(column) + "]";
    }
};

#endif // TEXT_POSITION_HPP

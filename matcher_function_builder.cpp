#include "matcher_function_builder.hpp"
#include <cctype>

MatcherFunction MatcherFunctionBuilder::is_char(char expected_char) {
    return [=](char& ch) -> bool { return ch == expected_char; };
}

MatcherFunction MatcherFunctionBuilder::is_not_char(char unexpected_char) {
    return [=](char& ch) -> bool { return ch != unexpected_char; };
}

MatcherFunction MatcherFunctionBuilder::is_alpha() {
    return [](char& ch) -> bool { return isalpha(ch); };
}

MatcherFunction MatcherFunctionBuilder::is_digit() {
    return [](char& ch) -> bool { return isdigit(ch); };
}

MatcherFunction MatcherFunctionBuilder::is_alnum() {
    return [](char& ch) -> bool { return isalnum(ch); };
}

MatcherFunction MatcherFunctionBuilder::is_space() {
    return [](char& ch) -> bool { return isspace(ch); };
}

MatcherFunction MatcherFunctionBuilder::is_id_prefix() {
    return MatcherFunctionBuilder::make_or(
        MatcherFunctionBuilder::is_alpha(),
        MatcherFunctionBuilder::is_char('_')
    );
}

MatcherFunction MatcherFunctionBuilder::is_id_suffix() {
    return MatcherFunctionBuilder::make_or(
        MatcherFunctionBuilder::is_alnum(),
        MatcherFunctionBuilder::is_char('_')
    );
}

MatcherFunction MatcherFunctionBuilder::make_or(MatcherFunction func1, MatcherFunction func2) {
    return [=](char& ch) -> bool { return (func1(ch) || func2(ch)); };
}

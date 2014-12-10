#ifndef MATCHER_FUNCTION_BUILDER_HPP
#define MATCHER_FUNCTION_BUILDER_HPP

#include <functional>

typedef std::function<bool(char&)> MatcherFunction;

class MatcherFunctionBuilder {
public:
    static MatcherFunction is_char(char expected_char);
    static MatcherFunction is_not_char(char unexpected_char);
    static MatcherFunction is_alpha();
    static MatcherFunction is_digit();
    static MatcherFunction is_alnum();
    static MatcherFunction is_space();
    static MatcherFunction is_id_prefix();
    static MatcherFunction is_id_suffix();
private:
    static MatcherFunction make_or(MatcherFunction func1, MatcherFunction func2);
};

#endif // MATCHER_FUNCTION_BUILDER_HPP

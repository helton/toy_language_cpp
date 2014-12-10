#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

class Object {
public:
    virtual std::string to_string() const  = 0;
};

template<typename T>
class Value : public Object {
public:
    Value(const T& value) : value(value) {}
    const T& get_value() const {
        return value;
    }
    std::string to_string() const override {
        return std::to_string(value);
    };
protected:
    T value;
};

class Boolean : public Value<bool> {
public:
    Boolean(bool value) : Value(value) {}
};

class Double : public Value<double> {
public:
    Double(double value) : Value(value) {}
};

#endif // OBJECT_HPP_INCLUDED

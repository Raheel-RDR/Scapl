#pragma once

#include "variable.h"
#include "integerArrayVariable.h"

class IntegerArrayVariableWithLiteralIndex : public Variable
{
    Variable* array_variable;
    int index;
public:
    IntegerArrayVariableWithLiteralIndex(Variable* av, int i) : array_variable{ av }, index{ i }
    {
        std::stringstream ss;
        ss << "$" << array_variable->get_name() << "+" << index;
        variable_name = ss.str();
    }
    Variable* get_array_variable() { return array_variable; }
    size_t get_index() const { return index; }
    int get_value() const override { return ((IntegerArrayVariable*)array_variable)->get_array_value(index); }
    void set_value(int i) override { ((IntegerArrayVariable*)array_variable)->set_array_value(index, i); }
    void print(char last) override { std::cout << get_value() << last << "\n"; }
};

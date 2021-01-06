#pragma once

#include "variable.h"
#include "integerArrayVariable.h"

class IntegerArrayVariableWithVariableIndex : public Variable
{
    Variable* array_variable;
    Variable* index_variable;
public:
    IntegerArrayVariableWithVariableIndex(Variable* av, Variable* iv) :
        array_variable{av}, index_variable{iv}
    {
        std::stringstream ss;
        ss << "$" << array_variable->get_name() << "+" << index_variable->get_name();
        variable_name = ss.str();
    }
    Variable* get_array_variable() { return array_variable; }
    Variable* get_index_variable() { return index_variable; }
    int get_value() const override { return ((IntegerArrayVariable*)array_variable)->get_array_value(index_variable->get_value()); }
    void set_value(int i) override { ((IntegerArrayVariable*)array_variable)->set_array_value(index_variable->get_value(), i);}
    void print(char last) override { std::cout << get_value() << last << "\n"; }
};

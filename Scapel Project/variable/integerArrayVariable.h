#pragma once
#include "variable.h"

class IntegerArrayVariable : public Variable
{
    int* values;
    int array_size;
public:
    IntegerArrayVariable(const std::string& name, int count)
    {
        variable_name = name;
        if (count < 1)
        {
            count = 1;
        }
        array_size = count;
        values = new int[array_size];
        for (int i = 0; i < array_size; i++)
        {
            values[i] = 0;
        }
    }
    int get_value() const override { return 0; }
    int get_array_value(int index) const { return ((0 <= index && index < array_size) ? values[index] : 0); }
    void set_value(int i) override {}
    void set_array_value(int index, int i) { if (0 <= index && index < array_size) { values[index] = i; } }
    void print(char last) override
    {
        std::cout << values[0];
        for (int i = 1; i < array_size; i++)
        {
            std::cout << "," << values[i];
        }
        std::cout << last << "\n";
    }
};

#pragma once
#include "variable.h"

class IntegerVariable : public Variable
{
	int value{ 0 };
public:
	IntegerVariable(const std::string& name)
	{
		variable_name = name;
	}
	int get_value() const override { return value; }
	void set_value(int i) override { value = i; }
	void print(char last) override { std::cout << value << last << "\n"; }
};

#pragma once
#include "variable.h"

class LiteralInteger : public Variable
{
	int value{ 0 };
public:
	LiteralInteger(int v) : value{ v }
	{
		std::stringstream ss;
		ss << v;
		variable_name = ss.str();
	}
	int get_value() const override { return value; }
	void set_value(int i) override {}
	void print(char last) override { std::cout << value << last << "\n"; }
};

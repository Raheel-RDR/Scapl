#pragma once
#include "variable.h"

class LiteralText : public Variable
{
	std::string text;
public:
	LiteralText(const std::string& t) : text{ t }
	{
		std::stringstream ss;
		ss << t;
		variable_name = ss.str();
	}
	int get_value() const override { return 0; }
	void set_value(int i) override {}
	void print(char last) override { std::cout << text << last << "\n"; }
};

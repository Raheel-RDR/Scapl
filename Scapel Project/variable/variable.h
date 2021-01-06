#pragma once
#include <iostream>
#include <string>
#include <sstream>

class Variable
{
protected:
	std::string variable_name;
public:
	Variable() {}
	virtual ~Variable() {}

	std::string get_name() const { return variable_name; }
	virtual int get_value() const = 0;
	virtual void set_value(int v) = 0;
	virtual void print(char last) = 0;
};


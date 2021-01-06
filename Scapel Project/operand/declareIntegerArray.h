#pragma once
#include "operand.h"

class DeclareIntegerArray : public Operand
{
	IntegerArrayVariable* variable;
	std::string size;
public:
	DeclareIntegerArray(){}
	DeclareIntegerArray(IntegerArrayVariable* v) : variable{ v } {}


	bool compile(const std::string& line, Program* p) override;
	std::string operandName() const override { return "dca"; }
	QJsonObject arguments() const override {
		QJsonObject jsonObj;
		jsonObj["arg1"] = QString::fromStdString(variable->get_name());
		jsonObj["arg2"] = QString::fromStdString(size);
		return jsonObj;
	}
	void print_debug_info() const override { std::cout << variable->get_name(); }
};

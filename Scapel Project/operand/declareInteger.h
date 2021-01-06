#pragma once
#include "operand.h"

class DeclareInteger : public Operand
{
	IntegerVariable* variable;
public:
	DeclareInteger(){}
	DeclareInteger(IntegerVariable* v) : variable{ v } {}


	bool compile(const std::string& line, Program* p) override;
	std::string operandName() const override { return "dci"; }
	QJsonObject arguments() const override {
		QJsonObject jsonObj;
		jsonObj["arg1"] = QString::fromStdString(variable->get_name());
		jsonObj["arg2"] = "";
		return jsonObj;
	}
	void print_debug_info() const override { std::cout << variable->get_name(); }
};

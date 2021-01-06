#pragma once
#include "operand.h"

class PrintVariable : public Operand
{
	Variable* variable;
public:
	PrintVariable(Variable* v) : variable{ v } {}
	PrintVariable(){}

	int execute(int current_step, Program&) override
	{
		variable->print(' ');
		return ++current_step;
	}
	bool compile(const std::string& line, Program* p) override;
	std::string operandName() const override { return "prt"; }
	QJsonObject arguments() const override {
		QJsonObject jsonObj;
		jsonObj["arg1"] = QString::fromStdString(variable->get_name());
		jsonObj["arg2"] = "";
		return jsonObj;
	}
	void print_debug_info() const override { std::cout << variable->get_name(); }
};

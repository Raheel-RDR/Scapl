#pragma once
#include "operand.h"
#include "rundialog.h"

class ReadVariable : public Operand
{
	Variable* variable;
public:
	ReadVariable(Variable* v) : variable{v} {}
	ReadVariable(){}

	int execute(int current_step, Program&) override
	{
		std::cout << "Enter an integer: ";
		int temp;
		std::cin >> temp;
		variable->set_value(temp);
		return ++current_step;
	}
	bool compile(const std::string& line, Program* p) override;
	std::string operandName() const override { return "rdi"; }
	QJsonObject arguments() const override {
		QJsonObject jsonObj;
		jsonObj["arg1"] = QString::fromStdString(variable->get_name());
		jsonObj["arg2"] = "";
		return jsonObj;
	}
	void print_debug_info() const override { std::cout << variable->get_name(); }
};

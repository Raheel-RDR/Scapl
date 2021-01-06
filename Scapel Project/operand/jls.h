#pragma once
#include "operand.h"

class Jls : public Operand
{
	std::string label;
public:
	Jls(const std::string l) : label{ l } {}
	Jls(){}

	int execute(int current_step, Program& p) override;
	bool compile(const std::string& line, Program* p) override;
	std::string operandName() const override { return "jls"; }
	QJsonObject arguments() const override {
		QJsonObject jsonObj;
		jsonObj["arg1"] = QString::fromStdString(label);
		jsonObj["arg2"] = "";
		return jsonObj;
	}
	void print_debug_info() const override { std::cout << label; }
};

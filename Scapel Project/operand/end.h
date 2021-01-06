#pragma once
#include "operand.h"

class End : public Operand
{
public:
	End() {}
	int execute(int current_step, Program& p) override
	{
		return -1;
	}
	bool compile(const std::string& line, Program* p) override { return true; }
	std::string operandName() const override { return "end"; }
	QJsonObject arguments() const override {
		QJsonObject jsonObj;
		jsonObj["arg1"] = "";
		jsonObj["arg2"] = "";
		return jsonObj;
	}
	void print_debug_info() const override { std::cout << "END"; }
};

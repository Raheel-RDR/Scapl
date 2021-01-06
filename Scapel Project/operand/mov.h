#pragma once
#include "operand.h"

class Mov : public Operand
{
	Variable* source;
	Variable* dest;
public:
	Mov(Variable* s, Variable* d) : source{ s }, dest{ d } {}
	Mov(){};
	int execute(int current_step, Program& p) override;
	bool compile(const std::string& line, Program* p) override;
	std::string operandName() const override { return "mov"; }
	QJsonObject arguments() const override {
		QJsonObject jsonObj;
		jsonObj["arg1"] =  QString::fromStdString(source->get_name());
		jsonObj["arg2"] =  QString::fromStdString(dest->get_name());
		return jsonObj;
	}
	void print_debug_info() const override { std::cout << source->get_name() << "," << dest->get_name(); }
};

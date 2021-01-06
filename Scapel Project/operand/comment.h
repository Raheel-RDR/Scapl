#pragma once
#include "operand.h"

class Comment : public Operand
{
	std::string comment;
public:
	Comment(const std::string& c) : comment{ c } {}
	std::string operandName() const override { return "#"; }
	bool compile(const std::string& line, Program* p) override { return true; }
	QJsonObject arguments() const override {
		QJsonObject jsonObj;
		jsonObj["arg1"] =  QString::fromStdString(comment);
		jsonObj["arg2"] = "";
		return jsonObj;
	}
	void print_debug_info() const override { std::cout << comment; }
};

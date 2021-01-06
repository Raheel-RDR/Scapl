#pragma once
#include <string>
#include <iostream>
#include <QJsonObject>
#include "variable/variable.h"
#include "variable/integerVariable.h"
#include "variable/integerArrayVariable.h"
#include "variable/integerArrayVariableWithVariableIndex.h"
#include "variable/intergerArrayVariableWithLiteralIndex.h"
#include "program/program.h"

class Program;
class Operand
{
public:
	Operand(){}
	virtual ~Operand();

	virtual int execute(int current_step, Program&) { return ++current_step; }
	virtual bool compile(const std::string& line, Program* p) { return true; }
	virtual std::string operandName() const = 0;
	virtual QJsonObject arguments() const = 0;
	virtual void print_debug_info() const = 0;

protected:
	bool parse_left_right(const std::string& line, std::string& left, std::string& right);
	Variable* parse_source_or_dest(const std::string& line, Program* p);
	Variable* parse_source_or_dest_array(const std::string& line, Program* p);
	Variable* parse_source_or_dest_text(const std::string& line);
	Variable* parse_source_or_dest_literal(const std::string& line);
	Variable* parse_source_or_dest_variable(const std::string& line, Program* p);
};

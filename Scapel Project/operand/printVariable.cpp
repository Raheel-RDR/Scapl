#include "printVariable.h"

bool PrintVariable::compile(const std::string& line, Program* p)
{
	auto variable = parse_source_or_dest(line, p);
  this->variable = variable;
  return true;
}

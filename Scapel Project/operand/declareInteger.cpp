#include "declareInteger.h"

bool DeclareInteger::compile(const std::string& line, Program* p)
{
	  IntegerVariable* v = new IntegerVariable(line);
    this->variable = v;
		p->add_integer_variable(v->get_name(), v);
    return true;
}

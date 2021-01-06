#include "jeq.h"

int Jeq::execute(int current_step, Program& p)
{
	if (p.last_comparison == 0)
	{
		return p.get_label_iterator(label);
	}
	return ++current_step;
}

bool Jeq::compile(const std::string& line, Program* p)
{
	this->label = line;
  return true;
}

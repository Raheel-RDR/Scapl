#include "jmp.h"

int Jmp::execute(int current_step, Program& p)
{
	return p.get_label_iterator(label);
}

bool Jmp::compile(const std::string& line, Program* p)
{
	this->label = line;
  return true;
}

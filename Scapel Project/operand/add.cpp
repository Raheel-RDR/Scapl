#include "add.h"
#include "./program/program.h"

int Add::execute(int current_step, Program& p)
{
    int temp = dest->get_value();
    temp += source->get_value();
    dest->set_value(temp);
	return ++current_step;
}

bool Add::compile(const std::string& line, Program* p)
{
	std::string left, right;                               //create string variables left and right
	if (parse_left_right(line, left, right))               //check if parse_left_right successfu - this method will set left as the left variable and set right as the right variable
	{
    	this->source = parse_source_or_dest(left, p);           //set lvar as the left variable returned by parse_source_or_dest()
      this->dest = parse_source_or_dest(right, p);          //set rvar are the right variable returned by parse_source_or_dest()
			return true;
	}
	return false;
}

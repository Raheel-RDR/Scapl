#include "declareIntegerArray.h"
#include "./program/program.h"

extern void trim(std::string&);

bool DeclareIntegerArray::compile(const std::string& line, Program* p)
{
    std::string line_copy = line;
    int idx = line_copy.find(' ');
    if (idx != std::string::npos)
    {
        std::string left, right;                               //create string variables left and right
        parse_left_right(line, left, right);
        std::string name = left;
        line_copy = line_copy.substr(idx);
        trim(line_copy);
        this->size = right;
        size_t count = std::stoi(right);
        try
        {
            count = std::atoi(line_copy.c_str());
        }
        catch(...)
        { }
        if (0 < count)
        {
            IntegerArrayVariable*  v = new IntegerArrayVariable(name,count);
            this->variable = v;
            p->add_integer_variable(v->get_name(), v);
            return true;
        }
        return false;
    }
    return false;
}

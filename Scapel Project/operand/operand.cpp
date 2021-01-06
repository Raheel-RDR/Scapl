#include "operand.h"
#include "./program/program.h"

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

Operand::~Operand()
{
}

bool Operand::parse_left_right(const std::string& line, std::string& left, std::string& right)
{
    if (auto idx = line.find(' '); idx != std::string::npos)     //if line has a space in it (find index of ' ')
    {
        left = line.substr(0, idx);                             //set left to the substring of everything up until space
        trim(left);                                             //trim whitespace of left
        right = line.substr(idx + 1);                           //set right to the substring of characters after the space
        trim(right);                                            //trime whitespace of right
        return true;
    }
    return false;                                               //no space found return false
}

Variable* Operand::parse_source_or_dest(const std::string& line, Program* p)
{
    if (line[0] == '$')
    {
        return parse_source_or_dest_array(line.substr(1), p);
    }
    if (line[0] == '"')                                          //check if first character of input string is quotation mark '"'
    {
        return parse_source_or_dest_text(line.substr(1));       //parse text for everything after the first quotation mark
    }
    if ('-' == line[0] || ('0' <= line[0] && line[0] <= '9') )  //check if input string begins with - or 0-9
    {
        return parse_source_or_dest_literal(line);              //call parse_literal
    }
    return parse_source_or_dest_variable(line, p);                //if neither text nor literal then must be a variable and call parse_variable
}

Variable* Operand::parse_source_or_dest_text(const std::string& line)
{
    if (line[line.size() - 1] == '"')                         //check if the last character of input string is a quotation mark '"'
    {
        auto text = line.substr(0, line.size() - 1);         //remove quotation mark
        return new LiteralText(text);                       //return new LiteralText object
    }
    return nullptr;                                        //if last character is not a quotation mark return null (this means that there was no ending quotation mark)
}

Variable* Operand::parse_source_or_dest_literal(const std::string& line)
{
    int value = 0;
    try
    {
        value = std::atoi(line.c_str());                    //convert char to integer and store in value
    }
    catch (...)
    {
    }
    return new LiteralInteger(value);                     //pass variable to LiteralInteger constructor
}

Variable* Operand::parse_source_or_dest_variable(const std::string& line, Program* p)
{
    return p->get_integer_variable(line);

}

Variable* Operand::parse_source_or_dest_array(const std::string& line, Program* p)
{
    auto idx = line.find('+');
    if (idx != std::string::npos)
    {
        auto variable_name = line.substr(0,idx);
        auto variable = p->get_integer_variable(variable_name);
        if (variable)
        {
            auto index = line.substr(idx + 1);
            if ('-' == index[0] || ('0' <= index[0] && index[0] <= '9'))
            {
                int i = 0;
                try
                {
                    i = std::atoi(index.c_str());
                }
                catch (...)
                {
                }
                return new IntegerArrayVariableWithLiteralIndex(variable, i);
            }
            auto index_variable = p->get_integer_variable(index);
            if (index_variable)
            {
                return new IntegerArrayVariableWithVariableIndex(variable, index_variable);
            }
        }
    }
    return nullptr;
}

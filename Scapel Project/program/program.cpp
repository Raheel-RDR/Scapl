#include "program.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <locale>
#include <vector>

#include "./operand/operand.h"
#include "./operand/cmp.h"
#include "./operand/mov.h"
#include "./operand/add.h"
#include "./operand/comment.h"
#include "./operand/declareInteger.h"
#include "./operand/declareIntegerArray.h"
#include "./operand/end.h"
#include "./operand/jmp.h"
#include "./operand/jmr.h"
#include "./operand/jls.h"
#include "./operand/jeq.h"
#include "./operand/printVariable.h"
#include "./operand/readVariable.h"

#include "./serializer/serializer.h"

// trim from start (in place)
void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

Program::Program(){}
Program::~Program(){}

bool Program::compile(const std::string& program, const QString& directory)
{
    bool parsed = false;
    Serializer serializer(directory);

    if (program.size())
    {
        std::stringstream ss(program);
        std::string to;

        while (std::getline(ss, to, '\n'))
        {
            parsed =  parse(to, serializer);
            if (!parsed)
            {
                break;
            }
        }
    }
    return parsed;
}

bool Program::parse(const std::string& line, Serializer& serializer)
{
    auto rest_of_line = get_label(line);        //run get_label() to map the jumps and return the rest of line after label
    auto operand = get_operand(rest_of_line);   //run get_operand to return the operand object for the rest of the line
    if(is_error()) return false;
    std::string label = just_label(line);
    serializer.save_to_json(label, operand);           //add operand element at the end of the statements vector
    statements.push_back(operand);              //increment the current vector index
    current_vector_index++;
    return true;
}
std::string Program::just_label(const std::string& line)
{
    auto idx = line.find(":");                          //find index of ":"
    if (idx != std::string::npos)                       //if returned index is found
    {
        auto label = line.substr(0, idx);               //label is the substring before :
        trim(label);                                    //trim whitespace
        return label;
    }
    return "";
}

std::string Program::get_label(const std::string& line)
{
    auto idx = line.find(":");                          //find index of ":"
    if (idx != std::string::npos)                       //if returned index is found
    {
        auto label = line.substr(0, idx);               //label is the substring before :
        trim(label);                                    //trim whitespace

        jump_map.emplace(label, current_vector_index);  //add label to jump_map
        return line.substr(idx + 1);                    //the rest operation is everything after :
    }
    return line;
}

size_t Program::get_label_iterator(const std::string& label)
{
    if (auto idx = jump_map.find(label); idx != jump_map.end()) //search map for label
    {
        return idx->second;                                     //return label interator
    }
    return 0;                                                   //if not found return 0
}

bool Program::add_integer_variable(const std::string& name,Variable* variable)
{
    variable_map.emplace(name, variable);                       //add name, variable mapping to variable_map
    return true;
}

Variable* Program::get_integer_variable(const std::string& name) const
{
    if (auto idx = variable_map.find(name); idx != variable_map.end())  //search through variable_map for a variable that maps to given name
    {
        return idx->second;                                             //return variable that is mapped to name
    }
    return nullptr;                                                    // if variable is not associated with specified name return null pointer
}

Operand* Program::get_operand(const std::string& line)
{
    auto line_copy = line;                                           //create copy of line
    trim(line_copy);                                                //trim whitespace
    if (0 == line_copy.size())                                      //check if line is empty
    {
        return new Comment("blank line");
    }
    if( line[0] == '#') // Blank lines treated like comments       //check if line begins with '#' character indicating Comment
    {
        return new Comment(line.substr(1));                        //return a comment consisting of the rest of the line
    }
    auto op = line_copy;                                          //set variable op = line_copy
    auto idx = line_copy.find(' ');                               //find the index of the first occurence of a space ' '
    if (idx != std::string::npos)                                //check if there is a space
    {
        op = line_copy.substr(0, idx);                          //set op variable to equal to the substring of line up until space (operation)
        line_copy = line_copy.substr(idx);                      //set line_copy to be the rest of the line (excluding the operation)
        trim(line_copy);                                        //trim whitespace
    }
    if (op == "dci")                                            //check if op is dci
    {
        DeclareInteger* dci = new DeclareInteger();
        dci->compile(line_copy, this);
        return dci;
    }
     if (op == "dca")                                            //check if op is dci
    {
        DeclareIntegerArray* dca = new DeclareIntegerArray();
        dca->compile(line_copy, this);
        return dca;
    }
    if (op == "rdi")                                           //check if op is rdi
    {
      ReadVariable* rdi = new ReadVariable();
      rdi->compile(line_copy, this);
      return rdi;
    }
    if (op == "prt")                                           //check if op is prt
    {
        PrintVariable* prt = new PrintVariable();
        prt->compile(line_copy, this);
        return prt;
    }
    if (op == "cmp")                                           //check if op is cmp
    {
        Cmp* cmp = new Cmp();
        cmp->compile(line_copy, this);
        return cmp;                          //call parse_cmp with the rest of the line for arguments
    }
    if (op == "add")                                           //check if op is add
    {
        Add* add = new Add();
        add->compile(line_copy, this);
        return add;                          //call parse_cmp with the rest of the line for arguments
    }
    if (op == "mov")                                           //check if op is add
    {
        Mov* mov = new Mov();
        mov->compile(line_copy, this);
        return mov;                          //call parse_cmp with the rest of the line for arguments
    }
    if (op == "jmr")                                           //check if op is jmr
    {
        Jmr* jmr = new Jmr();
        jmr->compile(line_copy, this);
        return jmr;
    }
    if (op == "jls")                                           //check if op is jls
    {
        Jls* jls = new Jls();
        jls->compile(line_copy, this);
        return jls;
    }
    if (op == "jeq")                                           //check if op is jeq
    {
        Jeq* jeq = new Jeq();
        jeq->compile(line_copy, this);
        return jeq;
    }
    if (op == "jmp")                                           //check if op is jmp
    {
        Jmp* jmp = new Jmp();
        jmp->compile(line_copy, this);
        return jmp;
    }
    if (op == "end")                                           //check if op is end
    {
        return new End();                                      //return new End object
    }
    set_error();                                               //if failed to parse out a correct operand set error
    errors.push_back("Invalid operand found");                 //push invalid operand error
    return new Comment("no valid operand found");              //return a comment to user about error
}

Operand* Program::get_operand_from_json(const QJsonObject& statement)
{
    std::string operand = statement.value("Operand").toString().toUtf8().constData();
    std::string arg1 = statement.value("Arguments").toObject().value("arg1").toString().toUtf8().constData();
    std::string arg2 = statement.value("Arguments").toObject().value("arg2").toString().toUtf8().constData();

    std::string line = operand + " " + arg1 + " " + arg2;
    return get_operand(line);
}

void Program::start(const QString& file)
{
    current_vector_index = 0;                           //set the current_vector_index at 0
    Serializer serializer(file);
    serializer.load_from_json();

    foreach (const QJsonValue& statement, serializer.get_jsonArray()){
        auto operand = get_operand_from_json(statement.toObject());
        statements.push_back(operand);
        std::string label = statement.toObject().value("Label").toString().toUtf8().constData();
        jump_map.emplace(label, current_vector_index);
        current_vector_index++;
    }
    current_vector_index = 0;
    bool done = false;
    while (!done)
  	{
  		if (!execute_next())
  		{
  			done = true;
  		}
  	}
}

bool Program::execute_next()
{
    Operand* next = statements[current_vector_index];   //set pointer next to current vector index in statements vectors of operands

    if (debug_mode)
    {
        std::cout << "Execute " << next->operandName() << " ";
        next->print_debug_info();
        std::cout << "\n";
    }
    current_vector_index = next->execute(current_vector_index, *this); //execute operation
    if (debug_mode)
    {
        print_debug_info();
    }
    if (current_vector_index < 0)                                       //check if vector is less than 0 (overflow)
        return false;                                                   //didn't execute
    return true;                                                        //return true on execution
}

void Program::print_debug_info()
{
    std::cout << "Variable List:\n";
    for (auto& v : variable_map)
    {
        std::cout << "  " << v.first << " ={";
        v.second->print('}');
    }
    std::cout << "\n";
}

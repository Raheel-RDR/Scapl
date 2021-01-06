#ifndef PROGRAM_H
#define PROGRAM_H
#pragma once
#include <map>
#include <vector>
#include <QString>
#include <QJsonObject>

#include "./variable/variable.h"
#include "./variable/integerVariable.h"
#include "./variable/integerArrayVariable.h"
#include "./variable/literalInteger.h"
#include "./variable/literalText.h"

class Operand;
class Cmp;
class Comment;
class DeclareInteger;
class End;
class Jmp;
class Jmr;
class PrintVariable;
class ReadVariable;

class Serializer;

class Program
{
    std::vector<Operand*> statements;
    std::vector<std::string> errors;
    std::map<std::string, size_t> jump_map;
    std::map<std::string, Variable*> variable_map;
    int current_vector_index{ 0 };
    bool debug_mode{ false };
    bool error_found {false};
public:
    Program();
    ~Program();

    int last_comparison{ 0 };
    bool compile(const std::string& program, const QString& directory);
    std::string get_errors() const {
        std::string text;
        for (unsigned i=0; i<errors.size(); ++i) text  += errors[i] + '\n';
        return text;
    }
    void set_error() { error_found = true;  }
    bool is_error(){ return error_found; }
    size_t num_lines() const { return statements.size(); }
    size_t num_labels() const { return jump_map.size(); }
    size_t num_variables() const { return variable_map.size(); }
    size_t get_label_iterator(const std::string& label);
    bool add_integer_variable(const std::string& name, Variable* v);
    Variable* get_integer_variable(const std::string& name) const;
    void set_debug_mode() { debug_mode = true; }
    bool is_debug_mode() { return debug_mode; }

    void start(const QString& file);
    bool execute_next();

protected:
    void print_debug_info();
    bool parse(const std::string& line, Serializer& serializer);
    std::string get_label(const std::string& line);
    std::string just_label(const std::string& line);
    Operand* get_operand(const std::string& line);
    Operand* get_operand_from_json(const QJsonObject& statement);
};

#endif // PROGRAM_H

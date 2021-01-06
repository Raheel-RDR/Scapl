TO BUILD PROJECT USE COMMAND:
make

TO LAUNCH PROJECT USE COMMAND:
./textEditor

GANG OF FOUR DESIGN PATTERN - INTERPRETER:
We have used the interpreter design pattern. We have implemented the design
patten in the following classes:
Abstract base expression - Operand
Terminal Expression - All operand but JMPS
Non-Terminal Expressions - JMPS
Context - Variables
Client - RunDialog

Our Rundialog window creates a vector of operands to be executed through a
program and calls execute on the first one. This sets off a chain of Expressions
being executed until it has reached the end.

Once run is clicked you must provide a complete path of the json file then click enter, once enter is clicked the terminal will take input and show output to user. (json file is made when user clicks compile first and saves the json file in storage)

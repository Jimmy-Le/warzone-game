#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H

// Header to the CommandProcessing.cpp file
#include <iostream>
using std::cout;
using std::string;
#include <vector>
using std::vector;
// forward declaration
class CommandProcessor;
class Command;

//-----------------COMMAND PROCESSOR CLASS----------------//

class CommandProcessor
{
private:
    vector<Command *> *allCommands; // pointer to a vector of command pointers
    Command *readCommand();
    void saveCommand(Command *command);

public:
    CommandProcessor(); // default constructor
    // CommandProcessor();               // parameterized
    CommandProcessor(CommandProcessor &otherCommandProcessor); // copy constructor
    ~CommandProcessor();                                       // destructor
                                                               //  assignment operator
    CommandProcessor &operator=(const CommandProcessor &otherCommandProcessor);
    // stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const CommandProcessor &commandProcessorObject);
    void getCommand();
    bool validate(Command command);
};

//-----------------COMMAND CLASS----------------//

class Command
{
private:
    string *command;
    string *effect;

public:
    Command();                      // default constructor
    Command(Command &otherCommand); // copy constructor
    Command(string commandString);  // parameterized
    Command(string commandString, string effectString);
    ~Command();                                                                       // destructor
    Command &operator=(const Command &otherCommand);                                  // assignment operator
    friend std::ostream &operator<<(std::ostream &out, const Command &commandObject); // stream insertion operator
    void saveEffect();
};

#endif
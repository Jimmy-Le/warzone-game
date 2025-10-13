// For part 1 of assignment 2

#include "CommandProcessing.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
#include <vector>
using std::allocator;
using std::vector;

// forward declaration
class CommandProcessor;
class Command;

//-----------------COMMAND PROCESSOR CLASS----------------//

// gets a command from the console as a string
// calls validate on the command to check if it is valid in the current game state
// calls the save command method to save that command
void CommandProcessor::readCommand()
{
    cout << "Enter next command: " << endl; // prompts user
    string newCommand;                      // creates a string tostore the command
    cin >> newCommand;                      // collects input from user

    // if the command is valid, it will be saved
    if (validate(newCommand))
    {
        // creates a new command object and keeps it as a pointer
        Command *command = &Command(newCommand);
        saveCommand(command);
    }
    // otherwise, validate will display an error message
}

// receives the pointer to a command object, makes a copy and stores it in a collection of command objects
void CommandProcessor::saveCommand(Command *command)
{
    // creates a new command object on the heap
    // REMEMBER TO DELETE AT THE END OF THE PROGRAM!!!!
    Command *newCommand = new Command(*command);

    // stores the command in the vector attribute of the commandProcessor class
    this->allCommands->push_back(newCommand);
}

// CommandProcessor(); // default constructor
// // CommandProcessor();               // parameterized
// CommandProcessor(CommandProcessor &otherCommandProcessor); // copy constructor
// ~CommandProcessor();                                       // destructor
//                                                            //  assignment operator
// CommandProcessor &operator=(const CommandProcessor &otherCommandProcessor);
// // stream insertion operator
// friend std::ostream &operator<<(std::ostream &out, const CommandProcessor &commandProcessorObject);
// void getCommand();
// void validate(Command command);

//-----------------COMMAND CLASS----------------//

// class Command
// {
// private:
//     string command;
//     string effect;

// public:
//     Command();                                                                        // default constructor
//     Command(Command &otherCommand);                                                   // copy constructor
//     ~Command();                                                                       // destructor
//     Command &operator=(const Command &otherCommand);                                  // assignment operator
//     friend std::ostream &operator<<(std::ostream &out, const Command &commandObject); // stream insertion operator
//     void saveEffect();
// };

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

// default constructor
CommandProcessor::CommandProcessor()
{
    // creates a pointer to an empty vector
    vector<Command *> *newVector = new vector<Command *>;
    this->allCommands = newVector;
}
// // CommandProcessor();               // parameterized
// copy constructor
CommandProcessor::CommandProcessor(CommandProcessor &otherCommandProcessor)
{
    // copy over the vector (deep copy)
    // makes a new vector
    this->allCommands = new vector<Command *>;

    // fills the vector with deep copies of the command objects
    for (int i = 0; i < otherCommandProcessor.allCommands->size(); i++)
    {
        this->allCommands->at(i) = otherCommandProcessor.allCommands->at(i);
    }
}
// destructor
CommandProcessor::~CommandProcessor()
{
    // need to make sure the vector is properly deleted
    //  loops through and deletes every command
    for (int i = 0; i < this->allCommands->size(); i++)
    {
        // will call the destructor of the command class
        delete this->allCommands->at(i);
    }
    // deletes the entire vector
    delete this->allCommands;
}
//  assignment operator
CommandProcessor &CommandProcessor::operator=(const CommandProcessor &otherCommandProcessor)
{
    // avoids self assignment
    if (this != &otherCommandProcessor)
    {
        // gets rid of old vector
        // loops through and deletes every command
        for (int i = 0; i < this->allCommands->size(); i++)
        {
            delete this->allCommands->at(i);
        }
        // deletes the entire vector
        delete this->allCommands;
        // makes a new vector
        this->allCommands = new vector<Command *>;

        // fills the vector with deep copies of the command objects
        for (int i = 0; i < otherCommandProcessor.allCommands->size(); i++)
        {
            this->allCommands->at(i) = otherCommandProcessor.allCommands->at(i);
        }
    }
    return *this;
};

// stream insertion operator
std::ostream &operator<<(std::ostream &out, const CommandProcessor &commandProcessorObject)
{
    // checks to make sure the vector isn't empty
    if (!commandProcessorObject.allCommands->empty())
        // prints out all the commands
        // will use the stream insertion operators from the command class
        for (int i = 0; i < commandProcessorObject.allCommands->size(); i++)
        {
            out << commandProcessorObject.allCommands->at(i) << endl;
        }
    else
        out << "There are no commands yet" << endl;
    return out;
};
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

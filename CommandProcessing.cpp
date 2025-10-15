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
Command *CommandProcessor::readCommand()
{
    cout << "Enter next command: " << endl; // prompts user
    string newCommand;                      // creates a string tostore the command
    cin >> newCommand;                      // collects input from user

    // if the command is valid, it will be saved
    if (validate(newCommand))
    {
        // creates a new command object and returns it
        Command *command = &Command(newCommand);
        return command;
    }
    // otherwise, validate will display an error message
    // we return a null pointer
    return nullptr;
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
void CommandProcessor::getCommand()
{
    // creates a new command pointer (on stack)
    // gets input from user
    Command *commandRead = readCommand();
    // if the command is valid
    if (commandRead != nullptr)
    {
        // it is saved
        saveCommand(commandRead);
    }
    // if command is invalid nothing will happen here, the validate method would have displayed the error message
}
// void validate(Command command);

//-----------------COMMAND CLASS----------------//

// default constructor
Command::Command()
{
    // the command object will contain null pointers for the attributes
    this->command = nullptr;
    this->effect = nullptr;
}
// parameterized
Command::Command(string commandString)
{
    // takes a command and creates the command object
    this->command = new string(commandString);
    // sets the effect to nullptr
    this->effect = nullptr;
}
// parameterized 2
Command::Command(string commandString, string effectString)
{
    // takes a command and an effect and creates the command object
    this->command = new string(commandString);
    // sets the effect to nullptr
    this->effect = new string(effectString);
}
// copy constructor
// takes another command object and makes a deep copy of it
Command::Command(Command &otherCommand)
{
    // deep copy of the command
    this->command = new string(*(otherCommand.command));
    // deep copy of the effect
    this->effect = new string(*(otherCommand.effect));
}
// destructor
Command::~Command()
{
    // deletes the command and effect pointers
    delete this->command;
    delete this->effect;
}
// assignment operator
Command &Command::operator=(const Command &otherCommand)
{
    // avoids self assignment
    if (this != &otherCommand)
    {
        // deletes old Command information
        delete this->command;
        delete this->effect;

        // copies over the other command and effect
        //  deep copy of the command
        this->command = new string(*(otherCommand.command));
        // deep copy of the effect
        this->effect = new string(*(otherCommand.effect));

        // returns the copied Command object
        return *this;
    }
}
// stream insertion operator
std::ostream &operator<<(std::ostream &out, const Command &commandObject)
{
    // the format for displaying a command will be:
    // CommandName: effect

    // checks to make sure the command is not null
    if (commandObject.command != nullptr)
    {
        // checks to make sure effect is not null
        if (commandObject.effect != nullptr)
        {
            out << *(commandObject.command) << ": " << *(commandObject.effect);
        }
        // if command has something but effect is null then:
        else
        {
            out << *(commandObject.command) << ": No effect";
        }
    }
    // if command is null
    else
    {
        // this case should not happen in the program but I still put it here in case
        out << "No command specified";
    }
    return out;
}
//     void saveEffect();
// };

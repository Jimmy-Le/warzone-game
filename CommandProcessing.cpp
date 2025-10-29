// For part 1 of assignment 2

#include "CommandProcessing.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
#include <vector>
using std::allocator;
using std::vector;
#include "GameEngine.h"
#include <limits>
#include <fstream>
using std::getline;
using std::ifstream;

// forward declaration
class CommandProcessor;
class Command;
class FileCommandProcessorAdapter;
class FileLineReader;

// accesses the global variable from the gameEngine.cpp file
extern GameEngine *theGameEngine;

// global command processor object:
CommandProcessor *theCommandProcessor = new CommandProcessor();

//-----------------COMMAND PROCESSOR CLASS----------------//

// gets a command from the console as a string
// calls validate on the command to check if it is valid in the current game state
// calls the save command method to save that command
Command *CommandProcessor::readCommand()
{

    // Remove this line since it's causing the double-enter issue
    // // clears the buffer (prevents taking the newline character from the previous int input in GameEngine)
    // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool validCommand = false;
    // will keep prompting user until a valid command is given
    while (!validCommand)
    {
        cout << "Enter next command: " << endl; // prompts user
        string newCommand;                      // creates a string tostore the command
        // Use std::ws to skip any whitespace/newlines instead
        getline(cin >> std::ws, newCommand); // collects input from user

        // if the command is valid, it will be saved
        if (validate(newCommand))
        {
            // to exit the loop
            validCommand = true;
            // creates a new command object and returns it
            Command *command = new Command(newCommand);
            return command;
        }
        // otherwise, validate will display an error message
    }
    return nullptr;
}

// receives the pointer to a command object, makes a copy and stores it in a collection of command objects
void CommandProcessor::saveCommand(Command *command)
{
    cout << *command << endl;
    if (command == nullptr)
    {
        cout << "Error: Tried to save a null command!" << endl;
        return;
    }
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
// validate method
// checks if the command is valid in the current state
bool CommandProcessor::validate(string command)
{

    // checks the game state:
    Status *currentState = theGameEngine->getState();

    // verifies if the command is valid in the state:
    // i will check the whole words first
    // dynamic cast will return a nullptr if the class of currentState does not match the one
    // casting to.
    if (command == "validatemap" && dynamic_cast<MapLoaded *>(currentState) != nullptr)
    {
        // valid command:)
        return true;
    }
    else if (command == "gamestart" && dynamic_cast<PlayersAdded *>(currentState) != nullptr)
    {
        // valid command!
        return true;
    }
    else if (command == "replay" && dynamic_cast<Win *>(currentState) != nullptr)
    {
        // valid
        return true;
    }
    else if (command == "quit" && dynamic_cast<Win *>(currentState) != nullptr)
    {
        // valid
        return true;
    }
    // now for the states that have 2 parts to the string:
    else
    {
        // looks for the first space in the string
        int indexOfSpace = command.find(' ');

        // if its -1, there was no space
        if (indexOfSpace != -1)
        {
            // we will take the first part of the string, before the space
            string cutString = command.substr(0, indexOfSpace);

            // now we compare and see if this string matches the commands we need
            if (cutString == "loadmap" && (dynamic_cast<Start *>(currentState) != nullptr || dynamic_cast<MapLoaded *>(currentState) != nullptr))
            {

                // valid command!
                return true;
            }
            else if (cutString == "addplayer" && (dynamic_cast<MapValidated *>(currentState) != nullptr || dynamic_cast<PlayersAdded *>(currentState) != nullptr))
            {
                return true;
            }
            else
            {
                // invalid command
                cout << "Invalid Command" << endl;
                return false;
            }
        }
        else
        {
            // invalid command
            cout << "Invalid Command" << endl;
            return false;
        }
    }
};

Command *CommandProcessor::lastCommand()
{
    return this->allCommands->back();
}

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
    if (otherCommand.effect != nullptr)
    {
        // deep copy of the effect
        this->effect = new string(*(otherCommand.effect));
    }
    else
    {
        this->effect = nullptr;
    }
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
    return *this;
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

// save effect method
// receives a string and saves it in the command object
void Command::saveEffect(string effectString)
{
    this->effect = new string(effectString);
}

// gets the command string
string Command::getCommandString()
{
    return *(this->command);
}

//---------------FILE COMMAND PROCESSOR ADAPTER CLASS--------------------//

// reads a command from a file as a string
// calls validate on the command to check if it is valid in the current game state
// calls the save command method to save that command
Command *FileCommandProcessorAdapter::readCommand()
{
    string newCommand = flr->readLineFromFile();

    cout << "readCommand: " << newCommand << endl;

    // if the command is valid, it will be saved
    if (validate(newCommand))
    {
        // creates a new command object and returns it
        Command *command = new Command(newCommand);
        return command;
    }
    // otherwise, validate will display an error message

    return nullptr;
}

// default constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter()
{
    this->flr = new FileLineReader();
}

// parameterized constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(string filename)
{
    this->flr = new FileLineReader(filename);
}
// copy constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileCommandProcessorAdapter &otherFileCommandProcessorAdapter)
{
    // copy over the filereader
    this->flr = new FileLineReader(*(otherFileCommandProcessorAdapter.flr));
}
// destructor
FileCommandProcessorAdapter::~FileCommandProcessorAdapter()
{
    delete this->flr;
}
//  assignment operator
FileCommandProcessorAdapter &FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter &otherFileCommandProcessorAdapter)
{
    // avoids self assignment
    if (this != &otherFileCommandProcessorAdapter)
    {
        // delete old data
        delete this->flr;
        // copy over from other object (deep copy)
        this->flr = new FileLineReader(*(otherFileCommandProcessorAdapter.flr));
    }
    return *this;
}

// stream insertion operator
std::ostream &operator<<(std::ostream &out, const FileCommandProcessorAdapter &fileCommandProcessorAdapterObject)
{

    out << "Reading from file: " << fileCommandProcessorAdapterObject.flr << endl;
    return out;
};

void FileCommandProcessorAdapter::getCommands()
{
    // will read every line until the end of the file
    while (!this->flr->getReader()->eof())
    {
        cout << "while reading" << endl;
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
}

//-----------------------FILE LINE READER CLASS---------------------//

// default constructor
FileLineReader::FileLineReader()
{
    this->reader = nullptr;
}

// parameterized constructor
FileLineReader::FileLineReader(string filename)
{
    this->filename = new string(filename);
    this->reader = new ifstream(filename);
}

// copy constructor
FileLineReader::FileLineReader(FileLineReader &otherflr)
{
    this->filename = new string(*(otherflr.filename));
    this->reader = new ifstream(*(this->filename));
}

// destructor
FileLineReader::~FileLineReader()
{
    this->reader->close();
    delete reader;
    delete filename;
}

// stream insertion operator
std::ostream &operator<<(std::ostream &out, const FileLineReader &fileLineReaderObject)
{
    out << fileLineReaderObject.getFilename() << endl;
    return out;
};

// getter for filename
string FileLineReader::getFilename() const
{
    return *(this->filename);
}

// getter for reader
ifstream *FileLineReader::getReader()
{
    return this->reader;
}

string FileLineReader::readLineFromFile()
{
    ifstream *thisReader = this->reader;
    string newCommand;
    if (this->reader != nullptr)
    {
        // gets a line from the file
        getline(*thisReader, newCommand);
        return newCommand;
    }
    else
    {
        cout << "No file detected." << endl;
        return "";
    }
}

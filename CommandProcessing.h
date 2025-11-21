#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H

// Header to the CommandProcessing.cpp file
#include <iostream>
#include "LoggingObserver.h"
using std::cout;
using std::string;
#include <vector>
using std::vector;
#include <iostream>
using std::ifstream;
// forward declaration
class CommandProcessor;
class Command;
class FileCommandProcessorAdapter;
class FileLineReader;

//-----------------COMMAND PROCESSOR CLASS----------------//

class CommandProcessor : public Subject, public ILoggable
{
private:
    vector<Command *> *allCommands; // pointer to a vector of command pointers
    Command *readCommand();

protected:
public:
    CommandProcessor(); // default constructor
    // CommandProcessor();               // parameterized
    CommandProcessor(CommandProcessor &otherCommandProcessor); // copy constructor
    ~CommandProcessor();                                       // destructor
                                                               //  assignment operator
    CommandProcessor &operator=(const CommandProcessor &otherCommandProcessor);
    // stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const CommandProcessor &commandProcessorObject);
    virtual void getCommand();
    void saveCommand(Command *command);
    bool validate(string command);
    Command *lastCommand(); // gets the command at the end of the list
    std::string stringToLog() override;
};

//-----------------COMMAND CLASS----------------//

class Command : public Subject, public ILoggable
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
    void saveEffect(string effectString);
    string getCommandString(); // getter for commandString
    string getEffectString();
    std::string stringToLog();
};

//-----------------FILE COMMAND PROCESSOR ADAPTER CLASS----------------//

class FileCommandProcessorAdapter : public CommandProcessor
{
private:
    FileLineReader *flr;
    Command *readCommand();

public:
    FileCommandProcessorAdapter();                                                              // default constructor
    FileCommandProcessorAdapter(string filename);                                               // parameterized
    FileCommandProcessorAdapter(FileCommandProcessorAdapter &otherFileCommandProcessorAdapter); // copy constructor
    ~FileCommandProcessorAdapter();                                                             // destructor
                                                                                                //  assignment operator
    FileCommandProcessorAdapter &operator=(const FileCommandProcessorAdapter &otherFileCommandProcessorAdapter);
    // stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const FileCommandProcessorAdapter &fileCommandProcessorAdapterObject);
    void getCommand();
    // getter for the fileLineReader
    FileLineReader *getFlr();
};

//--------------FILE LINE READER CLASS--------------------//

class FileLineReader
{
private:
    // file input reader
    ifstream *reader;
    // filename
    string *filename;

public:
    FileLineReader();                         // default constructor
    FileLineReader(string filename);          // parameterized constructor
    FileLineReader(FileLineReader &otherflr); // copy constructor
    ~FileLineReader();                        // destructor
    string getFilename() const;
    // getter for reader
    ifstream *getReader();                                                                    // getter
    friend std::ostream &operator<<(std::ostream &out, const FileLineReader &fileLineReader); // stream insertion
    // reads a line from a file and returns it.
    string readLineFromFile();
};
#endif
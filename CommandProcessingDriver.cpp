// Driver for Command processor

#include "CommandProcessing.h"
#include "CommandProcessingDriver.h"
#include "GameEngineDriver.h"
#include "LoggingObserver.h"
#include "GameEngine.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

extern CommandProcessor *theCommandProcessor;
extern GameEngine *theGameEngine;

// tests the command processor
void testCommandProcessor()
{

    // Create log observer
    LogObserver *logObs = new LogObserver();
    // Create objects
    CommandProcessor *cp = new CommandProcessor();
    Orderlist *ol = new Orderlist();
    Player *p = new Player();

    // Attach observer
    cp->attach(logObs);
    theGameEngine->attach(logObs);
    ol->attach(logObs);
    p->attach(logObs);

    // intro title
    cout << "-----Testing the Command Processor-----" << endl;
    // Present user with choices
    cout << "Choose whether to accept commands from:  \n 1- the console \nor \n 2- a file \n Enter you choice (1-2): " << endl;
    int input;
    // collect choice
    cin >> input;
    // take commands from the console
    if (input == 1)
    {
        // calls the GameEngineDriver method
        testGameStates();
    }
    // take commmands from a file
    else if (input == 2)
    {

        // gets the filename
        cout << "Enter the file name: " << endl;
        string filename;
        cin >> filename;

        // cout << "the file name entered is: |" << filename << "|" << endl;

        // creates a filecommandprocessor object
        FileCommandProcessorAdapter *fileAdapter = new FileCommandProcessorAdapter(filename);

        // sets the global variable theCommandProcessor to fileAdapter (a subclass object)
        theCommandProcessor = fileAdapter;

        // cout << "Before reading" << endl;
        //  reads all commands
        fileAdapter->getCommand();

        testGameStates();

        // deletes the object (avoid memory leaks
        delete fileAdapter;

        delete cp;
        delete theGameEngine;
        delete ol;
        delete p;
        delete logObs;
        cout << "------End of Command Processor testing-------";
    }
}

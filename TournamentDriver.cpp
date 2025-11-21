#include "TournamentDriver.h"
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

// tests the tournament stuff (just plays whole game idk)
void testTournament()
{

    // Create log observer
    LogObserver *logObs = new LogObserver();
    // Create objects
    Orderlist *ol = new Orderlist();
    Player *p = new Player();

    // Attach observer

    theGameEngine->attach(logObs);
    ol->attach(logObs);
    p->attach(logObs);

    // intro title
    cout << "-----Testing the Tournament-----" << endl;
    // Present user with choices
    cout << "Choose whether to accept commands from:  \n 1- the console \nor \n 2- a file \n Enter you choice (1-2): " << endl;
    int input;
    // collect choice
    cin >> input;
    // take commands from the console
    if (input == 1)
    {
        // attach observer
        theCommandProcessor->attach(logObs);
        // calls Fayfay's stuff!
        testStartupPhase();
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

        // attach observer
        theCommandProcessor->attach(logObs);

        // cout << "Before reading" << endl;
        //  reads all commands
        fileAdapter->getCommand();

        testGameStates();

        // deletes the object (avoid memory leaks
        delete fileAdapter;

        delete theCommandProcessor;
        delete theGameEngine;
        delete ol;
        delete p;
        delete logObs;
        cout << "------End of Tournament testing-------";
    }
}

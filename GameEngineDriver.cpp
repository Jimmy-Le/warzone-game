// Contains a free function called testGameStates()
#include "GameEngine.h"
#include "GameEngineDriver.h"
#include "CommandProcessing.h"
#include <iostream>

extern CommandProcessor *theCommandProcessor;

// continuously calls the listen() function
void testGameStates()
{
    cout << "Commands must not be capitalized. You are currently in the Start state." << std::endl;
    // if its not reading from a file
    if (dynamic_cast<FileCommandProcessorAdapter *>(theCommandProcessor) == nullptr)
    {
        while (true)
        {
            listen();
        }
    }
    else
    {
        while (!dynamic_cast<FileCommandProcessorAdapter *>(theCommandProcessor)->getFlr()->getReader()->eof())
        {
            listen();
        }
    }
}

extern GameEngine *theGameEngine;

void testStartupPhase()
{
    if (!theGameEngine)
    {
        theGameEngine = new GameEngine(); // initialize the global engine
    }
    theGameEngine->startupPhase();
}
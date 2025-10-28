// Contains a free function called testGameStates()
#include "GameEngine.h"
#include "GameEngineDriver.h"
#include <iostream>

// continuously calls the listen() function
void testGameStates()
{
    cout << "Commands must not be capitalized. You are currently in the Start state." << std::endl;
    while (true)
    {
        listen();
    }
}

extern GameEngine* theGameEngine;

void testStartupPhase() {
    if (!theGameEngine) {
        theGameEngine = new GameEngine(); // initialize the global engine
    }
    theGameEngine->startupPhase();
}
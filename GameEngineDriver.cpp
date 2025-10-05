// Contains a free function called testGameStates()
#include "GameEngine.h"
#include "GameEngineDriver.h"

// continuously calls the listen() function
void testGameStates()
{
    cout << "Enter a command (no capitals). You are currently in the Start state." << std::endl;
    while (true)
    {
        listen();
    }
}
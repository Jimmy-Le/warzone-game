// Contains a free function called testGameStates()
#include "GameEngine.h"
#include "GameEngineDriver.h"

void testGameStates()
{
    cout << "Enter a command (no capitals). You are currently in the Start state." << endl;
    while (true)
    {
        listen();
    }
}
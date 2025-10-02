// Contains a free function called testGameStates()
#include "GameEngine.h"
#include "GameEngineDriver.h"

// continuously calls the listen() function
void testGameStates()
{
    while (true)
    {
        listen();
    }
}
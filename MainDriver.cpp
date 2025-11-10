// Main driving force of our program!!!
#include "GameEngineDriver.h"
#include <iostream>
#include "PlayerDriver.h"
#include "OrdersDriver.h"
#include "CardsDriver.h"
#include "MapDriver.h"
#include "CommandProcessingDriver.h"
#include "CommandProcessing.h"
using namespace std;

// global command processor object:
CommandProcessor *theCommandProcessor = new CommandProcessor();

int main()
{
    while (true)
    {
        cout << "Choose which part to test: " << endl;
        cout << "1. Map" << endl;
        cout << "2. Player" << endl;
        cout << "3. Orders List" << endl;
        cout << "4. Cards deck/hand" << endl;
        cout << "5. Game Engine (will end the program)" << endl;
        cout << "============  Assignment 2 ============" << endl;
        cout << "6. Part 1: Command processor and command adapter" << endl;
        cout << "7. Part 2: Game startup phase " << endl;
        cout << "8. Part 3: Main Game Loop " << endl;
        cout << "9. Part 4: Orders Execution" << endl;

        int input;
        cin >> input;

        switch (input)
        {
        case 1:
            testLoadMaps();
            break;
        case 2:
            testPlayers();
            break;
        case 3:
            testOrderList();
            break;
        case 4:
            testCards();
            break;
        case 5:
            testGameStates();
            break;
        case 6:
            testCommandProcessor();
            break;
        case 7:
            testStartupPhase();
            break;
        case 8:
            testMainGameLoop();
            break;
        case 9:
            testOrderExecution();
            break;
        default:
            cout << "Invalid option, try again" << endl;
            break;
        }
    }
    return 0;
}
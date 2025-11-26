// Main driving force of our program!!!
#include "GameEngineDriver.h"
#include <iostream>
#include "PlayerDriver.h"
#include "OrdersDriver.h"
#include "CardsDriver.h"
#include "MapDriver.h"
#include "CommandProcessingDriver.h"
#include "CommandProcessing.h"
#include "LoggingObserverDriver.h"
#include "PlayerStrategiesDriver.h"
#include "TournamentDriver.h"
#include <string>
using namespace std;

// global command processor object:
CommandProcessor *theCommandProcessor = new CommandProcessor();

int main()
{
    bool continueProgram = true;
    while (continueProgram)
    {
        cout << "Choose which part to test: " << endl;
        cout << "1. Tournament Mode" << endl;
        cout << "2. PlayerStrategies" << endl;
        cout << "3. Exit" << endl;


        int input;
        cin >> input;

        switch (input)
        {
        case 1:
            testTournament();
            break;
        case 2:
            testPlayerStrategies();
            break;
        case 3:
            cout << "Exiting program..." << endl;
            continueProgram = false;
            break;
        default:
            cout << "Invalid option, try again" << endl;
            break;
        }
    }

    
    return 0;
}

// Main driving force of our program!!!
#include "GameEngineDriver.h"
#include <iostream>
#include "PlayerDriver.h"
#include "OrdersDriver.h"
#include "CardsDriver.h"
#include "MapDriver.h"
using namespace std;

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
        cout << "Assignment 2" << endl;
        cout << "6. Part 1: Command processor and command adapter" << endl;
        cout << "7. Part 2: Game startup phase " << endl;

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
            break;
        case 7:
            testStartupPhase();
            break;
        default:
            cout << "Invalid option, try again" << endl;
            break;
        }
    }
    return 0;
}
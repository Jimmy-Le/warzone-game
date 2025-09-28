// Main driving force of our program!!!
#include "GameEngineDriver.h"
#include <iostream>
#include "PlayerDriver.h"
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

        int input;
        cin >> input;

        switch (input)
        {
        case 1:

            break;
        case 2:
            testPlayers();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            testGameStates();
            break;
        default:
            cout << "Invalid option, try again" << endl;
            break;
        }
    }
}
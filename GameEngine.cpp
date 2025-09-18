// Controls the flow of the game.

#include <iostream>
using namespace std;
#include <string>
#include "GameEngine.h"

// Status class methods
Status::Status() {}
void Status::transition(string input, Status *currentStatus)
{
    cout << "testing";
}

// Start class methods
Start::Start() {}

void Start::transition(string input, Status *currentStatus)
{
    if (input == "loadmap")
    {
        currentStatus = switchStatus(2, static_cast<Start *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again.";
    }
};

// map loaded methods

MapLoaded::MapLoaded() {}
void MapLoaded::transition(string input, Status *currentStatus)
{
    if (input == "loadmap")
    {
        currentStatus = switchStatus(2, static_cast<MapLoaded *>(currentStatus));
    }
    else if (input == "validatemap")
    {
        currentStatus = switchStatus(3, static_cast<MapLoaded *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again.";
    }
}

;

// map validated methods

MapValidated::MapValidated() {

};
void MapValidated::transition(string input, Status *currentStatus)
{
    if (input == "addplayer")
    {
        currentStatus = switchStatus(4, static_cast<MapValidated *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again.";
    }
}

;

// players added methods

PlayersAdded::PlayersAdded()
{
}
void PlayersAdded::transition(string input, Status *currentStatus)
{
    if (input == "addplayer")
    {
        currentStatus = switchStatus(4, static_cast<PlayersAdded *>(currentStatus));
    }
    else if (input == "assigncountries")
    {
        currentStatus = switchStatus(5, static_cast<PlayersAdded *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again.";
    }
}

;

// assign reinforcement class methods
AssignReinforcement::AssignReinforcement()
{
}
void AssignReinforcement::transition(string input, Status *currentStatus)
{
    if (input == "issueorder")
    {
        currentStatus = switchStatus(6, static_cast<AssignReinforcement *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again.";
    }
};

// issue orders class methods

IssueOrders::IssueOrders()
{
}
void IssueOrders::transition(string input, Status *currentStatus)
{
    if (input == "issueorder")
    {
        currentStatus = switchStatus(6, static_cast<IssueOrders *>(currentStatus));
    }
    else if (input == "endissueorders")
    {
        currentStatus = switchStatus(7, static_cast<IssueOrders *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again.";
    }
};

// execute orders class methods

ExecuteOrders::ExecuteOrders()
{
}

void ExecuteOrders::transition(string input, Status *currentStatus)
{
    if (input == "execorder")
    {
        currentStatus = switchStatus(7, static_cast<ExecuteOrders *>(currentStatus));
    }
    else if (input == "endexecorders")
    {
        currentStatus = switchStatus(5, static_cast<ExecuteOrders *>(currentStatus));
    }
    else if (input == "win")
    {
        currentStatus = switchStatus(8, static_cast<ExecuteOrders *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again.";
    }
};

// win class methods

Win::Win() {}
void Win::transition(string input, Status *currentStatus)
{
    if (input == "play")
    {
        currentStatus = switchStatus(1, static_cast<Win *>(currentStatus));
    }
    else if (input == "end")
    {
        currentStatus = switchStatus(9, static_cast<Win *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again.";
    }
};

// global variable to keep track of the status
Status *currentStatus = new Start();

void listen()
{
    // Prompts user for command
    cout << "Enter a command: ";
    string input;
    cin >> input;

    // for testing purposes
    cout << input << endl;
    cout << &currentStatus << endl;

    currentStatus->transition(input, currentStatus);
};

// takes an integer corresponding to the status to switch to and then makes the status pointer point to an object
// of that status
Status *switchStatus(int nextStatus, Status *currentStatus)
{
    cout << "Entered switchStatus" << endl;
    Status *newStatus = nullptr;

    switch (nextStatus)
    {
    case 1:
        // switch to Start
        // create new Start object
        newStatus = new Start();
        // delete old status object
        delete currentStatus;
        // reassign pointer to the new start object
        currentStatus = newStatus;
        // return the modified pointer
        return currentStatus;
        break;
    case 2:
        // switch to MapLoaded
        // create new MapLoaded object
        newStatus = new MapLoaded();
        // delete old status object
        delete currentStatus;
        // reassign pointer to the new MapLoaded object
        currentStatus = newStatus;
        // return the modified pointer
        return currentStatus;
        break;
    case 3:
        // switch to MapValidated
        // create new MapValidated object
        newStatus = new MapValidated();
        // delete old status object
        delete currentStatus;
        // reassign pointer to the new MapValidated object
        currentStatus = newStatus;
        // return the modified pointer
        return currentStatus;
        break;
    case 4:
        // switch to PlayersAdded
        // create new PlayersAdded object
        newStatus = new PlayersAdded();
        // delete old status object
        delete currentStatus;
        // reassign pointer to the new PlayersAdded object
        currentStatus = newStatus;
        // return the modified pointer
        return currentStatus;
        break;
    case 5:
        // switch to AssignReinforcement
        // create new AssignReinforcement object
        newStatus = new AssignReinforcement();
        // delete old status object
        delete currentStatus;
        // reassign pointer to the new AssignReinforcement object
        currentStatus = newStatus;
        // return the modified pointer
        return currentStatus;
        break;
    case 6:
        // switch to IssueOrders
        // create new IssueOrders object
        newStatus = new IssueOrders();
        // delete old status object
        delete currentStatus;
        // reassign pointer to the new IssueOrders object
        currentStatus = newStatus;
        // return the modified pointer
        return currentStatus;
        break;
    case 7:
        // switch to ExecuteOrders
        // create new ExecuteOrders object
        newStatus = new ExecuteOrders();
        // delete old status object
        delete currentStatus;
        // reassign pointer to the new ExecuteOrders object
        currentStatus = newStatus;
        // return the modified pointer
        return currentStatus;
        break;
    case 8:
        // switch to win
        // create new Win object
        newStatus = new Win();
        // delete old status object
        delete currentStatus;
        // reassign pointer to the new Win object
        currentStatus = newStatus;
        // return the modified pointer
        return currentStatus;
        break;
    case 9:
        // end the program
        exit(0);
        break;
    }
    return currentStatus;
}

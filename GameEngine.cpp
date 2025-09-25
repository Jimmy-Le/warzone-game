// Controls the flow of the game.

#include <iostream>
using namespace std;
#include <string>
#include "GameEngine.h"

// Status class methods
Status::Status() {}
Status *Status::transition(string input, Status *currentStatus)
{
    return currentStatus;
}

// Start class methods
Start::Start() {}

Status *Start::transition(string input, Status *currentStatus)
{
    if (input == "loadmap")
    {
        return switchStatus(2, static_cast<Start *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again." << endl;
        return currentStatus;
    }
};
// stream insertion operator
std::ostream &operator<<(ostream &out, const Start &startObject)
{
    out << "State: Start" << endl;
    return out;
}

// map loaded methods

MapLoaded::MapLoaded() {}
Status *MapLoaded::transition(string input, Status *currentStatus)
{
    if (input == "loadmap")
    {
        return switchStatus(2, static_cast<MapLoaded *>(currentStatus));
    }
    else if (input == "validatemap")
    {
        return switchStatus(3, static_cast<MapLoaded *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again." << endl;
        return currentStatus;
    }
}

;
// stream insertion operator
std::ostream &operator<<(ostream &out, const MapLoaded &mapLoadedObject)
{
    out << "State: Map Loaded" << endl;
    return out;
}

// map validated methods

MapValidated::MapValidated() {

};
Status *MapValidated::transition(string input, Status *currentStatus)
{
    if (input == "addplayer")
    {
        return switchStatus(4, static_cast<MapValidated *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again." << endl;
        return currentStatus;
    }
}

;
// stream insertion operator
std::ostream &operator<<(ostream &out, const MapValidated &mapValidatedObject)
{
    out << "State: Map Validated" << endl;
    return out;
}

// players added methods

PlayersAdded::PlayersAdded()
{
}
Status *PlayersAdded::transition(string input, Status *currentStatus)
{
    if (input == "addplayer")
    {
        return switchStatus(4, static_cast<PlayersAdded *>(currentStatus));
    }
    else if (input == "assigncountries")
    {
        return switchStatus(5, static_cast<PlayersAdded *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again." << endl;
        return currentStatus;
    }
};
// stream insertion operator
std::ostream &operator<<(ostream &out, const PlayersAdded &playersAddedObject)
{
    out << "State: Players Added" << endl;
    return out;
}

// assign reinforcement class methods
AssignReinforcement::AssignReinforcement()
{
}
Status *AssignReinforcement::transition(string input, Status *currentStatus)
{
    if (input == "issueorder")
    {
        return switchStatus(6, static_cast<AssignReinforcement *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again." << endl;
        return currentStatus;
    }
};

// stream insertion operator
std::ostream &operator<<(ostream &out, const AssignReinforcement &assignReinforcementObject)
{
    out << "State: Assign Reinforcement " << endl;
    return out;
}

// issue orders class methods

IssueOrders::IssueOrders()
{
}
Status *IssueOrders::transition(string input, Status *currentStatus)
{
    if (input == "issueorder")
    {
        return switchStatus(6, static_cast<IssueOrders *>(currentStatus));
    }
    else if (input == "endissueorders")
    {
        return switchStatus(7, static_cast<IssueOrders *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again." << endl;
        return currentStatus;
    }
};

// stream insertion operator
std::ostream &operator<<(ostream &out, const IssueOrders &issueOrdersObject)
{
    out << "State: Issue Orders" << endl;
    return out;
}

// execute orders class methods

ExecuteOrders::ExecuteOrders()
{
}

Status *ExecuteOrders::transition(string input, Status *currentStatus)
{
    if (input == "execorder")
    {
        return switchStatus(7, static_cast<ExecuteOrders *>(currentStatus));
    }
    else if (input == "endexecorders")
    {
        return switchStatus(5, static_cast<ExecuteOrders *>(currentStatus));
    }
    else if (input == "win")
    {
        return switchStatus(8, static_cast<ExecuteOrders *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again." << endl;
        return currentStatus;
    }
};
// stream insertion operator
std::ostream &operator<<(ostream &out, const ExecuteOrders &ExecuteOrdersObject)
{
    out << "State: Execute Orders" << endl;
    return out;
}

// win class methods

Win::Win() {}
Status *Win::transition(string input, Status *currentStatus)
{
    if (input == "play")
    {
        return switchStatus(1, static_cast<Win *>(currentStatus));
    }
    else if (input == "end")
    {
        return switchStatus(9, static_cast<Win *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again." << endl;
        return currentStatus;
    }
};

// stream insertion operator
std::ostream &operator<<(ostream &out, const Win &winObject)
{
    out << "State: Win" << endl;
    return out;
}

// global variable to keep track of the status
Status *currentStatus = new Start();

void listen()
{
    // Prompts user for command
    cout << "Enter a command: ";
    string input;
    cin >> input;

    Status *oldStatus = currentStatus;
    Status *nextStatus = currentStatus->transition(input, currentStatus);
    if (nextStatus != currentStatus)
    {
        delete oldStatus;
        currentStatus = nextStatus;
    }
};

// takes an integer corresponding to the status to switch to and then makes the status pointer point to an object
// of that status
Status *switchStatus(int nextStatus, Status *currentStatus)
{
    Status *newStatus = nullptr;

    switch (nextStatus)
    {
    case 1:
        // switch to Start
        // create new Start object
        newStatus = new Start();
        // return a pointer to the new state
        cout << "Change state to Start" << endl;
        return newStatus;
        break;
    case 2:
        // switch to MapLoaded
        // create new MapLoaded object
        newStatus = new MapLoaded();
        cout << "Change State to Map Loaded" << endl;
        // return the modified pointer
        return newStatus;
        break;
    case 3:
        // switch to MapValidated
        // create new MapValidated object
        newStatus = new MapValidated();
        cout << "Change State to Map Validated" << endl;
        // return the modified pointer
        return newStatus;
        break;
    case 4:
        // switch to PlayersAdded
        // create new PlayersAdded object
        newStatus = new PlayersAdded();
        cout << "Change State to Players Added" << endl;
        // return the modified pointer
        return newStatus;
        break;
    case 5:
        // switch to AssignReinforcement
        // create new AssignReinforcement object
        newStatus = new AssignReinforcement();
        cout << "Change State to Assign Reinforcement" << endl;
        // return the modified pointer
        return newStatus;
        break;
    case 6:
        // switch to IssueOrders
        // create new IssueOrders object
        newStatus = new IssueOrders();
        cout << "Change State to Issue Orders" << endl;
        // return the modified pointer
        return newStatus;
        break;
    case 7:
        // switch to ExecuteOrders
        // create new ExecuteOrders object
        newStatus = new ExecuteOrders();
        cout << "Change State to Execute Orders" << endl;
        // return the modified pointer
        return newStatus;
        break;
    case 8:
        // switch to win
        // create new Win object
        newStatus = new Win();
        cout << "Change State to Win" << endl;
        // return the modified pointer
        return newStatus;
        break;
    case 9:
        // end the program
        cout << "Goodbye!" << endl;
        delete currentStatus;
        exit(0);
        break;
    }
    return currentStatus;
}

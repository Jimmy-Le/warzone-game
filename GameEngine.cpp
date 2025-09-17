// Controls the flow of the game.

#include <iostream>
using namespace std;
#include <string>

void listen()
{
    // Prompts user for command
    cout << "Enter a command: ";
    string input;
    cin >> input;

    // checkInput(input);
}

// takes an integer corresponding to the status to switch to and then makes the status pointer point to an object
// of that status
void switchStatus(int nextStatus, Status *currentStatus)
{

    switch (nextStatus)
    {
    case 1:
        // switch to Start
        break;
    case 2:
        // switch to MapLoaded
        break;
    case 3:
        // switch to MapValidated
        break;
    case 4:
        // switch to PlayersAdded
        break;
    case 5:
        // switch to AssignReinforcements
        break;
    case 6:
        // switch to IssueOrders
        break;
    case 7:
        // switch to ExecuteOrders
        break;
    case 8:
        // switch to win
        break;
    case 9:
        // end the program
        break;
    }
}

// Start class
class Start
{
protected:
    string name = "start";

    void transition(string input)
    {
        if (input == "loadmap")
        {
            switchStatus(2);
        }
        else
        {
            cout << "Invalid command, please try again.";
        }
    }
};

// map loaded class
class MapLoaded
{
public:
    void transition(string input)
    {
        if (input == "loadmap")
        {
            switchStatus(2);
        }
        else if (input == "validatemap")
        {
            switchStatus(3);
        }
        else
        {
            cout << "Invalid command, please try again.";
        }
    }
};

// map validated class
class MapValidated
{
public:
    void transition(string input)
    {
        if (input == "addplayer")
        {
            switchStatus(4);
        }
        else
        {
            cout << "Invalid command, please try again.";
        }
    }
};

// players added class
class PlayersAdded
{
public:
    void transition(string input)
    {
        if (input == "addplayer")
        {
            switchStatus(4);
        }
        else if (input == "assigncountries")
        {
            switchStatus(5);
        }
        else
        {
            cout << "Invalid command, please try again.";
        }
    }
};

// assign reinforcement class
class AssignReinforcement
{
public:
    void transition(string input)
    {
        if (input == "issueorder")
        {
            switchStatus(6);
        }
        else
        {
            cout << "Invalid command, please try again.";
        }
    }
};

// issue orders class
class IssueOrders
{
public:
    void transition(string input)
    {
        if (input == "issueorder")
        {
            switchStatus(6);
        }
        else if (input == "endissueorders")
        {
            switchStatus(7);
        }
        else
        {
            cout << "Invalid command, please try again.";
        }
    }
};

// execute orders class
class ExecuteOrders
{
public:
    void transition(string input)
    {
        if (input == "execorder")
        {
            switchStatus(7);
        }
        else if (input == "endexecorders")
        {
            switchStatus(5);
        }
        else if (input == "win")
        {
            switchStatus(8);
        }
        else
        {
            cout << "Invalid command, please try again.";
        }
    }
};

// win class
class Win
{
public:
    void transition(string input)
    {
        if (input == "play")
        {
            switchStatus(1);
        }
        else if (input == "end")
        {
            switchStatus(9);
        }
        else
        {
            cout << "Invalid command, please try again.";
        }
    }
};
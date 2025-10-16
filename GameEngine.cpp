// Controls the flow of the game.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::string;
#include <string>
#include "GameEngine.h"

#include "CommandProcessing.h"

// forward declaration
class CommandProcessor;
class Command;
// global object
extern CommandProcessor *theCommandProcessor;

//----------------------------------CLASS IMPLEMENTATIONS---------------------------------------------------------//

//----------STATUS CLASS --------------//
// This is the base class to all the game state classes.
// I used it like an interface.
// The game states are the phases listed in the bubbles for part 5 (see instructions assignment 1)

// default constructor
Status::Status() {}
// transition method, switches to another state
// in this case, we stay on the same state.
// this is just a backup method and isn't actually used in the program directly
Status *Status::transition(string input, Status *currentStatus)
{
    return currentStatus;
}
// Operator overloading
std::ostream &operator<<(std::ostream &out, const Status &status)
{
    // each Status subclass has their own print method
    status.print(out);
    return out;
}

//----------START CLASS --------------//
// the first game state

// default constructor
Start::Start() {}

// transition method
// switches to another state
// takes the input read from the console in the listen() method
// and the currentStatus of the game (the single attribute in my GameEngine class)
Status *Start::transition(string input, Status *currentStatus)
{
    // depending on the input, the state will change to the correct one
    if (input == "loadmap")
    {
        // I send an int(representing the state, they're numbered in order)
        // I also send the currentStatus and make sure it is cast as a Start* object
        // This is becuase I don't want to call the base class methods, I want to specifically call the Start class methods.
        return switchStatus(2, static_cast<Start *>(currentStatus));
    }
    else
    {
        // if the user inputs any other random command
        cout << "Invalid command, please try again." << endl;
        return currentStatus;
    }
};
// clone method
// I use this for my = operator overload and copy constructor
// it helps me do deep copies
Status *Start::clone()
{
    // returns an entirely new object of start type
    // no need to initialize anything, since there are no attributes in these classes
    return new Start();
};
// stream insertion operator
std::ostream &operator<<(ostream &out, const Start &startObject)
{
    out << "State: Start" << endl;
    return out;
}
// print method
// this is for the base class' stream insertion operator
void Start::print(std::ostream &out) const
{
    out << "Game State: Start";
};

//----------MAPLOADED CLASS --------------//
// 2

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
// clone method
Status *MapLoaded::clone()
{
    return new MapLoaded();
};
// stream insertion operator
std::ostream &operator<<(ostream &out, const MapLoaded &mapLoadedObject)
{
    out << "State: Map Loaded" << endl;
    return out;
}
// print method
void MapLoaded::print(std::ostream &out) const
{
    out << "Game State: MapLoaded";
};

//----------MAPVALIDATED CLASS --------------//
// 3
// default constructor
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
};
// clone method
Status *MapValidated::clone()
{
    return new MapValidated();
};
// stream insertion operator
std::ostream &operator<<(ostream &out, const MapValidated &mapValidatedObject)
{
    out << "State: Map Validated" << endl;
    return out;
}
// print method
void MapValidated::print(std::ostream &out) const
{
    out << "Game State: MapValidated";
};

//----------PLAYERSADDED CLASS --------------//
// 4
PlayersAdded::PlayersAdded()
{
}
Status *PlayersAdded::transition(string input, Status *currentStatus)
{
    if (input == "addplayer")
    {
        return switchStatus(4, static_cast<PlayersAdded *>(currentStatus));
    }
    else if (input == "gamestart")
    {
        return switchStatus(5, static_cast<PlayersAdded *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again." << endl;
        return currentStatus;
    }
};
// clone method
Status *PlayersAdded::clone()
{
    return new PlayersAdded();
};
// stream insertion operator
std::ostream &operator<<(ostream &out, const PlayersAdded &playersAddedObject)
{
    out << "State: Players Added" << endl;
    return out;
};
// print method
void PlayersAdded::print(std::ostream &out) const
{
    out << "Game State: PlayersAdded";
};

//----------ASSIGNREINFORCEMENT CLASS --------------//
// 5

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
// clone method
Status *AssignReinforcement::clone()
{
    return new AssignReinforcement();
};
// stream insertion operator
std::ostream &operator<<(ostream &out, const AssignReinforcement &assignReinforcementObject)
{
    out << "State: Assign Reinforcement " << endl;
    return out;
}
// print method
void AssignReinforcement::print(std::ostream &out) const
{
    out << "Game State: AssignReinforcement";
};

//----------ISSUEORDERS CLASS --------------//
// 6

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
// clone method
Status *IssueOrders::clone()
{
    return new IssueOrders();
};
// stream insertion operator
std::ostream &operator<<(ostream &out, const IssueOrders &issueOrdersObject)
{
    out << "State: Issue Orders" << endl;
    return out;
}
// print method
void IssueOrders::print(std::ostream &out) const
{
    out << "Game State: IssueOrders";
};

//----------EXECUTEORDERS CLASS --------------//
// 7
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
// clone method
Status *ExecuteOrders::clone()
{
    return new ExecuteOrders();
};
// stream insertion operator
std::ostream &operator<<(ostream &out, const ExecuteOrders &ExecuteOrdersObject)
{
    out << "State: Execute Orders" << endl;
    return out;
}
// print method
void ExecuteOrders::print(std::ostream &out) const
{
    out << "Game State: ExecuteOrders";
};

//----------WIN CLASS --------------//
// 8

Win::Win() {}
Status *Win::transition(string input, Status *currentStatus)
{
    if (input == "replay")
    {
        return switchStatus(1, static_cast<Win *>(currentStatus));
    }
    else if (input == "quit")
    {
        return switchStatus(9, static_cast<Win *>(currentStatus));
    }
    else
    {
        cout << "Invalid command, please try again." << endl;
        return currentStatus;
    }
};
// clone method
Status *Win::clone()
{
    return new Win();
};
// stream insertion operator
std::ostream &operator<<(ostream &out, const Win &winObject)
{
    out << "State: Win" << endl;
    return out;
}
// print method
void Win::print(std::ostream &out) const
{
    out << "Game State: Win";
};

//------------GAME ENGINE CLASS--------------------------------//
// keeps track of the state of the game!

// copy constructor
GameEngine::GameEngine(GameEngine &otherGameEngine)
{
    state = otherGameEngine.state->clone();
}
// parameterized constructor
GameEngine::GameEngine(Status *state)
{
    this->state = state;
}
// destructor
GameEngine::~GameEngine()
{
    delete this->state;
}
// assignment operator
GameEngine &GameEngine::operator=(const GameEngine &otherGameEngine)
{
    // avoids self assignment
    if (this != &otherGameEngine)
    {
        // gets rid of old state
        delete this->state;
        // makes a new state
        this->state = otherGameEngine.state->clone();
    }
    return *this;
}

// stream insertion operator
std::ostream &operator<<(std::ostream &out, const GameEngine &gameEngineObject)
{
    // checks to make sure the state isn't null
    if (gameEngineObject.getState())
        // prints out the game state
        //(this is where it uses the stream insertion operators made for each Status subclass)
        out << *(gameEngineObject.getState()) << endl;
    else
        out << "Game state: (null)" << endl;
    return out;
}
// getter
Status *GameEngine::getState() const
{
    return this->state;
};
// setter
void GameEngine::setState(Status *otherStatus)
{
    // deletes old state
    if (this->state != nullptr)
        delete this->state;
    this->state = otherStatus;
};

//--------------------------THE GAME ENGINE OBJECT!!!!!!!!!!--------------------------------------//
// global variable to keep track of the status
// very important
GameEngine *theGameEngine = new GameEngine(new Start());

//-------------LISTEN-------------//
// Takes user input
// takes care of transitions
// this is the method that controls everything in a way
void listen()
{
    // old version
    //  Prompts user for command
    //  cout << "Enter a command: ";
    //  string input;
    //  cin >> input;

    // NEW CHANGES!!!
    // Now, we will get commands from the commandProcessor!
    // prompt user for command
    theCommandProcessor->getCommand();
    // now we can go check the vector of commands to get that command (if it is valid)
    Command *command = theCommandProcessor->lastCommand();

    // want to make sure it only grabs the first part of the string (before the space)
    string input;
    // finds the first instance of space character
    // will be -1 if no space
    int indexOfSpace = command->getCommandString().find(' ');
    if (indexOfSpace != -1)
    {
        // we split the string
        // only have the part before the space
        input = command->getCommandString().substr(0, indexOfSpace);
    }
    else
    {
        // no space,no problem
        input = command->getCommandString();
    }

    // essentially, now only some state changes will be triggered by the user/command line
    // the other state changes will be done through other classes (i think, this is Jimmy's part)

    // keep track of previous state
    Status *oldStatus = theGameEngine->getState();
    // gets the next state
    Status *nextStatus = theGameEngine->getState()->transition(input, theGameEngine->getState());
    // in this case, either the user gave a correct command and we switch to a new state
    // or they gave an invalid command and we stay in the old state
    // so we check to see if we stay in the old state:
    if (nextStatus != oldStatus)
    {
        // if we don't, then we switch the state in GameEngine
        theGameEngine->setState(nextStatus);
    }
};

//--------------------------SWITCH StATUS-------------------------//
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
        // now the effect will be saved in the command object
        theCommandProcessor->lastCommand()->saveEffect("Transitions to the Start state");
        return newStatus;
        break;
    case 2:
        // switch to MapLoaded
        // create new MapLoaded object
        newStatus = new MapLoaded();
        cout << "Change State to Map Loaded" << endl;
        // now the effect will be saved in the command object
        theCommandProcessor->lastCommand()->saveEffect("Transitions to the map loaded state");
        //  return the modified pointer
        return newStatus;
        break;
    case 3:
        // switch to MapValidated
        // create new MapValidated object
        newStatus = new MapValidated();
        cout << "Change State to Map Validated" << endl;
        // now the effect will be saved in the command object
        theCommandProcessor->lastCommand()->saveEffect("Transitions to the map validated state");
        // return the modified pointer
        return newStatus;
        break;
    case 4:
        // switch to PlayersAdded
        // create new PlayersAdded object
        newStatus = new PlayersAdded();
        cout << "Change State to Players Added" << endl;
        // now the effect will be saved in the command object
        // MIGHT CAUSE PROBLEMS IF OTHER PARTS ALSO INTERACT WITH THIS
        // PLEASE LET ME KNOW IF YOUR PART TOUCHES THIS (arielle) TY
        theCommandProcessor->lastCommand()->saveEffect("Transitions to the players added state");
        // return the modified pointer
        return newStatus;
        break;
    case 5:
        // switch to AssignReinforcement
        // create new AssignReinforcement object
        newStatus = new AssignReinforcement();
        cout << "Change State to Assign Reinforcement" << endl;
        // now the effect will be saved in the command object
        theCommandProcessor->lastCommand()->saveEffect("Transitions to the assign reinforcement state");
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
        cout << "Goodbye!" << endl;
        // now the effect will be saved in the command object
        theCommandProcessor->lastCommand()->saveEffect("Exits the program");
        delete theGameEngine;
        exit(0);
        break;
    }
    return currentStatus;
}

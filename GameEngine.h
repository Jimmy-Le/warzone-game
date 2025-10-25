#ifndef GAMEENGINE_H
#define GAMEENGINE_H

// Header to the GameEngine.cpp file
#include <iostream>
using std::cout;
using std::string;
#include <string>
#include "Map.h"
#include "Player.h"
#include "Cards.h"

// Forward declarations
class Status;
class Start;
class MapLoaded;
class MapValidated;
class PlayersAdded;
class AssignReinforcement;
class IssueOrders;
class ExecuteOrders;
class Win;
class GameEngine;

/*
--> Base class for status
All other status classes will inherit from this one.
This is an abstract class/ interface.
*/
class Status
{
public:
    virtual Status *transition(string input, Status *currentStatus);
    virtual Status *clone() = 0; // clone method!
    Status();                    // default constructor
    Status(Status &otherStatus); // copy constructor
    friend std::ostream &operator<<(std::ostream &out, const Status &status);
    virtual void print(std::ostream &out) const = 0; // print method for the << overloading
};

class Start : public Status
{
public:
    Status *transition(string input, Status *currentStatus);
    Status *clone();
    void print(std::ostream &out) const;

    Start();                   // default constructor
    Start(Start &otherStatus); // copy constructor
                               // assignment operator
    Start &operator=(const Start &otherObject);
    // stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const Start &startObject);
};

class MapLoaded : public Status
{
public:
    Status *transition(string input, Status *currentStatus);
    Status *clone();
    void print(std::ostream &out) const;
    // default constructor
    MapLoaded();
    // copy constructor
    MapLoaded(MapLoaded &otherStatus);
    // assignment operator
    MapLoaded &operator=(const MapLoaded &otherObject);
    // stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const MapLoaded &mapLoadedObject);
};

class MapValidated : public Status
{
public:
    Status *transition(string input, Status *currentStatus);
    Status *clone();
    void print(std::ostream &out) const;
    // default constructor
    MapValidated();
    // copy constructor
    MapValidated(MapValidated &otherStatus);
    // assignment operator
    MapValidated &operator=(const MapValidated &otherObject);
    // stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const MapValidated &mapValidatedObject);
};

class PlayersAdded : public Status
{
public:
    Status *transition(string input, Status *currentStatus);
    Status *clone();
    void print(std::ostream &out) const;
    // default constructor
    PlayersAdded();
    // copy constructor
    PlayersAdded(PlayersAdded &otherStatus);
    // assignment operator
    PlayersAdded &operator=(const PlayersAdded &otherObject);
    // stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const PlayersAdded &playersAddedObject);
};

class AssignReinforcement : public Status
{
public:
    Status *transition(string input, Status *currentStatus);
    Status *clone();
    void print(std::ostream &out) const;
    // default constructor
    AssignReinforcement();
    // copy constructor
    AssignReinforcement(AssignReinforcement &otherStatus);
    // assignment operator
    AssignReinforcement &operator=(const AssignReinforcement &otherObject);
    // stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const AssignReinforcement &assignReinforcementObject);
};

class IssueOrders : public Status
{
public:
    Status *transition(string input, Status *currentStatus);
    Status *clone();
    void print(std::ostream &out) const;
    // default constructor
    IssueOrders();
    // copy constructor
    IssueOrders(IssueOrders &otherStatus);
    // assignment operator
    IssueOrders &operator=(const IssueOrders &otherObject);
    // stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const IssueOrders &issueOrdersObject);
};

class ExecuteOrders : public Status
{
public:
    Status *transition(string input, Status *currentStatus);
    Status *clone();
    void print(std::ostream &out) const;
    // default constructor
    ExecuteOrders();
    // copy constructor
    ExecuteOrders(ExecuteOrders &otherStatus);
    // assignment operator
    ExecuteOrders &operator=(const ExecuteOrders &otherObject);
    // stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const ExecuteOrders &executeOrdersObject);
};

class Win : public Status
{
public:
    Status *transition(string input, Status *currentStatus);
    Status *clone();
    void print(std::ostream &out) const;
    // default constructor
    Win();
    // copy constructor
    Win(Win &otherStatus);
    // assignment operator
    Win &operator=(const Win &otherObject);
    // stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const Win &winObject);
};

/*
GAME ENGINE CLASS
*/
class GameEngine
{
private:
    Status *state;
    Map* gameMap = nullptr;
    std::vector<Player*>* players = nullptr;
    Deck* deck = nullptr;

public:
    GameEngine();                            // default constructor
    GameEngine(Status *state);               // parameterized
    GameEngine(GameEngine &otherGameEngine); // copy constructor
    ~GameEngine();                           // destructor
                   //  assignment operator
    GameEngine &operator=(const GameEngine &otherGameEngine);
    // stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const GameEngine &gameEngineObject);
    // getter
    Status *getState() const;
    // setter
    void setState(Status *otherStatus);

    //Startup Phase
    void startupPhase();

    //Helper functions for game setup
    void loadMap(string filename);
    void validateMap();
    void addPlayers(string playerName);
    void startGame();
};

//Global game engine pointer
extern GameEngine *theGameEngine;

/*
 --> Takes input from command line
 */
void listen();

Status *switchStatus(int nextStatus, Status *currentStatus);
#endif
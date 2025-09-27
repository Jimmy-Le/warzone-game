#ifndef GAMEENGINE_H
#define GAMEENGINE_H

// Header to the GameEngine.cpp file
#include <iostream>
using namespace std;

#include <string>

/*
--> Base class for status
All other status classes will inherit from this one.
This is an abstract class/ interface.
*/
class Status
{
public:
    virtual Status *transition(string input, Status *currentStatus);
    Status();                    // default constructor
    Status(Status &otherStatus); // copy constructor
    // friend bool operator ==();
    // friend istream& operator >>(istream& ins, something);
};

class Start : public Status
{
public:
    Status *transition(string input, Status *currentStatus);

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
 --> Takes input from command line
 */
void listen();

Status *switchStatus(int nextStatus, Status *currentStatus);
#endif
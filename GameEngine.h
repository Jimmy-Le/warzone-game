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
};
class MapLoaded : public Status
{
public:
    Status *transition(string input, Status *currentStatus);

    MapLoaded();
    MapLoaded(MapLoaded &otherStatus);
};

class MapValidated : public Status
{
public:
    Status *transition(string input, Status *currentStatus);

    MapValidated();
    MapValidated(MapValidated &otherStatus);
};
class PlayersAdded : public Status
{
public:
    Status *transition(string input, Status *currentStatus);

    PlayersAdded();
    PlayersAdded(PlayersAdded &otherStatus);
};

class AssignReinforcement : public Status
{
public:
    Status *transition(string input, Status *currentStatus);

    AssignReinforcement();
    AssignReinforcement(AssignReinforcement &otherStatus);
};

class IssueOrders : public Status
{
public:
    Status *transition(string input, Status *currentStatus);

    IssueOrders();
    IssueOrders(IssueOrders &otherStatus);
};

class ExecuteOrders : public Status
{
public:
    Status *transition(string input, Status *currentStatus);

    ExecuteOrders();
    ExecuteOrders(ExecuteOrders &otherStatus);
};

class Win : public Status
{
public:
    Status *transition(string input, Status *currentStatus);

    Win();
    Win(Win &otherStatus);
};

/*
 --> Takes input from command line
 */
void listen();

Status *switchStatus(int nextStatus, Status *currentStatus);
#endif
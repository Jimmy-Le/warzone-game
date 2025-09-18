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
    virtual void transition(string input, Status *currentStatus);
    Status(); // default constructor
    // friend bool operator ==();
    // friend istream& operator >>(istream& ins, something);
};

class Start : public Status
{
public:
    void transition(string input, Status *currentStatus);

    Start();
};
class MapLoaded : public Status
{
public:
    void transition(string input, Status *currentStatus);

    MapLoaded();
};

class MapValidated : public Status
{
public:
    void transition(string input, Status *currentStatus);

    MapValidated();
};
class PlayersAdded : public Status
{
public:
    void transition(string input, Status *currentStatus);

    PlayersAdded();
};

class AssignReinforcement : public Status
{
public:
    void transition(string input, Status *currentStatus);

    AssignReinforcement();
};

class IssueOrders : public Status
{
public:
    void transition(string input, Status *currentStatus);

    IssueOrders();
};

class ExecuteOrders : public Status
{
public:
    void transition(string input, Status *currentStatus);

    ExecuteOrders();
};

class Win : public Status
{
public:
    void transition(string input, Status *currentStatus);

    Win();
};

/*
 --> Takes input from command line
 */
void listen();

Status *switchStatus(int nextStatus, Status *currentStatus);
#endif
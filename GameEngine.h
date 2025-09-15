//Header to the GameEngine.cpp file
#include <iostream>
using namespace std;

#include <string>


/*
--> Base class for status
All other status classes will inherit from this one.
This is an abstract class/ interface.
*/
class Status {
    protected: //Accessible only in inherited classes
    string name;
    void transition(string input);
    Status(); //default constructor
    //friend bool operator ==();
    //friend istream& operator >>(istream& ins, something);
};

/*
--> Takes input from command line
*/
int listen();

/*
--> Changes the state
Takes an int (corresponds to a state in the system)
Switches the state pointer to a new state object
OR
Displays an error message
*/
void switchTo(int);
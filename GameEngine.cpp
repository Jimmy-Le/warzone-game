// Controls the flow of the game.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::string;
#include <string>
#include "GameEngine.h"
#include <algorithm>
#include <random>
#include "LoggingObserver.h"
#include "CommandProcessing.h"
#include <vector>

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
    else if (input == "issueordersend")
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

// default constructor
GameEngine::GameEngine()
{
    state = new Start(); // default starting state
    gameMap = nullptr;
}

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
    if (gameMap != nullptr)
    {
        delete gameMap;
    }
    if (players)
    {
        for (Player *p : *players)
        {
            delete p; // delete each player object
        }
        delete players; // then delete the vector itself
    }
    if (deck != nullptr)
    {
        delete deck;
    }
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
    notify(this); // log state change
};

string GameEngine::stringToLog()
{
    std::ostringstream oss;
    oss << "GameEngine state has been modified. Current " << *getState();
    return oss.str();
}

//------------------------- StARTUP PHASE (ASS2)----------------------------
void GameEngine::startupPhase()
{
    cout << "\n================== STARTUP PHASE =================\n"
         << endl;
    cout << "Commands:\n"
         << "1. loadmap <filename> \n"
         << "2. validatemap  \n"
         << "3. addplayer <playerName> \n"
         << "4. gamestart \n";

    bool inStartup = true;
    while (inStartup)
    {

        // getCommand will prompt the user for input and then save it in a command object
        theCommandProcessor->getCommand();

        // Get the last command and its argument (the one we just collected)
        Command *cmd = theCommandProcessor->lastCommand();
        string cmdStr = cmd->getCommandString();
        string command, arg;

        // Parse command and argument

        size_t spacePos = cmdStr.find(' ');
        if (spacePos != string::npos)
        {
            command = cmdStr.substr(0, spacePos);
            arg = cmdStr.substr(spacePos + 1);
        }
        else
        {
            command = cmdStr;
        }

        // checks tournament mode!
        if ((dynamic_cast<Start *>(getState()) && command == "tournament"))
        {
            executeTournament(cmdStr);
        }
        else if ((dynamic_cast<Start *>(getState()) && command == "loadmap") || (dynamic_cast<MapLoaded *>(getState()) && command == "loadmap"))
        {
            loadMap(arg); // load the map
            if (gameMap != nullptr)
            {                         // checks if the map was successfully loaded
                changeState(command); // will change state to mapLoaded
            }
        }
        else if (dynamic_cast<MapLoaded *>(getState()) && command == "validatemap")
        {
            validateMap();        // validate the map
            changeState(command); // changes state to mapValidated
        }
        else if ((dynamic_cast<MapValidated *>(getState()) && command == "addplayer") || (dynamic_cast<PlayersAdded *>(getState()) && command == "addplayer"))
        {
            addPlayers(arg);      // add players
            changeState(command); // changes the state to PlayersAdded
        }
        else if (dynamic_cast<PlayersAdded *>(getState()) && command == "gamestart")
        {
            if (players->size() < 2)
            {
                cout << "At least two players are requiredto start the game." << endl;
            }
            else
            {
                startGame();          // start the game
                changeState(command); // will change state to AssignReinforcements or back to playersaddeds
                inStartup = false;    // exit startup phase
            }
        }
    }

    // when exiting the loop, we go to the main game!
    mainGameLoop();
}
// ========================= Temporary Function to get players (for testing purposes) =========================
std::vector<Player *> *GameEngine::getPlayers()
{
    return players;
}
// ========================= End of Temporary Function to get players (for testing purposes) =========================

//------------------------- TOURNAMENT (Assignment 3)  ----------------------------
void GameEngine::executeTournament(const string &tournamentCommand)
{
    // winners vector to store all the winning players in order
    vector<Player *> winners;

    // 1. Parse the command
    vector<string> mapFiles;
    vector<string> playerStrategies;
    int numGames = 1;
    int maxTurns = 10;

    // Find positions of each flags
    size_t mPos = tournamentCommand.find("-M");
    size_t pPos = tournamentCommand.find("-P");
    size_t gPos = tournamentCommand.find("-G");
    size_t dPos = tournamentCommand.find("-D");

    // Extract values based on flag positions
    if (mPos != string::npos && pPos != string::npos && gPos != string::npos && dPos != string::npos)
    {
        // Extract substrings
        string mList = tournamentCommand.substr(mPos + 3, pPos - (mPos + 3));
        string pList = tournamentCommand.substr(pPos + 3, gPos - (pPos + 3));
        string gNum = tournamentCommand.substr(gPos + 3, dPos - (gPos + 3));
        string dNum = tournamentCommand.substr(dPos + 3);

        // Split strings by comma
        string temp;
        for (char c : mList)
        {
            if (c == ',')
            {
                mapFiles.push_back(temp); // save the current map name to vector
                temp.clear();             // reset temp to start the next map name
            }
            else if (!isspace(c))
                temp += c; // add character to temp, ignore spaces
        }
        if (!temp.empty())
            mapFiles.push_back(temp); // add last map if any
        temp.clear();

        for (char c : pList)
        {
            if (c == ',')
            {
                playerStrategies.push_back(temp);
                temp.clear();
            }
            else if (!isspace(c))
                temp += c; // add character to temp, ignore spaces
        }
        if (!temp.empty())
            playerStrategies.push_back(temp); // add last strategy if any (after last comma)

        numGames = stoi(gNum); // convert to string to int
        maxTurns = stoi(dNum); // convert to string to int
    }
    // 2. Simulate the tournament
    cout << "Tournament mode:\n";
    cout << "M: ";
    for (auto &m : mapFiles)
        cout << m << " ";

    cout << "\nP: ";
    for (auto &p : playerStrategies)
        cout << p << " ";

    cout << "\nG: " << numGames << " D: " << maxTurns << endl;

    // Simulate each game on each map
    for (size_t mapIdx = 0; mapIdx < mapFiles.size(); ++mapIdx)
    {
        cout << "Map " << mapIdx + 1 << ": " << endl;
        for (int g = 0; g < numGames; ++g)
        {
            // //(Assignment 3 note: Here we would set up and run the actual game logic for each game on the map.)
            // // Simulate game (here you could call your actual game loop)
            // // For now, randomly pick a winner or draw
            // int winnerIndex = rand() % (playerStrategies.size() + 1); // last index = draw
            // if (winnerIndex < playerStrategies.size())
            //     cout << playerStrategies[winnerIndex] << " ";
            // else
            //     cout << "Draw ";

            // gameloop!
            changeState("loadmap");
            // we will start by loading the map
            loadMap(mapFiles[mapIdx]);

            changeState("validatemap");
            // next, map validation
            validateMap();

            // now we add the players
            // the player name will be the same as its strategy:)
            changeState("addplayer");
            for (int i = 0; i < playerStrategies.size(); i++)
            {
                addPlayers(playerStrategies[i]);
            }

            // starting the game
            changeState("gamestart");
            startGame();

            // entering the main game loop
            mainGameLoop(maxTurns);

            // the winner will be the only player left in the player vector,
            // if its a draw, all players are removed and Draw player is added
            winners.push_back(players->back());

            // cleanup before next game (we need to reset all the values)
            if (players)
            {
                for (Player *p : *players)
                {
                    delete p;
                }
                delete players;
                players = nullptr;
            }
            if (deck)
            {
                delete deck;
                deck = nullptr;
            }

            // play again! reset gamestate to start
            changeState("replay");
        }
        cout << endl;
        // TODO logging the results!
        // notify("Tournament mode:\n");
        // i have to send an object of a class we created that inherits from iloggable
        // not strings
        // perhaps I can make a custom command?
        //
    }

    cout << "\n===========End of tournament!============" << endl;
}

//-------------------------HELPER FUNCTIONS FOR GAME SETUP----------------------------
void GameEngine::loadMap(string filename)
{
    cout << "Loading map file: " << filename << endl;

    MapLoader loader;
    Map *loadedMap = loader.loadMap(filename);

    if (loadedMap == nullptr)
    {
        cout << "Failed to load map from file: " << filename << endl;
        return;
    }
    if (gameMap != nullptr)
    {
        delete gameMap;
    }
    gameMap = loadedMap;

    cout << "Map loaded successfully from filename:" << filename << endl;
}

void GameEngine::validateMap()
{
    if (gameMap == nullptr)
    {
        cout << "No map loaded" << endl;
        return;
    }

    cout << "Validating map..." << endl;
    bool isValid = gameMap->validate();

    if (isValid)
    {
        cout << "Map is valid!" << endl;
    }
    else
    {
        cout << "Map is invalid!" << endl;
    }
}

void GameEngine::addPlayers(string playerName)
{
    if (players == nullptr)
    {
        players = new std::vector<Player *>();
    }

    if (players->size() >= 6)
    {
        cout << "Maximum number of players reached." << endl;
        return;
    }

    Player *newPlayer = new Player(playerName);

    // checking the player strategy to assign
    // if a special strategy is used,that's their player name
    if (playerName == "Aggressive")
    {
        // assign aggressive player strategy
        PlayerStrategy *newStrategy = new AggressivePlayerStrategy(newPlayer);
        newPlayer->setStrategy(newStrategy);
    }
    else if (playerName == "Benevolent")
    {
        // assign benevolent player strategy
        PlayerStrategy *newStrategy = new BenevolentPlayerStrategy(newPlayer);
        newPlayer->setStrategy(newStrategy);
    }
    else if (playerName == "Neutral")
    {
        // assign neutral player strategy
        PlayerStrategy *newStrategy = new NeutralPlayerStrategy(newPlayer);
        newPlayer->setStrategy(newStrategy);
    }
    else if (playerName == "Cheater")
    {
        // assign cheater player strategy
        PlayerStrategy *newStrategy = new CheaterPlayerStrategy(newPlayer);
        newPlayer->setStrategy(newStrategy);
    }
    else
    {
        // if none of the special type, human strategy is assigned
        //  assign aggressive player strategy
        PlayerStrategy *newStrategy = new HumanPlayerStrategy(newPlayer);
        newPlayer->setStrategy(newStrategy);
    }

    // add player to the vector
    players->push_back(newPlayer);

    cout << "Player added: " << playerName << endl;
}

void GameEngine::startGame()
{
    cout << "\nStarting game setup..." << endl;
    // a) fairly distribute all the territories to the players
    cout << "Distributing territories..." << endl;
    gameMap->distributeTerritories(*players);

    // b) determine randomly the order of play of the players in the game
    cout << "Randomizing player order..." << endl;
    std::shuffle(players->begin(), players->end(), std::mt19937{std::random_device{}()});

    // ensure deck exists before drawing cards
    if (deck == nullptr)
    {
        cout << "Initializing deck..." << endl;
        deck = new Deck(); // ensure Deck has a default ctor; adjust if not
    }

    // c) give 50 initial army units to the players (placed in reinforcement pool)
    cout << "Assigning 50 armies per player..." << endl;
    for (auto *player : *players)
    {
        // give 50 initial army units to the players, which are placed in their respective reinforcement pool
        player->setReinforcementPool(50);
    }

    // d) let each player draw 2 initial cards from the deck
    cout << "Dealing 2 cards to each player..." << endl;
    for (auto *player : *players)
    {
        // check deck and hand validity inside draw if implemented; assuming valid here
        if (deck != nullptr)
        {
            deck->draw(player->getHand());
            deck->draw(player->getHand());
        }
    }
    cout << "Game setup complete." << endl;
}

//--------------------------THE GAME ENGINE OBJECT!!!!!!!!!!--------------------------------------//
// global variable to keep track of the status
// very important
GameEngine *theGameEngine = new GameEngine(new Start());

// listen has been replaced by getCommand and changeState
//-------------LISTEN-------------//
//  Takes user input
//  takes care of transitions
//  this is the method that controls everything in a way
//  void listen()
//  {
//      // Now, we will get commands from the commandProcessor!
//      // prompt user for command
//      theCommandProcessor->getCommand();
//      // now we can go check the vector of commands to get that command (if it is valid)
//      Command *command = theCommandProcessor->lastCommand();

//     string fullCmd = command->getCommandString();
//     string input;
//     string arg;

//     int indexOfSpace = fullCmd.find(' ');
//     if (indexOfSpace != string::npos)
//     {
//         input = fullCmd.substr(0, indexOfSpace);
//         arg = fullCmd.substr(indexOfSpace + 1);
//     }
//     else
//     {
//         input = fullCmd;
//         arg = "";
//     }

//     // essentially, now only some state changes will be triggered by the user/command line
//     // the other state changes will be done through other classes (i think, this is Jimmy's part)

//     // keep track of previous state
//     Status *oldStatus = theGameEngine->getState();
//     // gets the next state
//     Status *nextStatus = theGameEngine->getState()->transition(input, theGameEngine->getState());
//     // in this case, either the user gave a correct command and we switch to a new state
//     // or they gave an invalid command and we stay in the old state
//     // so we check to see if we stay in the old state:
//     if (nextStatus != oldStatus)
//     {
//         // if we don't, then we switch the state in GameEngine
//         theGameEngine->setState(nextStatus);
//     }
// };

// new function to handle state changes
// takes a string as input (state transition command) and then switches states accordingly.
void changeState(string input)
{
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
}

//--------------------------SWITCH STATUS-------------------------//
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
        // now the effect will be saved in the command object
        theCommandProcessor->lastCommand()->saveEffect("Transitions to the Start state");
        return newStatus;
        break;
    case 2:
        // switch to MapLoaded
        // create new MapLoaded object
        newStatus = new MapLoaded();
        cout << "==========Map Loaded===========" << endl;
        // now the effect will be saved in the command object
        theCommandProcessor->lastCommand()->saveEffect("Transitions to the map loaded state");
        //  return the modified pointer
        return newStatus;
        break;
    case 3:
        // switch to MapValidated
        // create new MapValidated object
        newStatus = new MapValidated();
        cout << "==========Map Validated=========" << endl;
        // now the effect will be saved in the command object
        theCommandProcessor->lastCommand()->saveEffect("Transitions to the map validated state");
        // return the modified pointer
        return newStatus;
        break;
    case 4:
        // switch to PlayersAdded
        // create new PlayersAdded object
        newStatus = new PlayersAdded();
        cout << "========Player Added========" << endl;
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
        cout << "\n======================= Reinforcement Phase =======================\n"
             << endl;
        // now the effect will be saved in the command object
        theCommandProcessor->lastCommand()->saveEffect("Transitions to the assign reinforcement state");
        // return the modified pointer
        return newStatus;
        break;
    case 6:
        // switch to IssueOrders
        // create new IssueOrders object
        newStatus = new IssueOrders();
        cout << "\n======================= Issuing Orders Phase =======================\n"
             << endl;
        // return the modified pointer
        return newStatus;
        break;
    case 7:
        // switch to ExecuteOrders
        // create new ExecuteOrders object
        newStatus = new ExecuteOrders();
        cout << "\n======================= Execute Orders Phase =======================" << endl;
        // return the modified pointer
        return newStatus;
        break;
    case 8:
        // switch to win
        // create new Win object
        newStatus = new Win();
        cout << "\n======================= End of the Game =======================" << endl;
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

/***
 * ------------------------- The Main Game Loop -------------------------------
 * This function will keep looping through the different phases of the game until the end condition is met.
 * TODO: Implement the end condition (a player conquers all territories)
 * For now, it will loop
 */
void GameEngine::mainGameLoop(int maxTurns)
{
    int maxRounds = maxTurns; // Default value is set to 5
    int rounds = 0;
    bool gameOver = false;
    while (gameOver != true)
    {
        // check if maxRounds got reached
        if (rounds == maxRounds)
        {
            // end of the game!
            gameOver = true;
            // remove all players
            for (Player *p : *players)
            {
                delete p;
            }
            // create new draw player
            Player *drawPlayer = new Player("Draw");
            // add them to the players list
            //  add player to the vector
            players->push_back(drawPlayer);

            cout << "\n===============DRAW===================" << endl;
            cout << "\n===Maximum turns have been reached.===" << endl;
            break;
        }
        cout << "\n================== ROUND " << rounds + 1 << " =================" << endl;
        if (rounds != 0)
        { // Do not distribute reinforcements in the first round
          // game state will go back to assign reinforcements
            changeState("endexecorders");
            reinforcementPhase();
            // switches to issue orders
            changeState("issueorder");
        }
        else
        {
            // will immediately switch to issue orders
            changeState("issueorder");
        }

        issueOrderPhase();
        changeState("issueordersend");
        executeOrderPhase();
        gameOver = isGameOver();
        rounds++;
    }
    theGameEngine->setState(new Win()); // Transition to Win state
}

/***
 * ------------------------- Reinforcement Phase -------------------------------
 * This function will handle the reinforcement phase of the game.
 * It will give players armies based on the number of territories they own and any continent bonuses. (# of territories / 3) + bonus
 * Minimum of 3 armies per turn.
 */
void GameEngine::reinforcementPhase()
{
    int ownedTerritories;
    int reinforcements;
    int continentBonus;

    // Loop through each player and calculate the reinforcements they will receive
    for (Player *player : *players)
    {
        ownedTerritories = player->toDefend()->size();      // Number of territories owned by the player
        reinforcements = std::max(3, ownedTerritories / 3); // Minimum of 3 armies per turn or # of territories / 3

        continentBonus = 0; // Continent bonus for players that own all territories in a continent
        std::vector<Continent *> *continents = gameMap->getContinents();
        for (Continent *continent : *continents)
        {                        // Loop through each continent and checks if the player doesn't own all territories
            bool ownsAll = true; // break if at least one territory is not owned by the player
            for (Territory *territory : *continent->getTerritories())
            {
                if (territory->getOwner() != player)
                {
                    ownsAll = false;
                    break;
                }
            }
            if (ownsAll)
            { // If the player does own all territories in the continent, add the bonus armies
                cout << "Player " << player->getName() << " owns all territories in continent " << continent->getName() << " and receives a bonus of " << continent->getBonusArmies() << " armies." << endl;
                continentBonus += continent->getBonusArmies();
            }
        }

        reinforcements += continentBonus; // Sum the reinforcements and continent bonus together

        player->addToReinforcementPool(reinforcements); // Update the player's reinforcement pool

        cout << "Player " << player->getName() << " receives " << reinforcements << " army reinforcement units." << endl;
    }
    // creates new command object heheheheh
    Command *issueOrderCommand = new Command("issueorder");
    // saves this new command
    theCommandProcessor->saveCommand(issueOrderCommand);
}

/***
 * ------------------------- Issue Order Phase -------------------------------
 * This function will handle the issue order phase of the game.
 * Each player will issue orders until they choose to end their turn.
 */
void GameEngine::issueOrderPhase()
{

    for (auto pIt = players->begin(); pIt != players->end();)
    { // Call the issueOrder method for each player
        Player *player = *pIt;
        cout << player->getName() << " is issuing orders." << endl;
        player->issueOrder();
        pIt++;
    }
}

/***
 * ------------------------- Execute Order Phase -------------------------------
 * This function will handle the execute order phase of the game.
 * Each player's orders will be validated and executed
 *
 */
void GameEngine::executeOrderPhase()
{

    int status = 0; // Status to track order execution success/failure, will be used to remove a card from the players hand
    bool noMoreOrders = false;

    DeployOrder *checkDeployOrder = nullptr;

    // ========== Deploy Orders First For All Players==========
    cout << "\nExecuting Deploy Orders First...\n"
         << endl;
    for (auto pIt = players->begin(); pIt != players->end();)
    {
        Player *player = *pIt; // Call the Validate and Execute for all orders for each player

        cout << player->getName() << " is executing orders." << endl;
        std::vector<std::unique_ptr<Orders>> &listOfOrders = player->getOrderList()->orderList; // Get the player's order list

        for (auto it = listOfOrders.begin(); it != listOfOrders.end();)
        { // Iterate through the player's order list
            std::unique_ptr<Orders> &order = *it;

            checkDeployOrder = dynamic_cast<DeployOrder *>(order.get()); // Check if the order is a deploy order
            if (checkDeployOrder != nullptr)
            { // If it is not a deploy order,prepare to break out of the loop to move to the next player
                order->execute(*player);
                player->getOrderList()->remove(*(order.get()));
            }
            else
            {
                it++; // Move to the next order if it is not a deploy order
            }
        }
        pIt++;
    }

    // ========== Searching For Negotiate Orders ==========
    cout << "\nExecuting Negotiate Orders...\n"
         << endl;
    for (auto pIt = players->begin(); pIt != players->end();)
    {
        Player *player = *pIt; // Call the Validate and Execute for all orders for each player

        cout << player->getName() << " is executing orders." << endl;
        std::vector<std::unique_ptr<Orders>> &listOfOrders = player->getOrderList()->orderList;

        for (auto it = listOfOrders.begin(); it != listOfOrders.end();)
        { // Iterate through the player's order list
            std::unique_ptr<Orders> &order = *it;

            Negotiate *checkNegotiateOrder = dynamic_cast<Negotiate *>(order.get()); // Check if the order is a negotiate order
            if (checkNegotiateOrder != nullptr)
            {                                                   // If it is not a negotiate order, check the next ordeer
                status = order->execute(*player);               // Execute the negotiate order
                player->getOrderList()->remove(*(order.get())); // Remove the executed order from the list
            }
            else
            {
                it++; // Move to the next order if it is not a negotiate order
            }
        }
        pIt++; // Move to the next player
    }

    cout << "\nExecuting Remaining Orders...\n"
         << endl;
    // ========== Then Execute All Other Orders ==========
    while (!noMoreOrders)
    {                        // Continue until all players have no more orders
        noMoreOrders = true; // Assume all players have no more orders
        for (Player *player : *players)
        { // Loop through each player
            std::vector<std::unique_ptr<Orders>> &listOfOrders = player->getOrderList()->orderList;

            if (!listOfOrders.empty())
            {                                                          // If the player has orders left to execute
                noMoreOrders = false;                                  // At least one player has orders left
                std::unique_ptr<Orders> &order = listOfOrders.front(); // Get the first order in the list
                order->execute(*player);                               // Execute the order
                // TODO: Remove Card from hand

                player->getOrderList()->remove(*(order.get())); // Remove the executed order from the list
            }
        }
    }
}

/***
 * ------------------------- Check for Game Over -------------------------------
 * This function will check if the game is over.by checking if there are only 1 player left
 * This function also removes players who have been eliminated (no territories left)
 * The game is over when a player conquers all territories.
 */
bool GameEngine::isGameOver()
{
    // Check if any player has no more territories
    for (auto it = players->begin(); it != players->end();)
    {
        Player *player = *it;

        if (player->toDefend()->empty())
        { // Would need to make sure that this list is updated properly
            cout << "Player " << player->getName() << " has been eliminated!" << endl;

            players->erase(std::remove(players->begin(), players->end(), player), players->end()); // Remove player from the game
            delete player;                                                                         // Free memory
            player = NULL;
        }
        else
        {
            ++it;
        }
    }

    // Check if only one player remains
    if (players->size() == 1)
    {
        cout << "Player " << (*players)[0]->getName() << " is the winner!" << endl;
        // game state will switch to win
        changeState("win");
        return true; // Game over
    }
    else
    {
        cout << players->size() << " players remain in the game." << endl;
    }

    return false; // Game continues
}

#include "PlayerStrategiesDriver.h"

#include "Player.h"
#include "PlayerStrategies.h"
#include "GameEngine.h"
#include "GameEngineDriver.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// namespace
// {
//     // Helper to display the expectation around an empty neutral strategy vector.
//     void printNeutralVectorResult(const vector<Territory *> *territories, const string &action)
//     {
//         if (territories == nullptr)
//         {
//             cout << "Received a null set of territories to " << action << "." << endl;
//             return;
//         }

//         if (territories->empty())
//         {
//             cout << "Neutral strategy correctly returned no territories to " << action << "." << endl;
//         }
//         else
//         {
//             cout << "Neutral strategy unexpectedly returned " << territories->size() << " territories to " << action << ":" << endl;
//             for (Territory *territory : *territories)
//             {
//                 if (territory != nullptr)
//                 {
//                     cout << " - " << territory->getName() << endl;
//                 }
//             }
//         }
//     }

    // void testNeutralPlayerStrategy()
    // {
    //     cout << "\n-- Neutral Player Strategy --" << endl;
    //     Player neutralPlayer("Neutral Strategist");
    //     neutralPlayer.setStrategy(new NeutralPlayerStrategy(&neutralPlayer));

    //     PlayerStrategy *strategy = neutralPlayer.getStrategy();

    //     const size_t ordersBefore = neutralPlayer.getOrderList()->orderList.size();
    //     cout << "Invoking issueOrder()..." << endl;
    //     strategy->issueOrder();
    //     const size_t ordersAfter = neutralPlayer.getOrderList()->orderList.size();

    //     if (ordersBefore == ordersAfter)
    //     {
    //         cout << "Order list unchanged (" << ordersAfter << " entries) as expected for a neutral player." << endl;
    //     }
    //     else
    //     {
    //         cout << "Order list size changed from " << ordersBefore << " to " << ordersAfter << "." << endl;
    //     }

    //     cout << "Checking attack targets..." << endl;
    //     vector<Territory *> *attackTargets = strategy->toAttack();
    //     printNeutralVectorResult(attackTargets, "attack");
    //     delete attackTargets;

    //     cout << "Checking defend targets..." << endl;
    //     vector<Territory *> *defendTargets = strategy->toDefend();
    void testNeutralPlayerStrategy() {
    cout << "\n========== TEST: Neutral -> Aggressive Transition ==========" << "\n";

    // --- Setup Player ---
    Player p("NeutralTestPlayer");
    p.setReinforcementPool(8); // ensure aggressive deploys armies
    p.setStrategy(new NeutralPlayerStrategy(&p));

    // Create a small scenario: one owned territory adjacent to an enemy territory
    auto* home = new Territory("Home");
    home->setOwner(&p);
    home->setArmies(5);
    p.addToDefend(home);

    Player enemy("EnemyPlayer");
    auto* enemyTerr = new Territory("EnemyLand");
    enemyTerr->setOwner(&enemy);
    enemyTerr->setArmies(4);

    // Link adjacencies so the aggressive player can find an attack target
    home->addAdjacentTerritory(enemyTerr);
    enemyTerr->addAdjacentTerritory(home);

    // Add a Bomb card so Bomb orders validate when executed
    p.getHand()->hand->push_back(new Card("Bomb"));

    cout << "Initial Strategy: NeutralPlayerStrategy\n";

    cout << "\nCalling issueOrder()...\n";
    p.issueOrder();
    cout << "Order list size = " << p.getOrderList()->orderList.size() << endl;

    // --- Simulate Being Attacked ---
    cout << "\nSimulating attack on player...\n";
    p.onAttacked();     // Direct manual trigger to show the effect

    cout << "\nCalling issueOrder() again after becoming Aggressive...\n";
    p.issueOrder();

    cout << "Order list size now = " 
         << p.getOrderList()->orderList.size() << endl;

    cout << "========== END TEST ==========" << "\n\n";
}

    void testAggressivePlayerStrategy()
    {

        cout << "\n-- Aggressive Player Strategy --" << endl;
        if (!theGameEngine){
            theGameEngine = new GameEngine(); // initialize the global engine
        }
        theGameEngine->loadMap("Short.map");
        theGameEngine->validateMap();
        theGameEngine->addPlayers("Alice");
        theGameEngine->addPlayers("Bob");

        LogObserver* logObserver = new LogObserver();
    

        std::vector<Player *>* players = theGameEngine->getPlayers();

        for(Player* p: *players){
            p->setStrategy(new AggressivePlayerStrategy(p));
            p->attach(logObserver);
            p->getOrderList()->attach(logObserver);
        }

        theGameEngine->startGame();
        theGameEngine->mainGameLoop();
        
        delete theGameEngine;
        delete logObserver;
        theGameEngine = nullptr;
        logObserver = nullptr;
        // cout << "\n-- Aggressive Player Strategy --" << endl;
        // Player aggressivePlayer("Aggressive Strategist");
        // aggressivePlayer.setStrategy(new AggressivePlayerStrategy(&aggressivePlayer));

        // PlayerStrategy *strategy = aggressivePlayer.getStrategy();

        // const size_t ordersBefore = aggressivePlayer.getOrderList()->orderList.size();
        // cout << "Invoking issueOrder()..." << endl;
        // strategy->issueOrder();
        // const size_t ordersAfter = aggressivePlayer.getOrderList()->orderList.size();

        // if (ordersAfter > ordersBefore)
        // {
        //     cout << "Order list increased from " << ordersBefore << " to " << ordersAfter << " as expected for an aggressive player." << endl;
        // }
        // else
        // {
        //     cout << "Order list size did not increase as expected for an aggressive player." << endl;
        // }

        // cout << "Aggressive player strategy test completed.\n" << endl;
    }

void testPlayerStrategies()
{
    cout << "========== Testing Player Strategies ==========" << endl;
    testNeutralPlayerStrategy();
    //testAggressivePlayerStrategy();
}

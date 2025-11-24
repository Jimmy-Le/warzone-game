#include "PlayerStrategiesDriver.h"

#include "Player.h"
#include "PlayerStrategies.h"
#include "GameEngine.h"
#include "GameEngineDriver.h"
#include "Orders.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void testBenevolentIgnoresBombCard();
void testAggressiveUsesHarmfulCards();

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

void testBenevolentPlayerStrategy() {
    cout << "\n========== TEST: Benevolent Airlift Card (Non-Harmful) ==========" << endl;

    Player benevolent("BenevolentCardUser");
    benevolent.setStrategy(new BenevolentPlayerStrategy(&benevolent));
    benevolent.setReinforcementPool(0); // focus on card-driven movement, not deployments

    // Set up two friendly territories with different army counts
    auto* weak = new Territory("WeakHold");
    weak->setOwner(&benevolent);
    weak->setArmies(2);

    auto* strong = new Territory("StrongHold");
    strong->setOwner(&benevolent);
    strong->setArmies(8);

    // Make them adjacent to allow existing benevolent move logic
    weak->addAdjacentTerritory(strong);
    strong->addAdjacentTerritory(weak);

    benevolent.addToDefend(weak);
    benevolent.addToDefend(strong);

    // Give the benevolent player an airlift card so validation succeeds
    benevolent.getHand()->hand->push_back(new Card("airlift"));

    cout << "Before issueOrder(): WeakHold armies = " << weak->getArmies()
         << ", StrongHold armies = " << strong->getArmies() << endl;

    benevolent.issueOrder();

    cout << "Orders created: " << benevolent.getOrderList()->orderList.size() << endl;

    // Execute the benevolent Airlift (purely defensive, between friendly territories)
    for (auto& ord : benevolent.getOrderList()->orderList) {
        if (dynamic_cast<Airlift*>(ord.get())) {
            cout << "Executing Airlift order..." << endl;
            ord->execute(benevolent);
        }
    }

    cout << "After Airlift: WeakHold armies = " << weak->getArmies()
         << ", StrongHold armies = " << strong->getArmies() << endl;
    cout << "========== END TEST ==========" << endl << endl;
}

void testBenevolentIgnoresBombCard() {
    cout << "\n========== TEST: Benevolent Ignores Bomb Card ==========" << endl;

    Player benevolent("BenevolentBombCheck");
    benevolent.setStrategy(new BenevolentPlayerStrategy(&benevolent));
    benevolent.setReinforcementPool(0);

    // Set up two friendly territories and one enemy territory for context
    auto* weak = new Territory("WeakHold");
    weak->setOwner(&benevolent);
    weak->setArmies(1);

    auto* strong = new Territory("StrongHold");
    strong->setOwner(&benevolent);
    strong->setArmies(6);

    auto* enemyTerr = new Territory("EnemyLand");
    Player enemy("EnemyPlayer");
    enemyTerr->setOwner(&enemy);
    enemyTerr->setArmies(5);

    // Adjacencies
    weak->addAdjacentTerritory(strong);
    strong->addAdjacentTerritory(weak);
    strong->addAdjacentTerritory(enemyTerr);
    enemyTerr->addAdjacentTerritory(strong);

    benevolent.addToDefend(weak);
    benevolent.addToDefend(strong);
    benevolent.addToAttack(enemyTerr);

    // Give an Airlift (allowed) and a Bomb (should be ignored by benevolent)
    benevolent.getHand()->hand->push_back(new Card("airlift"));
    benevolent.getHand()->hand->push_back(new Card("bomb"));

    cout << "Before issueOrder(): orders = " << benevolent.getOrderList()->orderList.size() << endl;
    benevolent.issueOrder();
    //since the issueOrders of the Benevolent does not issue any attacking orders though it may have card like bomb it cannot use it to harm anybody as it cannot issue
    //the order that would require the Bomb card 
    cout << "After issueOrder(): orders = " << benevolent.getOrderList()->orderList.size() << endl;

    bool hasBombOrder = false;
    bool hasAirliftOrder = false;
    for (auto& ord : benevolent.getOrderList()->orderList) {
        if (dynamic_cast<Bomb*>(ord.get())) hasBombOrder = true;
        if (dynamic_cast<Airlift*>(ord.get())) hasAirliftOrder = true;
    }

    cout << "Contains Bomb order? " << (hasBombOrder ? "YES (unexpected)" : "NO (as expected)") << endl;
    cout << "Contains Airlift order? " << (hasAirliftOrder ? "YES" : "NO") << endl;
    cout << "========== END TEST ==========" << endl << endl;
}


    // void testBenevolentPlayerStrategy(){
    //  cout << "\n-- Aggressive Player Strategy --" << endl;
    //     if (!theGameEngine){
    //         theGameEngine = new GameEngine(); // initialize the global engine
    //     }
    //     theGameEngine->loadMap("Earth.map");
    //     theGameEngine->validateMap();
    //     theGameEngine->addPlayers("Hakim");
    //     theGameEngine->addPlayers("Hanna");

    //     LogObserver* logObserver = new LogObserver();
    

    //     std::vector<Player *>* players = theGameEngine->getPlayers();

    //     for(Player* p: *players){
    //         p->setStrategy(new BenevolentPlayerStrategy(p));
    //         p->attach(logObserver);
    //         p->getOrderList()->attach(logObserver);
    //     }

    //     theGameEngine->startGame();
    //     theGameEngine->mainGameLoop();
        
    //     delete theGameEngine;
    //     delete logObserver;
    //     theGameEngine = nullptr;
    //     logObserver = nullptr;
    // }

    void testAggressivePlayerStrategy()
    {
        cout << "\n========== TEST: Aggressive Uses Harmful Cards ==========" << endl;
        cout<<"HUHUHU"<<endl;

        Player aggressive("Aggro");
        aggressive.setStrategy(new AggressivePlayerStrategy(&aggressive));
        aggressive.setReinforcementPool(6);

        // Friendly territories
        auto* strong = new Territory("Stronghold");
        strong->setOwner(&aggressive);
        strong->setArmies(10);

        auto* backup = new Territory("Backup");
        backup->setOwner(&aggressive);
        backup->setArmies(4);

        // Enemy territories adjacent to strongest
        Player enemyA("EnemyA");
        Player enemyB("EnemyB");
        auto* enemy1 = new Territory("EnemyFront");
        auto* enemy2 = new Territory("EnemyRear");
        enemy1->setOwner(&enemyA);
        enemy2->setOwner(&enemyB);
        enemy1->setArmies(5);
        enemy2->setArmies(3);

        // Adjacency for movement/attack
        strong->addAdjacentTerritory(backup);
        backup->addAdjacentTerritory(strong);
        strong->addAdjacentTerritory(enemy1);
        strong->addAdjacentTerritory(enemy2);
        enemy1->addAdjacentTerritory(strong);
        enemy2->addAdjacentTerritory(strong);

        aggressive.addToDefend(strong);
        aggressive.addToDefend(backup);

        // Provide harmful cards so validation passes; duplicate bombs show repeated harmful card usage
        aggressive.getHand()->hand->push_back(new Card("bomb"));
        aggressive.getHand()->hand->push_back(new Card("bomb"));

        cout << "Initial hand size: " << aggressive.getHand()->hand->size() << endl;
        cout << "Before issueOrder(): orders = " << aggressive.getOrderList()->orderList.size() << endl;

        aggressive.issueOrder();

        cout << "After issueOrder(): orders = " << aggressive.getOrderList()->orderList.size() << endl;

        int bombCount = 0;
        int advanceCount = 0;
        for (auto& ord : aggressive.getOrderList()->orderList) {
            if (dynamic_cast<Bomb*>(ord.get())) bombCount++;
            if (dynamic_cast<Advance*>(ord.get())) advanceCount++;
        }

        cout << "Bomb orders issued: " << bombCount << " (expected > 0 to show harmful card use)" << endl;
        cout << "Advance orders issued: " << advanceCount << " (attack and consolidation)" << endl;

        cout << "Executing Bomb orders to consume bomb cards..." << endl;
        for (auto& ord : aggressive.getOrderList()->orderList) {
            if (dynamic_cast<Bomb*>(ord.get())) {
                ord->execute(aggressive);
            }
        }

        cout << "Hand size after executing bombs: " << aggressive.getHand()->hand->size() << endl;
        cout << "EnemyFront armies after potential bombing: " << enemy1->getArmies() << endl;
        cout << "EnemyRear armies after potential bombing: " << enemy2->getArmies() << endl;
        cout << "========== END TEST ==========" << endl << endl;
    }

void testPlayerStrategies()
{   int choice = 0;
    cout << "========== Testing Player Strategies ==========" << endl;
    cout<<"1. Neutral Player Strategy"<<endl;
    cout<<"2. Aggressive Player Strategy"<<endl;
    cout<<"3. Benevolent Player Strategy"<<endl;
    cout<<"4. Cheater Player Strategy"<<endl;
    cout<<"5. Human Player Strategy"<<endl;
    cout<<"6. Aggressive Uses Harmful Cards"<<endl;
    cout<<"7. Benevolent Card (Non-Harmful Airlift)"<<endl;
    cout<<"8. Benevolent Ignores Bomb Card"<<endl;
     cout<<"Choose a specific strategy to test: "<<endl;
     cin >> choice;
    switch (choice)
    {
    case 1:
        cout<<"Testing Neutral Player Strategy"<<endl;
        testNeutralPlayerStrategy();
        break;
    
    case 2:
        cout<<"Testing Aggressive Player Strategy"<<endl;
        testAggressivePlayerStrategy();
        break;
    case 3:
    cout<<"Testing Benevolent Player Strategy"<<endl;
        testBenevolentPlayerStrategy();
        break;
    case 7:
        cout<<"Testing Benevolent Card (Non-Harmful Airlift)"<<endl;
        testBenevolentPlayerStrategy();
        break;
    case 8:
        cout<<"Testing Benevolent Ignores Bomb Card"<<endl;
        testBenevolentIgnoresBombCard();
        break;
    }


}

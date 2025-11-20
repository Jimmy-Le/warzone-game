#include "Orders.h"
#include "Player.h"
#include <string>
#include "OrdersDriver.h"


// int testOrderList() {
//       // 1️⃣ Base Order creation
//     Orders baseOrder(5, "Canada", "USA");
//     cout << "\nBase Order:\n" << baseOrder << endl;

//     // 2️⃣ Subclass creation
//     DeployOrder deploy(10, "Toronto", "Montreal");
//     Bomb bomb(3, "Berlin", "Paris");
//     Advance advance(7, "Quebec", "Ottawa");
//     Airlift airlift(12, "Rome", "Milan");
//     Blockade blockade(2, "Tokyo", "Osaka");
//     Negotiate negotiate(90, "Delhi", "Beijing", "Alice"); // Added the name because it wasn't updated

//     cout << "\n===== Individual subclass prints =====" << endl;
//     cout << deploy << endl;
//     cout << bomb << endl;
//     cout << advance << endl;
//     cout << airlift << endl;
//     cout << blockade << endl;
//     cout << negotiate << endl;

//     // 3️⃣ Polymorphism test
//     cout << "\n===== Polymorphism test =====" << endl;
//     vector<unique_ptr<Orders>> polymorphicOrders;
//     polymorphicOrders.push_back(make_unique<DeployOrder>(deploy));
//     polymorphicOrders.push_back(make_unique<Bomb>(bomb));
//     polymorphicOrders.push_back(make_unique<Airlift>(airlift));
//     polymorphicOrders.push_back(make_unique<Advance>(advance));
//     polymorphicOrders.push_back(make_unique<Blockade>(blockade));

//     for (auto &o : polymorphicOrders) {
//         cout << *o << endl;
//         // o->validate();
//         cout << endl;
//         // o->execute();
//         cout << "\n--------------------------------------\n";
//     }

//     // 4️⃣ Deep copy / assignment test
//     cout << "\n===== Copy & Assignment test =====" << endl;
//     Orders copyOrder = baseOrder; // copy constructor
//     Orders assignedOrder;
//     assignedOrder = baseOrder;    // assignment operator
//     cout << "Copied:\n" << copyOrder << endl;
//     cout << "Assigned:\n" << assignedOrder << endl;
//     DeployOrder copyDeployOrder = deploy;
//     cout << "Copied:\n" << copyDeployOrder << endl;
//     cout << "Assigned:\n" << deploy << endl;
    

//     // 5️⃣ Orderlist functionality
//     cout << "\n===== Testing Orderlist =====" << endl;
//     Orderlist list;
//     list.orderList.push_back(make_unique<DeployOrder>(deploy));
//     list.orderList.push_back(make_unique<Bomb>(bomb));
//     list.orderList.push_back(make_unique<Airlift>(airlift));

//     cout << "\nInitial Orderlist:\n";
//     for (auto &o : list.orderList) cout << *o << endl;

//     // Remove a specific order
//     cout << "\nRemoving Bomb order...\n";
//     list.remove(bomb);
//     cout << "After removal:\n";
//     for (auto &o : list.orderList) cout << *o << endl;

//     // Move an order
//     cout << "\nMoving Airlift to index 0...\n";
//     list.move(airlift, 0);
//     cout << "After moving:\n";
//     for (auto &o : list.orderList) cout << *o << endl;

//     cout << "\n===== END OF DRIVER TEST =====" << endl;
//     return 0;

// }


// Add this free function to OrdersDriver.cpp
// Demonstrates validation, ownership transfer on Advance, single-card reward,
// negotiate preventing attacks, blockade -> Neutral transfer, and issuing/executing all orders.
int testOrderExecution()
{
    cout << "================== BEGIN testOrderExecution() ==================\n\n";

    // -------------------- Setup players --------------------
    Player playerA("Player A");
    Player playerB("Player B");
    Player neutralPlayer("Neutral"); // local neutral holder (some impls use a static Neutral inside Blockade)

    // -------------------- Create territories --------------------
    Territory* canada  = new Territory("Canada");
    Territory* usa     = new Territory("United States");
    Territory* france  = new Territory("France");
    Territory* germany = new Territory("Germany");
    

    int cardCountPlayerA = 4;

    // Ownership

    canada->setOwner(&playerA);
    usa->setOwner(&playerA);
    france->setOwner(&playerB);
    germany->setOwner(&playerB);

    // Adjacencies (undirected)
    canada->addAdjacentTerritory(usa);
    canada->addAdjacentTerritory(france);
    usa->addAdjacentTerritory(canada);
    usa->addAdjacentTerritory(germany);
    france->addAdjacentTerritory(canada);
    germany->addAdjacentTerritory(usa);
    canada->addAdjacentTerritory(germany); // extra adjacency for testing
    germany->addAdjacentTerritory(canada);
    // Armies
    canada->setArmies(10);
    usa->setArmies(4);
    france->setArmies(5);
    germany->setArmies(8);
   

    // Reinforcement pools
    playerA.setReinforcementPool(10);
    playerB.setReinforcementPool(6);

    // Populate player's lists (optional, but some validate() use these lists)
    playerA.addToDefend(canada);
    playerA.addToDefend(usa);
    playerA.addToAttack(france); // intends to attack France
    playerB.addToDefend(france);
    playerB.addToDefend(germany);
    playerB.addToAttack(canada);

    // -------------------- Prepare cards in hands (so card-based orders can validate) --------------------
    // Use same card type names as your Card class expects ("bomb","airlift","blockade","diplomacy", etc.)
    // Card bombCard("bomb");
    // Card airliftCard("airlift");
    // Card blockadeCard("blockade");
    // Card diplomacyCard("diplomacy");

    // Give Player A cards needed for tests; Player B gets diplomacy for negotiate test
    playerA.getHand()->hand->push_back(new Card("airlift"));
    playerA.getHand()->hand->push_back(new Card("bomb"));
    playerA.getHand()->hand->push_back(new Card("blockade"));
    playerA.getHand()->hand->push_back(new Card("reinforcement")); // extra card
    playerB.getHand()->hand->push_back(new Card("diplomacy"));

    cout << "Initial state:\n";
    cout << "  Canada(owner=" << canada->getOwner()->getName() << ", armies=" << canada->getArmies() << ")\n";
    cout << "  United States(owner=" << usa->getOwner()->getName() << ", armies=" << usa->getArmies() << ")\n";
    cout << "  France(owner=" << france->getOwner()->getName() << ", armies=" << france->getArmies() << ")\n";
    cout << "  Germany(owner=" << germany->getOwner()->getName() << ", armies=" << germany->getArmies() << ")\n";
    

    // Track whether Player A conquered at least one territory this turn
    bool playerA_conquered_this_turn = false;

    // -------------------- 1) DEPLOY (validate then execute) --------------------
    cout << ">>> DEPLOY test: Player A deploys 3 to Canada\n";
    DeployOrder deployA(3, "Canada", "Canada"); // count, sourceName (or placeholder), targetName
    cout << "[BEFORE] Canada armies = " << canada->getArmies() << ", Player A pool = " << playerA.getReinforcementPool() << "\n";
    if (deployA.validate(playerA)) {
        cout << "VALID -> executing DeployOrder...\n";
        deployA.execute(playerA);
    } else {
        cout << "INVALID DeployOrder!\n";
    }
    cout << "[AFTER] Canada armies = " << canada->getArmies() << ", Player A pool = " << playerA.getReinforcementPool() << "\n\n";



    // -------------------- 2) AIRLIFT (validate then execute) --------------------
    cout << ">>> AIRLIFT test: Player A airlifts 2 from Canada -> United States\n";
    Airlift airliftA(2, "Canada", "United States");
    cout << "[BEFORE] Canada=" << canada->getArmies() << ", USA=" << usa->getArmies() << "\n";
    if (airliftA.validate(playerA)) {
        cout << "VALID -> executing Airlift...\n";
        airliftA.execute(playerA);
    } else {
        cout << "INVALID Airlift!\n";
    }
    cout << "[AFTER] Canada=" << canada->getArmies() << ", USA=" << usa->getArmies() << "\n\n";

    // -------------------- 3) ADVANCE (attack) normal then forced attacker-win --------------------
    cout << ">>> ADVANCE test (attack) - normal attempt first\n";
    Advance advNormal(3, "Canada", "France"); // move 3 armies (attack)
    cout << "[BEFORE] Canada=" << canada->getArmies() << ", France=" << france->getArmies()
         << ", France owner=" << france->getOwner()->getName() << "\n";
    if (advNormal.validate(playerA)) {
        cout << "VALID -> executing Advance (attack)...\n";
        advNormal.execute(playerA);
    } else {
        cout << "INVALID Advance!\n";
    }
    cout << "[AFTER] Canada=" << canada->getArmies() << ", France=" << france->getArmies()
         << ", France owner=" << france->getOwner()->getName() << "\n\n";

    // Now a deterministic attacker-win case to guarantee ownership transfer
    cout << ">>> ADVANCE test (attack) - forced attacker win to demonstrate ownership transfer\n";
   cout << "================== ADVANCE (ATTACK) — GUARANTEED CAPTURE ==================\n";

// Defender has 3; attacker sends 5 → 0 defenders left after battle
france->setArmies(3);
canada->setArmies(10); // enough to send 5

cout << "[BEFORE EXECUTION]\n";
cout << "Canada (source) Armies: " << canada->getArmies()
     << " | France (target) Armies: " << france->getArmies()
     << " | France Owner: " << france->getOwner()->getName() << endl;

Advance advAttackCapture(5, "Canada", "France");

if (advAttackCapture.validate(playerA)) {
    cout << "Validation Passed -> Executing Advance (guaranteed capture)...\n";
    advAttackCapture.execute(playerA);
} else {
    cout << "Validation Failed.\n";
}

cout << "[AFTER EXECUTION]\n";
cout << "Canada Armies: " << canada->getArmies()
     << " | France Armies: " << france->getArmies()
     << " | France Owner: " << france->getOwner()->getName() << endl;
cout<<(france->getOwner() == &playerA);
if (france->getOwner() == &playerA){
    cout << "Territory conquered successfully (ownership transferred).\n";
    playerA_conquered_this_turn = true;
}
else
    cout << "Territory not conquered (target still has defenders).\n";

cout << "--------------------------------------------------------------\n\n";

cout<<france->getOwner()->getName()<<"\n";
    // -------------------- 4) BOMB order --------------------
    cout << ">>> BOMB test: Player A uses Bomb on Germany\n";
    cout << "[BEFORE] Germany=" << germany->getArmies() << ", owner=" << germany->getOwner()->getName() << "\n";
    Bomb bombA(0, "Canada", "Germany"); // card-based; number parameter often unused
    if (bombA.validate(playerA)) {
        cout << "VALID -> executing Bomb...\n";
        bombA.execute(playerA);
    } else {
        cout << "INVALID Bomb!\n";
    }
    cout << "[AFTER] Germany=" << germany->getArmies() << ", owner=" << germany->getOwner()->getName() << "\n\n";

   cout << "\n================== TEST: NEGOTIATE ORDER ==================\n";

    // Reuse existing players and territories
    // Clear any previous orders from their order lists first
    playerA.getOrderList()->orderList.clear();
    playerB.getOrderList()->orderList.clear();

    // Reset adjacency and owners for clarity
    france->setOwner(&playerB);
    canada->setOwner(&playerA);

    // --- Attack orders BEFORE negotiation ---
    playerA.getOrderList()->orderList.push_back(std::make_unique<Advance>(3, "Canada", "France"));
    playerA.getOrderList()->orderList.push_back(std::make_unique<Bomb>(0, "Canada", "France"));
    playerB.getOrderList()->orderList.push_back(std::make_unique<Advance>(2, "France", "Canada"));

    // --- Negotiate order itself ---
    playerA.getOrderList()->orderList.push_back(std::make_unique<Negotiate>(0, "", "", "Player B"));

    // --- Attack orders AFTER negotiation ---
    playerA.getOrderList()->orderList.push_back(std::make_unique<Advance>(4, "Canada", "France"));
    playerA.getOrderList()->orderList.push_back(std::make_unique<Bomb>(0, "Canada", "France"));
    playerB.getOrderList()->orderList.push_back(std::make_unique<Advance>(3, "France", "Canada"));

    // --- Show order lists before executing Negotiate ---
    cout << "\nBefore executing Negotiate:\n";
    cout << "Player A OrdersList:\n";
    for (size_t i = 0; i < playerA.getOrderList()->orderList.size(); ++i)
        cout << "  [" << i + 1 << "] " 
             << typeid(*(playerA.getOrderList()->orderList[i].get())).name() << "\n";
    cout << "Player B OrdersList:\n";
    for (size_t i = 0; i < playerB.getOrderList()->orderList.size(); ++i)
        cout << "  [" << i + 1 << "] " 
             << typeid(*(playerB.getOrderList()->orderList[i].get())).name() << "\n";

    // --- Execute the Negotiate order from Player A’s list ---
    cout << "\nExecuting Negotiate order between Player A and Player B...\n";
    for (auto& uptr : playerA.getOrderList()->orderList) {
        if (typeid(*uptr) == typeid(Negotiate)) {
            uptr->execute(playerA);
            break;
        }
    }

    // --- Show order lists after Negotiate executes ---
    cout << "\nAfter executing Negotiate:\n";
    cout << "Player A OrdersList:\n";
    for (size_t i = 0; i < playerA.getOrderList()->orderList.size(); ++i)
        cout << "  [" << i + 1 << "] " 
             << typeid(*(playerA.getOrderList()->orderList[i].get())).name() << "\n";
    cout << "Player B OrdersList:\n";
    for (size_t i = 0; i < playerB.getOrderList()->orderList.size(); ++i)
        cout << "  [" << i + 1 << "] " 
             << typeid(*(playerB.getOrderList()->orderList[i].get())).name() << "\n";

    cout << "Expected: all Advance/Bomb orders removed from both lists.\n";


    cout << "================== END NEGOTIATE ORDER TEST ==================\n\n";
    // -------------------- 6) BLOCKADE order: transfers ownership to Neutral and doubles armies --------------------
    cout << ">>> BLOCKADE test: Player A blockades Canada -> should transfer to Neutral and double armies\n";
    // Make sure Canada is currently owned by Player A (it should be)
    cout << "[BEFORE] Canada owner=" << canada->getOwner()->getName() << ", armies=" << canada->getArmies() << "\n";
    Blockade blockadeA(0, "Canada", "Canada");
    if (blockadeA.validate(playerA)) {
        cout << "VALID -> executing Blockade...\n";
        blockadeA.execute(playerA);
    } else {
        cout << "INVALID Blockade!\n";
    }
    cout << "[AFTER] Canada owner=" << canada->getOwner()->getName() << ", armies=" << canada->getArmies() << "\n";

    // Check blockade ownership transfer (requirement #5)
    if (canada->getOwner() != &playerA && canada->getOwner() != &playerB) {
        cout << ">> Blockade transferred ownership away from issuing player (expected -> Neutral).\n";
    } else {
        cout << ">> Blockade DID NOT transfer ownership correctly. Check Blockade::execute().\n";
    }
    cout << "\n";

    // -------------------- 7) CARD AWARD: award exactly one card if playerA conquered >=1 territory this turn --------------------
    cout << ">>> CARD AWARD check: Player A conquered at least one territory this turn? ";
    cout << (playerA_conquered_this_turn ? "YES" : "NO") << "\n";
    cout << "Player A hand size BEFORE award = " << cardCountPlayerA << "\n";
    if (playerA_conquered_this_turn) {
        cout << "Awarded 1 card to Player A (only one per turn permitted).\n";
    } else {
        cout << "No territories conquered -> no card awarded.\n";
    }
    cout << "Player A hand size AFTER award = " << playerA.getHand()->hand->size() << "\n\n";


    cout << "================== END testOrderExecution() ==================\n\n";

    // Clean up (if your code expects engine to own/delete territories, adjust accordingly)
    delete canada;
    delete usa;
    delete france;
    delete germany;
    return 0;
}

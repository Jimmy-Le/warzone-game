#include "Orders.h"
#include "Player.h"
#include <string>
#include "OrdersDriver.h"


int testOrderList() {
      // 1️⃣ Base Order creation
    Orders baseOrder(5, "Canada", "USA");
    cout << "\nBase Order:\n" << baseOrder << endl;

    // 2️⃣ Subclass creation
    DeployOrder deploy(10, "Toronto", "Montreal");
    Bomb bomb(3, "Berlin", "Paris");
    Advance advance(7, "Quebec", "Ottawa");
    Airlift airlift(12, "Rome", "Milan");
    Blockade blockade(2, "Tokyo", "Osaka");
    Negotiate negotiate(90, "Delhi", "Beijing", "Alice"); // Added the name because it wasn't updated

    cout << "\n===== Individual subclass prints =====" << endl;
    cout << deploy << endl;
    cout << bomb << endl;
    cout << advance << endl;
    cout << airlift << endl;
    cout << blockade << endl;
    cout << negotiate << endl;

    // 3️⃣ Polymorphism test
    cout << "\n===== Polymorphism test =====" << endl;
    vector<unique_ptr<Orders>> polymorphicOrders;
    polymorphicOrders.push_back(make_unique<DeployOrder>(deploy));
    polymorphicOrders.push_back(make_unique<Bomb>(bomb));
    polymorphicOrders.push_back(make_unique<Airlift>(airlift));
    polymorphicOrders.push_back(make_unique<Advance>(advance));
    polymorphicOrders.push_back(make_unique<Blockade>(blockade));

    for (auto &o : polymorphicOrders) {
        cout << *o << endl;
        // o->validate();
        cout << endl;
        // o->execute();
        cout << "\n--------------------------------------\n";
    }

    // 4️⃣ Deep copy / assignment test
    cout << "\n===== Copy & Assignment test =====" << endl;
    Orders copyOrder = baseOrder; // copy constructor
    Orders assignedOrder;
    assignedOrder = baseOrder;    // assignment operator
    cout << "Copied:\n" << copyOrder << endl;
    cout << "Assigned:\n" << assignedOrder << endl;
    DeployOrder copyDeployOrder = deploy;
    cout << "Copied:\n" << copyDeployOrder << endl;
    cout << "Assigned:\n" << deploy << endl;
    

    // 5️⃣ Orderlist functionality
    cout << "\n===== Testing Orderlist =====" << endl;
    Orderlist list;
    list.orderList.push_back(make_unique<DeployOrder>(deploy));
    list.orderList.push_back(make_unique<Bomb>(bomb));
    list.orderList.push_back(make_unique<Airlift>(airlift));

    cout << "\nInitial Orderlist:\n";
    for (auto &o : list.orderList) cout << *o << endl;

    // Remove a specific order
    cout << "\nRemoving Bomb order...\n";
    list.remove(bomb);
    cout << "After removal:\n";
    for (auto &o : list.orderList) cout << *o << endl;

    // Move an order
    cout << "\nMoving Airlift to index 0...\n";
    list.move(airlift, 0);
    cout << "After moving:\n";
    for (auto &o : list.orderList) cout << *o << endl;

    cout << "\n===== END OF DRIVER TEST =====" << endl;
    return 0;

}


int testOrderExecution()
{
     // ---------- SETUP ----------
    Player playerA("Player A");
    Player playerB("Player B");
    Player neutral("Neutral");

    Territory* canada  = new Territory("Canada");
    Territory* usa     = new Territory("United States");
    Territory* france  = new Territory("France");
    Territory* germany = new Territory("Germany");

    // --- Ownerships ---
    canada->setOwner(&playerA);
    usa->setOwner(&playerA);
    france->setOwner(&playerB);
    germany->setOwner(&playerB);

    // --- Adjacency setup ---
    canada->addAdjacentTerritory(usa);
    canada->addAdjacentTerritory(france);
    usa->addAdjacentTerritory(canada);
    usa->addAdjacentTerritory(germany);
    france->addAdjacentTerritory(canada);
    germany->addAdjacentTerritory(usa);

    // --- Armies ---
    canada->setArmies(10);
    usa->setArmies(5);
    france->setArmies(8);
    germany->setArmies(6);

    // --- Player lists ---
    playerA.addToDefend(canada);
    playerA.addToDefend(usa);
    playerA.addToAttack(france);
    playerB.addToDefend(france);
    playerB.addToDefend(germany);
    playerB.addToAttack(canada);

    // --- Reinforcement pools ---
    playerA.setReinforcementPool(20);
    playerB.setReinforcementPool(15);

    // --- Cards (manual way, no addCard) ---
    Card bombCard("bomb");
    Card airliftCard("airlift");
    Card blockadeCard("blockade");
    Card diplomacyCard("diplomacy");
    Card playerBDiplomacyCard("diplomacy");

    playerA.getHand()->hand->push_back(bombCard);
    playerA.getHand()->hand->push_back(airliftCard);
    playerA.getHand()->hand->push_back(blockadeCard);
    playerA.getHand()->hand->push_back(diplomacyCard);
    playerB.getHand()->hand->push_back(playerBDiplomacyCard);

    cout << ">>> INITIAL SETUP COMPLETE.\n";
    cout << "Player A Reinforcements: " << playerA.getReinforcementPool() << endl;
    cout << "Player B Reinforcements: " << playerB.getReinforcementPool() << endl << endl;
    cout << "Canada Armies: " << canada->getArmies() 
         << ", USA Armies: " << usa->getArmies() << endl;
    cout << "France Armies: " << france->getArmies() 
         << ", Germany Armies: " << germany->getArmies() << endl;
    cout << "--------------------------------------------------------------\n\n";

    // ============================================================
    // 1 DEPLOY ORDER
    // ============================================================
    cout << "========================= DEPLOY ORDER =======================\n";
    DeployOrder deployOrder(5, "Canada", "Canada");

    cout << "[BEFORE EXECUTION]\n";
    cout << "Canada Armies: " << canada->getArmies() 
         << ", Reinforcement Pool: " << playerA.getReinforcementPool() << endl;

    if (deployOrder.validate(playerA)) {
        cout << "Validation Passed -> Executing Deploy...\n";
        deployOrder.execute(playerA);
    } else {
        cout << "Validation Failed.\n";
    }

    cout << "[AFTER EXECUTION]\n";
    cout << "Canada Armies: " << canada->getArmies() 
         << ", Reinforcement Pool: " << playerA.getReinforcementPool() << endl;
    cout << "--------------------------------------------------------------\n\n";

    // ============================================================
    // 2 ADVANCE (MOVE)
    // ============================================================
    cout << "======================= ADVANCE (MOVE) =======================\n";
    Advance advMove(3, "Canada", "United States");

    cout << "[BEFORE EXECUTION]\n";
    cout << "Canada Armies: " << canada->getArmies() 
         << " | USA Armies: " << usa->getArmies() << endl;

    if (advMove.validate(playerA)) {
        cout << "Validation Passed -> Executing Advance (Move)...\n";
        advMove.execute(playerA);
    } else {
        cout << "Validation Failed.\n";
    }

    cout << "[AFTER EXECUTION]\n";
    cout << "Canada Armies: " << canada->getArmies() 
         << " | USA Armies: " << usa->getArmies() << endl;
    cout << "--------------------------------------------------------------\n\n";

    // ============================================================
    // 3 ADVANCE (ATTACK)
    // ============================================================
    cout << "======================= ADVANCE (ATTACK) =====================\n";
    Advance advAttack(5, "Canada", "France");

    cout << "[BEFORE EXECUTION]\n";
    cout << "Canada Armies: " << canada->getArmies() 
         << " | France Armies: " << france->getArmies() 
         << " | France Owner: " << france->getOwner()->getName() << endl;

    if (advAttack.validate(playerA)) {
        cout << "Validation Passed -> Executing Advance (Attack)...\n";
        advAttack.execute(playerA);
    } else {
        cout << "Validation Failed.\n";
    }

    cout << "[AFTER EXECUTION]\n";
    cout << "Canada Armies: " << canada->getArmies() 
         << " | France Armies: " << france->getArmies() 
         << " | France Owner: " << france->getOwner()->getName() << endl;
    cout << "--------------------------------------------------------------\n\n";

    // ============================================================
    // 4 BOMB
    // ============================================================
    cout << "=========================== BOMB ORDER =======================\n";
    Bomb bombOrder(0, "Canada", "Germany");

    cout << "[BEFORE EXECUTION]\n";
    cout << "Germany Armies: " << germany->getArmies() << endl;

    if (bombOrder.validate(playerA)) {
        cout << "Validation Passed -> Executing Bomb...\n";
        bombOrder.execute(playerA);
    } else {
        cout << "Validation Failed.\n";
    }

    cout << "[AFTER EXECUTION]\n";
    cout << "Germany Armies: " << germany->getArmies() << endl;
    cout << "--------------------------------------------------------------\n\n";

    // ============================================================
    // 5 AIRLIFT
    // ============================================================
    cout << "========================== AIRLIFT ORDER =====================\n";
    Airlift airOrder(2, "Canada", "United States");

    cout << "[BEFORE EXECUTION]\n";
    cout << "Canada Armies: " << canada->getArmies() 
         << " | USA Armies: " << usa->getArmies() << endl;

    if (airOrder.validate(playerA)) {
        cout << "Validation Passed -> Executing Airlift...\n";
        airOrder.execute(playerA);
    } else {
        cout << "Validation Failed.\n";
    }

    cout << "[AFTER EXECUTION]\n";
    cout << "Canada Armies: " << canada->getArmies() 
         << " | USA Armies: " << usa->getArmies() << endl;
    cout << "--------------------------------------------------------------\n\n";

    // ============================================================
    // 6 BLOCKADE
    // ============================================================
    cout << "========================== BLOCKADE ORDER ====================\n";
    Blockade blockOrder(0, "United States", "United States");

    cout << "[BEFORE EXECUTION]\n";
    cout << "USA Armies: " << usa->getArmies() 
         << " | Owner: " << usa->getOwner()->getName() << endl;

    if (blockOrder.validate(playerA)) {
        cout << "Validation Passed -> Executing Blockade...\n";
        blockOrder.execute(playerA);
    } else {
        cout << "Validation Failed.\n";
    }

    cout << "[AFTER EXECUTION]\n";
    cout << "USA Armies: " << usa->getArmies() 
         << " | Owner: " << usa->getOwner()->getName() << endl;
    cout << "--------------------------------------------------------------\n\n";

    // ============================================================
    // 7 NEGOTIATE
    // ============================================================
    cout << "========================== NEGOTIATE ORDER ===================\n";
    Negotiate negoOrder(0, "", "", "Player B");

    cout << "[BEFORE EXECUTION]\n";
    cout << "Checking if hostile orders exist between Player A and Player B...\n";

    if (negoOrder.validate(playerA)) {
        cout << "Validation Passed -> Executing Negotiate...\n";
        negoOrder.execute(playerA);
    } else {
        cout << "Validation Failed.\n";
    }

    cout << "[AFTER EXECUTION]\n";
    cout << "Diplomacy pact active: attacks between Player A and Player B canceled.\n";
    cout << "--------------------------------------------------------------\n\n";

    // ============================================================
    //  CARD REWARD CHECK
    // ============================================================
    cout << "====================== CARD REWARD CHECK =====================\n";
    cout << "If Player A conquered a territory -> reward card drawn.\n";
    cout << "Player A Hand Size: " << playerA.getHand()->hand->size() << endl;
    cout << "--------------------------------------------------------------\n\n";

    // ============================================================
    //  FINAL SUMMARY
    // ============================================================
    cout << "========================== FINAL STATE ========================\n";
    cout << "Canada   -> Owner: " << canada->getOwner()->getName() 
         << ", Armies: " << canada->getArmies() << endl;
    cout << "USA      -> Owner: " << usa->getOwner()->getName() 
         << ", Armies: " << usa->getArmies() << endl;
    cout << "France   -> Owner: " << france->getOwner()->getName() 
         << ", Armies: " << france->getArmies() << endl;
    cout << "Germany  -> Owner: " << germany->getOwner()->getName() 
         << ", Armies: " << germany->getArmies() << endl;
    cout << "==============================================================\n";
    cout << "End of testOrderExecution().\n";
    return 0;
}

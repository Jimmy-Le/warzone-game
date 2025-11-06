#include "Orders.h"
#include <iostream>
#include <vector>

using namespace std;

//testing deploy order
// int main() {
// 	DeployOrder *d1 = new DeployOrder(5, "England", "Mexico");
// 	Player *p = new Player();
// 	p->setReinforcementPool(30);
// 	d1->execute(*p);
// 	cout << "Player's reinforcement pool after deploy: " << p->getReinforcementPool() << endl;
// 	cout<< "Mexico army should have increased: " << p->toDefend()->at(0)->getArmies() << endl;
// 	delete p;
// 	delete d1;
// 	return 0;
// }
//NOTE: Okay i am done with testing functionality of deploy order >>PASS


//testing advance order
// int main() {
//     Player attacker("Umer");
//     Player defender("Jabeel");

//     Deck deck;
//     Territory* A = new Territory("A");
//     Territory* B = new Territory("B");
//     A->setArmies(50);
//     A->setOwner(&attacker);
//     B->setOwner(&defender);
//     A->addAdjacentTerritory(B);
//     cout<< A->isAdjacent(B) <<endl ;

//     B->addAdjacentTerritory(A);
//     cout<<B->isAdjacent(A) <<endl;

//     attacker.toDefend()->push_back(A);
//     attacker.toAttack()->push_back(B);
 
//     Advance order(20, "A", "B");
// 		cout<<"Before battle:\n";
// 		cout << "A armies: " << A->getArmies()
// 				 << "\nB armies: " << B->getArmies()
// 				 << "\nB owner: " << (B->getOwner() == &attacker ? "Attacker" : "Defender") << endl;
//     order.execute(attacker);
//     cout << "\nAfter battle:\n";
//     cout << "A armies: " << A->getArmies()
//          << "\nB armies: " << B->getArmies()
//          << "\nB owner: " << (B->getOwner() == &attacker ? "Attacker" : "Defender") << endl;
// delete A;
// delete B;
//         }
//NOTE: Okay doen with testing the Advance order all edge cases PASSED

// int main() {
//     cout << "\n====== TESTING AIRLIFT ORDER ======\n";

//     Player player("Umer");
// 		Card airliftCard("Airlift");
// 		player.getHand()->hand->push_back(airliftCard); // Give player an Airlift card

//     // Create two territories NOT adjacent to simulate Airlift bypass
//     Territory source("Base");
//     Territory target("Outpost");

//     source.setOwner(&player);
//     target.setOwner(&player);
//     source.addAdjacentTerritory(&target);

//     player.toDefend()->push_back(&source);
//     player.toDefend()->push_back(&target);

//     // Create an Airlift order (move 8 armies from Base → Outpost)
//     Airlift airliftOrder(8, "Base", "Outpost");

//     cout << "\nBefore Airlift:\n";
//     cout << "Base armies = " << source.getArmies()
//          << "\nOutpost armies = " << target.getArmies() << endl;

//     airliftOrder.execute(player);

//     cout << "\nAfter Airlift:\n";
//     cout << "Base armies = " << source.getArmies()
//          << "\nOutpost armies = " << target.getArmies() << endl;

//     cout << "\n Expected behavior:\n"
//          << "-> Armies moved even if territories not adjacent.\n"
//          << "-> Source decreases by 8, target increases by 8.\n";

//     return 0;
// }



// int main() {
//     cout << "\n====== TESTING BOMB ORDER ======\n";

//     // --- Setup players ---
//     Player attacker("Umer");
//     Player defender("Enemy");

//     // Give attacker a Bomb card so validation passes
//    Card bombCard("Bomb");
//    attacker.getHand()->hand->push_back(bombCard);

//     // --- Create territories ---
//     Territory source("Base");
//     Territory target("EnemyCity");

//     // Assign ownership
//     source.setOwner(&attacker);
//     target.setOwner(&defender);

//     // Add adjacency (Bomb needs source and target adjacent)
//     source.addAdjacentTerritory(&target);
//     //target.addAdjacentTerritory(&source);

//     // Add to player lists
//     attacker.toDefend()->push_back(&source);
//     attacker.toAttack()->push_back(&target);

//     cout << "\nBefore Bomb:\n";
//     cout << "Target territory armies = " << target.getArmies() << endl;

//     // --- Case 1: Valid Bomb order ---
//     Bomb bombOrder(0, "Base", "EnemyCity");
//     bombOrder.execute(attacker);

//     cout << "\nAfter Bomb:\n";
//     cout << "Target territory armies = " << target.getArmies() << endl;
//     cout << "Expected: target armies halved\n";

//     // --- Case 2: Invalid (target owned by same player) ---
//     cout << "\n====== TESTING INVALID CASE (own territory) ======\n";
//     // After changing ownership
// target.setOwner(&attacker);
// // Remove from attack collection
// auto& attackList = *attacker.toAttack();
// auto it = find(attackList.begin(), attackList.end(), &target);
// if (it != attackList.end())
//     attackList.erase(it);
// // Add to defend collection
// attacker.toDefend()->push_back(&target);
//     bombOrder.execute(attacker);

//     // --- Case 3: Invalid (non-adjacent) ---
//     cout << "\n====== TESTING INVALID CASE (not adjacent) ======\n";
//     Territory farAway("DistantLand");
//     farAway.setOwner(&defender);
//     attacker.toAttack()->push_back(&farAway);
//     // not adding adjacency link intentionally
//     Bomb invalidBomb(0, "Base", "DistantLand");
//     invalidBomb.execute(attacker);

//     return 0;
// }



// int main() {
//     Player A("Umer");
//     Player B("Enemy");

//     Negotiate order(0, "", "", &B);
//     order.execute(A);

//     cout << "\nTrying to attack after negotiation...\n";
//     if (find(A.negotiatedWith.begin(), A.negotiatedWith.end(), &B) != A.negotiatedWith.end()) {
//         cout << "Attack blocked -- A and B are under truce.\n";
//     }
// }


// #include <iostream>
// #include "Orders.h"
// #include "Player.h"
// #include "Map.h"
// using namespace std;

// int main() {
//     cout << "===== BLOCKADE ORDER TEST =====" << endl;

//     // --- Setup Players ---
//     Player* player1 = new Player("Alice");
//     //Player* neutral = new Player("Neutral"); // optional if your system tracks neutral elsewhere

//     // --- Setup Territories ---
//     Territory* territoryA = new Territory("Montreal");
//     territoryA->setOwner(player1);
//     territoryA->setArmies(8);
//     player1->toDefend()->push_back(territoryA);

//     cout << "\nBefore Blockade:" << endl;
//     cout << "Territory: " << territoryA->getName()
//          << " | Owner: " << territoryA->getOwner()->getName()
//          << " | Armies: " << territoryA->getArmies() << endl;

//     // --- Add a dummy "Blockade" card so validation passes ---
//     Card blockadeCard("Blockade");
//     player1->getHand()->hand->push_back(blockadeCard);

//     // --- Create and execute Blockade order ---
//     Blockade blockadeOrder(0, "", territoryA->getName());
//     blockadeOrder.execute(*player1);

//     cout << "\nAfter Blockade Execution:" << endl;
//     cout << "Territory: " << territoryA->getName()
//          << " | Owner: " << territoryA->getOwner()->getName()
//          << " | Armies: " << territoryA->getArmies() << endl;

//     // --- Validation checks ---
//     if (territoryA->getArmies() == 16 && territoryA->getOwner()->getName() == "Neutral") {
//         cout << "\n Test Passed: Blockade doubled armies and transferred ownership.\n";
//     } else {
//         cout << "\n Test Failed: Unexpected state after blockade.\n";
//     }

//     // Cleanup
//     delete player1;
//     //delete neutral;
//     delete territoryA;

//     cout << "\n===== END OF TEST =====" << endl;
//     return 0;
// }

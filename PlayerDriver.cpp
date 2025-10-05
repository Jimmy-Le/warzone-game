#include "PlayerDriver.h"
#include "Orders.h"
#include <iostream>
#include <memory>
#include <string>

using namespace std;



Player player("Player 1");

void testPlayers(){
    cout << "========== Testing Players ==========" << endl;
    cout << player.getName() << " created"<< endl;
    playerMenu();
}

void playerMenu(){

    bool exit = false;
    cout << "Player Menu" << endl;
    while(!exit){
        // Display Menu
        cout << "1. Print Player" << endl;
        cout << "2. Test Attacking" << endl;
        cout << "3. Test Defending" << endl;
        cout << "4. Test Orders" << endl;
        cout << "5. Exit Player Menu\n" << endl;


        int choice;                                 // User's choice
        cin >> choice;

        switch(choice){
            case 1:                                                 // Print Player Information
                cout << "\n========== Printing Player Information ===========\n" << endl;
                cout << player << endl;
                break;
            case 2:                                                 // Test Attacking
                cout << "\n========== Testing Attacking ===========\n" << endl;
                cout << player.getName() << "'s Territories to Attack: " << endl;
                for (string& territory : *player.toAttack()) {
                    cout << territory << " " << endl;
                }
                break;
            case 3:                                                 // Test Defending
                cout << "\n========== Testing Defending ===========\n" << endl;
                cout << player.getName() << "'s Territories to Defend: " << endl;
                for (string& territory : *player.toDefend()) {
                    cout << territory << " " << endl;
                }
                break;
            case 4:                                                 // Test Orders
                cout << "\n========== Testing Orders ===========\n" << endl;
               player.issueOrder(3, "India", "China", "deploy");
                cout << player.getName() << "'s Order added " << endl;
                cout << "Print Player's Information to view all orders" << endl;
                break;
            case 5:                                                 // Exit Player Menu
                cout << "\n========== Exiting Player Menu ===========\n" << endl;
                exit = true;
                player.~Player();
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
        }
        cout << "\n===============================\n" << endl;
    }
}

#include "Player.h"



void testPlayers(){
    Player abc;
    abc.toAttack();
    abc.toDefend();
    abc.issueOrder();
    abc.issueOrder();
    abc.issueOrder();
    abc.printPlayer();
}

int main(){
    testPlayers();
}

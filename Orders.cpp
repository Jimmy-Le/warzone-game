//THINGS TO WORK ON
//BASED ON LECTURE I MIGHT HAVE TO WORK ON MY ASSIGNMENT OPERATOR ITS NOT CORRECT DEFINITELY 
//YES THAT IS ONE THING I NEED TO WORK ON 
//REMOVE() AND MOVE() FOR THE ORDERLIST
//VALIDATE() AND EXECUTE()
//use unique pointer indeed the shared pointer is an overkill and a bit irrelevant 
//i believe the main utility along side with memory management was the reference counter and being able to prevent
//double deletions and dangling pointers //
//but if we still relied on the default constructors and assignment operators a shallow copy (only pointers copied) is created
//which means if i add modify the state of one order then any order pointing the same values will also get modified
//which i don't want 
//so we use unique pointers + userdefined copy constructors +assingment operator for a secure and memory proof Order class 
//no user defined destructor needed the default ones with smart pointers efficient . Will be implicitly called at the end of the program 
//and another thing 
//when using shared pointers and want to make a deep copy we do the following --> 
//make_shared<int>(42) = shared_ptr<int>(new int(42)) returns poitner pointing to new heap object 


#include "Orders.h"




Orders::Orders(){
  this->numberOfArmyUnits = make_unique<int>(0);
  this->sourceTerritory = make_unique<string>("");
  this->targetTerritory = make_unique<string>("");
};

Orders::Orders(int numberOfArmyUnits , string sourceTerritory , string targetTerritory){
  (*this).numberOfArmyUnits = make_unique<int>(numberOfArmyUnits); //another way
  this->sourceTerritory = make_unique<string>(sourceTerritory);
  this->targetTerritory = make_unique<string>(targetTerritory);
};


Orders::Orders(const Orders& otherOrder){
  this->numberOfArmyUnits = make_unique<int>(*otherOrder.numberOfArmyUnits);
  //why do we use new  , so that each orders mebers have a separate location in the heap memory
  //as the memebers are pointers we do not want multiple pointers pointing to the same location in memory
  //that would be a shallow copy and could cause problems suppose we deleted on pointer the other would become a dangling pointer

  this->sourceTerritory = make_unique<string>(*otherOrder.sourceTerritory);
  this->targetTerritory = make_unique<string>(*otherOrder.targetTerritory);

};

Orders& Orders::operator=(const Orders& otherOrder){
  if(this != &otherOrder){
    *numberOfArmyUnits =  *otherOrder.numberOfArmyUnits;
    *sourceTerritory = *otherOrder.sourceTerritory;
    *targetTerritory = *otherOrder.targetTerritory;
  }
  return *this;


};

int Orders::getNumberOfArmyUnits() const{ //const method makes sure to not modify the object , const objects can only use cconst methods like using setter on const obj is not allowed
  return *numberOfArmyUnits;
};
string Orders::getSourceTerritory() const{
  return *sourceTerritory;
};
string Orders::getTargetTerritory() const{
  return *targetTerritory;
};
void Orders::setNumberOfArmyUnits(int numberOfArmyUnits) {
  *this->numberOfArmyUnits = numberOfArmyUnits;
};

void Orders::setSourceTerritory(string sourceTerritory) {
  *this->sourceTerritory = sourceTerritory;
};
void Orders::setTargetTerritory(string targetTerritory) {
  *this->targetTerritory = targetTerritory;
};


void Orders::execute(Player& player){
  cout<<"Orders is getting executed";
};

bool Orders::validate(Player& player){
  cout<<"Order is validated";
  return true;
};


  void Orders::print(ostream& os) const{
    os<< "Number of Army Units:" << this->getNumberOfArmyUnits() <<endl ; 
    os << " Source Territory:" <<this->getSourceTerritory() <<endl;
    os << " Target Territory:" << this->getTargetTerritory() <<endl;
      }
 ostream& operator<<(ostream& os , const Orders& otherOrder){
        otherOrder.print(os);  // Polymorphic call
        return os;
};


//----------------------------------------------------------------------------
//DeployOrder Class Method Implementations

//to select which base constructor runs in the initializer list is decided rightafter the : 
DeployOrder::DeployOrder( int numberOfArmyUnits , string sourceTerritory  , string targetTerritory)
    : Orders(numberOfArmyUnits , sourceTerritory , targetTerritory) {};

DeployOrder::DeployOrder() : Orders(){};

DeployOrder::DeployOrder(const DeployOrder& deploy) : Orders::Orders(static_cast<const Orders&>(deploy)) {};

DeployOrder& DeployOrder::operator=(const DeployOrder& otherDeployOrder){
  Orders::operator=(static_cast<const Orders&>(otherDeployOrder));
  return *this;
};


 void DeployOrder::print(ostream& os) const{
        os << "DEPLOY ORDER INFORMATION" << endl;
        os << "-----------------------------------------------" << endl;
        Orders::print(os);   // base info
    }

  ostream& operator<<(ostream& os, const DeployOrder& deploy) {
        deploy.print(os);      // reuse same print()
        return os;
    }

void DeployOrder::execute(Player& player){
  if (!validate(player)) {
        cout << "Invalid Deploy order.\n";
        return;
    }

    // find target again to apply the effect
    for (auto* terr : *player.toDefend()) {
        if (terr->getName() == this->getTargetTerritory()) {
            int currentArmies = terr->getArmies();
            terr->setArmies(currentArmies + this->getNumberOfArmyUnits());

            player.setReinforcementPool(
                player.getReinforcementPool() - this->getNumberOfArmyUnits()
            );

            cout << "Deployed " << this->getNumberOfArmyUnits()
                 << " armies to " << terr->getName() << ".\n";
            cout << "Remaining reinforcement pool: "
                 << player.getReinforcementPool() << endl;
            break;
        }
    }
}

bool DeployOrder::validate(Player& player){
      // check if target territory belongs to this player
    for (auto* terr : *player.toDefend()) {
        if (terr->getName() == this->getTargetTerritory()) {
            // check reinforcement availability
            if (this->getNumberOfArmyUnits() <= player.getReinforcementPool())
                return true;
            else {
                cout << "Not enough armies in reinforcement pool.\n";
                return false;
            }
        }
    }
    cout << "Target territory not owned by player.\n";
    return false;
}




//-----------------------------------------------------------------------------
//NEGOTIATE SUBCLASS METHOD IMPLEMENTATIONS
//TODO: i made change to the constructor of the Negotiate order as we need a Target player with home the issuing player sets a pact
Negotiate::Negotiate(int numberOfArmyUnits, string sourceTerritory, string targetTerritory , Player* target) 
    : Orders(numberOfArmyUnits, sourceTerritory, targetTerritory)  , targetPlayer(target) {};

Negotiate::Negotiate() : Orders(){};

Negotiate::Negotiate(const Negotiate& otherNegotiate)
    : Orders(static_cast<const Orders&>(otherNegotiate)) {
    this->targetPlayer = otherNegotiate.targetPlayer;  // shallow copy of pointer, not ownership
}


Negotiate& Negotiate::operator=(const Negotiate& otherNegotiate) {
    if (this != &otherNegotiate) {
        Orders::operator=(static_cast<const Orders&>(otherNegotiate));
        this->targetPlayer = otherNegotiate.targetPlayer; // why would i need a deep copy if something happens to the player i would like it to be reflected in the player rather than a copy of the payer 
    }
    return *this;
}



 void Negotiate::print(ostream& os) const{
        os << "NEGOTIATE ORDER INFORMATION" << endl;
        os << "-----------------------------------------------" << endl;
        Orders::print(os);   // base info
        os << *this->getTargetPlayer();
    }

  ostream& operator<<(ostream& os, const Negotiate& negotiate) {
        negotiate.print(os);      // reuse same print()
        return os;
    }

  void Negotiate::execute(Player& player){
    if (!validate(player)) {
            cout << "Negotiate order execution aborted.\n";
            return;
        }

        // Mutual diplomacy setup
        player.negotiatedWith.push_back(targetPlayer);
        //FIXME: okay pkayer is a raw pointer , negotiateWith is a vector of unique pointers to players , my target player also unique but issuing player raw , that is what forms incocnsistencies 
        //keep the negotiatedWith vector of raw pointers ,and make target also raw but delete it / memeory management 
        
        this->getTargetPlayer()->negotiatedWith.push_back(&player);

        cout << "Diplomacy established between " << player.getName()
            << " and " << targetPlayer->getName()
            << ". They cannot attack each other this turn.\n";
}

  bool Negotiate::validate(Player& player){
    if (this->getTargetPlayer() == nullptr) {
            cout << "INVALID NEGOTIATE ORDER: Target player not specified.\n";
            return false;
        }
        if (this->getTargetPlayer() == &player) {
            cout << "INVALID NEGOTIATE ORDER: Cannot negotiate with yourself.\n";
            return false;
        }
        cout << "Negotiate order validated between " << player.getName()
            << " and " << this->getTargetPlayer()->getName() << ".\n";
        return true;
}


//-------------------------------------------------------------------------------
//BOMB SUBCLASS METHOD IMPLEMENTATION
Bomb::Bomb(int numberOfArmyUnits, string sourceTerritory, string targetTerritory)
    : Orders(numberOfArmyUnits, sourceTerritory, targetTerritory) {};

Bomb::Bomb() : Orders(){};
    
Bomb::Bomb(const Bomb& otherBomb) : Orders(static_cast<const Orders&>(otherBomb)){};

Bomb& Bomb::operator=(const Bomb& otherBomb){
    Orders::operator=(static_cast<const Orders&>(otherBomb));
    return *this;
};


ostream& operator<<(ostream& os, const Bomb& bomb) {
        bomb.print(os);      // reuse same print()
        return os;
    }

 void Bomb::print(ostream& os) const{
        os << "BOMB ORDER INFORMATION" << endl;
        os << "-----------------------------------------------" << endl;
        Orders::print(os);   // base info
    }

    void Bomb::execute(Player& player){
      // Validate before execution
      if (!validate(player)) {
          cout << "Bomb order aborted due to failed validation.\n";
          return;
      }

      // Step 1: Find target territory again (for applying effect)
      Territory* targetTerr = nullptr;
      for (auto* terr : *player.toAttack()) {
          if (terr->getName() == this->getTargetTerritory()) {
              targetTerr = terr;
              break;
          }
      }

      if (!targetTerr) {
          cout << "Target territory not found during execution.\n";
          return;
      }

      // Step 2: Apply the bomb effect — halve target armies
      int currentArmies = targetTerr->getArmies();
      targetTerr->setArmies(currentArmies / 2);

      cout << "Bomb order successfully executed! "
          << targetTerr->getName() << " armies halved from "
          << currentArmies << " -> " << targetTerr->getArmies() << ".\n";

      // Step 3:Remove Bomb card after use
      // for (auto it = player.getHand()->hand->begin(); it != player.getHand()->hand->end(); ++it) {
      //     if (*(it->cardType) == "Bomb") {
      //         player.getHand()->hand->erase(it);
      //         cout << "Bomb card removed from hand after execution.\n";
      //         break;
      //     }
      // }  I DO NOT KNOW IF THIS SOMETHING THE BOMB ORDER EXECUTE HAS TO HANDLE MAYBE GAME ENGINE TAKE CARES OF THIS 
}

  bool Bomb::validate(Player& player){
    // Step 1: Check if player owns a Bomb card
      bool hasBombCard = false;
      for (auto card : *player.getHand()->hand) {
          if (*(card.cardType) == "Bomb") { // your current check
              hasBombCard = true;
              break;
          }
      }

      if (!hasBombCard) {
          cout << "BOMB ORDER INVALID: Player does not have a Bomb card in hand.\n";
          return false;
      }

      // Step 2: Ensure target territory is NOT owned by the issuing player
      for (auto* terr : *player.toDefend()) {
          if (terr->getName() == this->getTargetTerritory()) {
              cout << "BOMB ORDER INVALID: Target territory is owned by the player.\n";
              return false;
          }
      }

      // Step 3: Find source and target territories
      Territory* sourceTerr = nullptr;
      Territory* targetTerr = nullptr;

      for (auto* terr : *player.toDefend()) {
          if (terr->getName() == this->getSourceTerritory())
              sourceTerr = terr;
      }
      for (auto* terr : *player.toAttack()) {
          if (terr->getName() == this->getTargetTerritory())
              targetTerr = terr;
      }

      if (!sourceTerr || !targetTerr) { //also test sourceTerr == nullptr;
          cout << "BOMB ORDER INVALID: Source or target territory not found.\n";
          return false;
      }

      // Step 4: Check adjacency
      if (sourceTerr->isAdjacent(targetTerr) == false) {
          cout << "BOMB ORDER INVALID: Source and target are not adjacent.\n";
          return false;
      }

      // All validations passed
      return true;
  }


//--------------------------------------------------------------------------------
//ADVANCE SUBCLASS METHOD IMPLEMENTATION

Advance::Advance(int numberOfArmyUnits , string sourceTerritory , string targetTerritory) : Orders(numberOfArmyUnits , sourceTerritory , targetTerritory) {};

Advance::Advance() : Orders(){};

Advance::Advance(const Advance& otherAdvance) : Orders(static_cast<const Orders&>(otherAdvance)){
 
};

ostream& operator<<(ostream& os, const Advance& advance) {
        advance.print(os);      // reuse same print()
        return os;
    }

 void Advance::print(ostream& os) const{
        os << "ADVANCE ORDER INFORMATION" << endl;
        os << "-----------------------------------------------" << endl;
        Orders::print(os);   // base info
    }

Advance& Advance::operator=(const Advance& advance){
  Orders::operator=(static_cast<const Orders&>(advance));
  return *this;
};
 
// ...existing code...
void Advance::execute(Player& player) {
    if (!validate(player)) {
        cout << "Advance order execution aborted.\n";
        return;
    }

    // Locate territories again for the effect (do NOT allocate new Territory objects)
    Territory* sourceTerr = nullptr;
    Territory* targetTerr = nullptr;
    Territory* sameTerr   = nullptr;

    for (auto* terr : *player.toDefend()) {
        if (terr->getName() == this->getSourceTerritory()) {
            sourceTerr = terr;
            break;
        }
    }
    for (auto* terr : *player.toAttack()) {
        if (terr->getName() == this->getTargetTerritory()) {
            targetTerr = terr;
            break;
        }
    }
    for (auto* terr : *player.toDefend()) {
        if (terr->getName() == this->getTargetTerritory()) {
            sameTerr = terr;
            break;
        }
    }

    // // Defensive checks
    // if (!sourceTerr) {
    //     cout << "Advance error: source territory not found at execution time.\n";
    //     return;
    // }

    // MOVE: target is also owned by player
    if (sameTerr != nullptr) {
        cout << "Moving armies from " << sourceTerr->getName()
             << " -> " << sameTerr->getName() << endl;

        if (this->getNumberOfArmyUnits() > sourceTerr->getArmies()) {
            cout << "Not enough armies in source territory for move.\n";
            return;
        }

        sourceTerr->setArmies(sourceTerr->getArmies() - this->getNumberOfArmyUnits());
        sameTerr->setArmies(sameTerr->getArmies() + this->getNumberOfArmyUnits());
        return;
    }

    // // ATTACK: target belongs to another player
    // if (!targetTerr) {
    //     cout << "Advance error: attack target not found at execution time.\n";
    //     return;
    // }

    cout << "ATTACK from " << sourceTerr->getName()
         << " -> " << targetTerr->getName() << endl;

    int attackingUnits = this->getNumberOfArmyUnits();
    int defendingUnits = targetTerr->getArmies();

    if (attackingUnits > sourceTerr->getArmies()) {
        cout << "Invalid: trying to send more armies than available.\n";
        return;
    }

    int attackerKills = round(0.6 * attackingUnits);
    int defenderKills = round(0.7 * defendingUnits);
    cout<<attackerKills <<endl;
    cout<<defenderKills <<endl;
    cout<<(attackerKills >= defenderKills);
    if (attackerKills >= defenderKills) {
        cout << "ATTACKER WINS THE BATTLE!\n";

        int survivingAttackers = attackingUnits - defenderKills;
        sourceTerr->setArmies(sourceTerr->getArmies() - attackingUnits);
        targetTerr->setArmies(max(0, survivingAttackers));
        targetTerr->setOwner(&player);

        // Move conquered territory to player's defend list (push existing pointer)
        player.toDefend()->push_back(targetTerr);

        // Remove from attack list (erase by pointer)
        auto& attackList = *player.toAttack();
        auto it = find(attackList.begin(), attackList.end(), targetTerr);
        if (it != attackList.end())
            attackList.erase(it);

        // Reward player with one random card
        static Deck sharedDeck;
        sharedDeck.draw(player.getHand());
        cout << "Player rewarded with a card for conquering a territory.\n";
    } else {
        cout << "DEFENDER WINS THE BATTLE.\n";
        int remainingDefenders = defendingUnits - attackerKills;
        targetTerr->setArmies(remainingDefenders);
        sourceTerr->setArmies(sourceTerr->getArmies() - attackingUnits);
    }
}




  bool Advance::validate(Player& player){
      Territory* sourceTerr = nullptr;
      Territory* targetTerr = nullptr;
      Territory* sameTerr = nullptr;

      // Find source and target territories
      for (auto* terr : *player.toDefend()) {
          if (terr->getName() == this->getSourceTerritory())
              sourceTerr = terr;
      }
      for (auto* terr : *player.toAttack()) {
          if (terr->getName() == this->getTargetTerritory())
              targetTerr = terr;
      }
       for (auto* terr : *player.toDefend()) {
          if (terr->getName() == this->getTargetTerritory())
              sameTerr = terr;
      }

      // Check existence
      if(sourceTerr == nullptr){
        cout<<"INVALID ADVANCE ORDER: Source territory does not belong to the issuing player.\n";
        return false ;
      }
      if ((!targetTerr) && (!sameTerr) ) {
          cout << "INVALID ADVANCE ORDER: Source or Target not found.\n";
          return false;
      }

      // Check ownership of source
      if (sourceTerr->getOwner() != &player) {
          cout << "INVALID ADVANCE ORDER: Source territory not owned by player.\n";
          return false;
      }

      // Check adjacency
      //NOTE: had a problem here but i guess now all the edge cases are checked for (in case its a move i need to check for adjacency as well )
      if(sameTerr != nullptr){
        if (!sourceTerr->isAdjacent(sameTerr)) {
            cout << "INVALID ADVANCE ORDER: Territories are not adjacent.\n";
            return false;
        }
    }

    if(targetTerr != nullptr){
        if (!sourceTerr->isAdjacent(targetTerr)) {
            cout << "INVALID ADVANCE ORDER: Territories are not adjacent.\n";
            return false;
        }
    }

      // Check sufficient armies
      if (this->getNumberOfArmyUnits() > sourceTerr->getArmies()) {
          cout << "INVALID ADVANCE ORDER: Not enough armies in source territory.\n";
          return false;
      }

      return true;
  };


//--------------------------------------------------------------------------------
//AIRLIFT SUBCLASS METHOD IMPLEMENTATION
Airlift::Airlift(int numberOfArmyUnits, string sourceTerritory, string targetTerritory)
    : Orders(numberOfArmyUnits, sourceTerritory, targetTerritory) {};

Airlift::Airlift() : Orders(){};    

Airlift::Airlift(const Airlift& otherAirlift) : Orders(static_cast<const Orders&>(otherAirlift)){

};

Airlift& Airlift::operator=(const Airlift& otherAirlift){
   Orders::operator=(static_cast<const Orders&>(otherAirlift));
    return *this;
};

ostream& operator<<(ostream& os, const Airlift& airlift) {
        airlift.print(os);      // reuse same print()
        return os;
    }

 void Airlift::print(ostream& os) const{
        os << "AIRLIFT ORDER INFORMATION" << endl;
        os << "-----------------------------------------------" << endl;
        Orders::print(os);   // base info
    }

  
  void Airlift::execute(Player& player){
      if (!validate(player)) {
          cout << "Airlift order execution aborted.\n";
          return;
      }

      // Step 1: Find territories again (for actual move)
      Territory* sourceTerr = nullptr;
      Territory* targetTerr = nullptr;

      for (auto* terr : *player.toDefend()) {
          if (terr->getName() == this->getSourceTerritory())
              sourceTerr = terr;
      }

      for (auto* terr : *player.toDefend()) {
          if (terr->getName() == this->getTargetTerritory())
              targetTerr = terr;
      }

      // Step 2: Perform the Airlift
      cout << "Airlifting " << this->getNumberOfArmyUnits()
          << " armies from " << sourceTerr->getName()
          << " -> " << targetTerr->getName() << endl;

      sourceTerr->setArmies(sourceTerr->getArmies() - this->getNumberOfArmyUnits());
      targetTerr->setArmies(targetTerr->getArmies() + this->getNumberOfArmyUnits());

      cout << "Airlift complete.\n"
          << "Source now has " << sourceTerr->getArmies()
          << ", Target now has " << targetTerr->getArmies() << " armies.\n";

      // 3️⃣ Optional: Remove Airlift card from hand
      // for (auto it = player.getHand()->hand->begin(); it != player.getHand()->hand->end(); ++it) {
      //     if (*(it->cardType) == "Airlift") {
      //         player.getHand()->hand->erase(it);
      //         cout << "Airlift card removed from player's hand after use.\n";
      //         break;
      //     }
      // }  //yet to decide if this is something the execute() needs to do 
}

  bool Airlift::validate(Player& player){
    // Step 1 :Check if player has an Airlift card
    bool hasAirliftCard = false;
    for (auto card : *player.getHand()->hand) {
        if (*(card.cardType) == "Airlift") {
            hasAirliftCard = true;
            break;
        }
    }
    if (!hasAirliftCard) {
        cout << "AIRLIFT ORDER INVALID: Player does not have an Airlift card.\n";
        return false;
    }

    // Step 2:  Find source and target territories
    Territory* sourceTerr = nullptr;
    Territory* targetTerr = nullptr;

    for (auto* terr : *player.toDefend()) {
        if (terr->getName() == this->getSourceTerritory())
            sourceTerr = terr;
    }

    for (auto* terr : *player.toDefend()) {
        if (terr->getName() == this->getTargetTerritory())
            targetTerr = terr;
    }

    if (!sourceTerr || !targetTerr) {
        cout << "AIRLIFT ORDER INVALID: Source or Target not found.\n";
        return false;
    }

    // Step 3: Both territories must belong to the same player
    if (sourceTerr->getOwner() != &player || targetTerr->getOwner() != &player) {
        cout << "AIRLIFT ORDER INVALID: Both territories must be owned by the player.\n";
        return false;
    }

    // Step 4:  Check if enough armies available
    if (this->getNumberOfArmyUnits() > sourceTerr->getArmies()) {
        cout << "AIRLIFT ORDER INVALID: Not enough armies in source territory.\n";
        return false;
    }

    // Passed all checks
    return true;
    
  };

//--------------------------------------------------------------------------------
// BLOCKADE SUBCLASS METHODS IMPLEMENTATION

Blockade::Blockade(int numberOfArmyUnits, string sourceTerritory, string targetTerritory)
    : Orders(numberOfArmyUnits, sourceTerritory, targetTerritory) {};

Blockade::Blockade() : Orders(){};

Blockade::Blockade(const Blockade& otherBlockade) : Orders(static_cast<const Orders&>(otherBlockade)){};

Blockade& Blockade::operator=(const Blockade& otherBlockade){
    Orders::operator=(static_cast<const Orders&>(otherBlockade));
    return *this;
};

ostream& operator<<(ostream& os, const Blockade& blockade) {
        blockade.print(os);      // reuse same print()
        return os;
    }

 void Blockade::print(ostream& os) const{
        os << "BLOCKADE ORDER INFORMATION" << endl;
        os << "-----------------------------------------------" << endl;
        Orders::print(os);   // base info
    }

  
  void Blockade::execute(Player& player){
    if (!validate(player)) {
        cout << "Blockade order execution aborted.\n";
        return;
    }

    // Step 1: Find the target territory
    Territory* target = nullptr;
    for (auto* terr : *player.toDefend()) {
        if (terr->getName() == this->getTargetTerritory()) {
            target = terr;
            break;
        }
    }

    if (!target) {
        cout << "Target territory not found, cannot execute Blockade order.\n";
        return;
    }

    // Step 2: Apply the blockade effect
    target->setArmies(target->getArmies() * 2);
    cout << "Blockade executed: " << target->getName()
         << " armies doubled to " << target->getArmies() << ".\n";

    // Step 3: Transfer ownership to Neutral
    static Player neutralPlayer("Neutral"); // persists across calls
    target->setOwner(&neutralPlayer);

    // Step 4: Remove from player’s defend list
    auto& defendList = *player.toDefend();
    auto it = find(defendList.begin(), defendList.end(), target);
    if (it != defendList.end())
        defendList.erase(it);

    cout << "Territory ownership transferred to Neutral player.\n";
    //TODO: might implement this in card section do not forget
    // Step 5: Remove Blockade card from player's hand 
    // for (auto it = player.getHand()->hand->begin(); it != player.getHand()->hand->end(); ++it) {
    //     if (*(it->cardType) == "Blockade") {
    //         player.getHand()->hand->erase(it);
    //         cout << "Blockade card removed from player's hand after use.\n";
    //         break;
    //     }
    // }

}

  bool Blockade::validate(Player& player)
  {
   // Step 1: Check if player has a Blockade card
    bool hasBlockadeCard = false;
    for (auto card : *player.getHand()->hand) {
        if (*(card.cardType) == "Blockade") {
            hasBlockadeCard = true;
            break;
        }
    }

    if (!hasBlockadeCard) {
        cout << "BLOCKADE ORDER INVALID: Player does not have a Blockade card in hand.\n";
        return false;
    }

    // Step 2: Check if target territory belongs to player
    bool ownsTarget = false;
    for (auto* terr : *player.toDefend()) {
        if (terr->getName() == this->getTargetTerritory()) {
            ownsTarget = true;
            break;
        }
    }

    if (!ownsTarget) {
        cout << "BLOCKADE ORDER INVALID: Target territory not owned by player.\n";
        return false;
    }

    // Passed all validation checks
    cout << "Blockade order validated successfully.\n";
    return true;
  }

  

//-------------------------------------------------------------------------
//ORDERLIST 

int found = 0;

void Orderlist::remove(Orders& order){
    bool flag = false;
    

    for(int i =0 ; i< this->orderList.size() ; i++){ //this->orderlist represents the vector which is simply an object holding pointers to orders
        if(typeid(*this->orderList[i]).name()  == (typeid(order)).name()){
            //check for the equality of the rest of paramters
           if((*this->orderList[i]).getNumberOfArmyUnits() == order.getNumberOfArmyUnits() &&
            (*this->orderList[i]).getSourceTerritory() == order.getSourceTerritory() &&
            (*this->orderList[i]).getTargetTerritory() == order.getTargetTerritory()){
            
            found = i;
            flag= true;
            break;
           }
        }
    }
    if(flag == false){
        cout<<"NO SUCH ELEMENT BELONGS IN THE LIST ";
    }
    else{
        this->orderList.erase(this->orderList.begin() + found);
    }


};

//for moving the orders in the orderlist i need to use the insert function of the vector class 
//but i will have to check how it readjusts the indcies 
//my idea is that reuse the remove method to first remove the order -didnt work 
//but we will have to store it in a variable 
//then move the order  would mean insert it a specific location by providing an index

void Orderlist::move(Orders& order , int index){
    int from;
  for(int i =0 ; i< this->orderList.size() ; i++){ //this->orderlist represents the vector which is simply an object holding pointers to orders
        // cout<<"=================================================" <<endl;
        //     cout<<typeid(*this->orderList[i]).name() <<endl; // i believe the problem is the both are essentially Orders so it deletes the first element , even if we asked for bomb
        //     //what can solve this problem have an id with BOmb that generates unique id for each order ;
        //     cout<<typeid(order).name() <<endl;
        //     cout<<"=================================================" <<endl <<"\n";
        if(typeid(*this->orderList[i]).name()  == (typeid(order)).name()){
            //check for the equality of the rest of parameters
           if((*this->orderList[i]).getNumberOfArmyUnits() == order.getNumberOfArmyUnits() &&
            (*this->orderList[i]).getSourceTerritory() == order.getSourceTerritory() &&
            (*this->orderList[i]).getTargetTerritory() == order.getTargetTerritory()){
            
            from = i;
            break;
           }
        }
    }
 auto saved = std::move(this->orderList[from]);//unique pointers ownership can only be transferred , here ownership of the Order pointers transferred to saved temporarily 
this->orderList.erase(this->orderList.begin() + from);

this->orderList.insert(
    this->orderList.begin() + index,
    std::move(saved)//
);

 
}





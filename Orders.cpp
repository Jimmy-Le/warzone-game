//THINGS TO WORK ON
//BASED ON LECTURE I MIGHT HAVE TO WORK ON MY ASSIGNMENT OPERATOR ITS NOT CORRECT DEFINITELY 
//YES THAT IS ONE THING I NEED TO WORK ON 
//REMOVE() AND MOVE() FOR THE ORDERLIST
//VALIDATE() AND EXECUTE()
//use unique pointer indeed the shared pointer is an overkill and a bit irrelevant 
//i believe the main utility along side with memory management was the reference counter and being able to prevent
//double deletions and dangling pointers //
//but if we still relied on the default constructors and assignment operators a shallow copy (only pointers copied) is created
//which means if i idd modify the state of one order then any order pointing the same values will also get modified
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


//using initializer list
// Orders::Orders()
//     : numberOfArmyUnits(std::make_shared<int>(0)),
//       sourceTerritory(std::make_shared<string>()),
//       targetTerritory(std::make_shared<string>()) {} 
//THIS IS THE SAME AS THE ABOVE BUT WE USE THE CONCEPT OF INITIALIZER LIST
//NOW IT MAKES MORE SENSE WHY CALL THE BASE CLASS INSTRUCTOR IN THE INITIALIZER LIST
//XD --> much more simpler no syntax jargon



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


void Orders::execute(){
  cout<<"Orders is getting executed";
};

void Orders::validate(){
  cout<<"Order is validated";
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

void DeployOrder::execute(){
  cout<<"Deploy order is getting executed";
};

void DeployOrder::validate(){
  cout<<"Deploy order is validated";
};



//-----------------------------------------------------------------------------
//NEGOTIATE SUBCLASS METHOD IMPLEMENTATIONS
Negotiate::Negotiate(int numberOfArmyUnits, string sourceTerritory, string targetTerritory)
    : Orders(numberOfArmyUnits, sourceTerritory, targetTerritory) {};

Negotiate::Negotiate() : Orders(){};

Negotiate::Negotiate(const Negotiate& otherNegotiate): Orders(static_cast<const Orders&>(otherNegotiate))
  {};

Negotiate& Negotiate::operator=(const Negotiate& otherNegotiate){
    // if (this != &otherNegotiate) {
    //     this->numberOfArmyUnits = make_unique<int>(*otherNegotiate.numberOfArmyUnits);
    //     this->sourceTerritory = make_unique<string>(*otherNegotiate.sourceTerritory);
    //     this->targetTerritory = make_unique<string>(*otherNegotiate.targetTerritory);
    // }
    Orders::operator=(static_cast<const Orders&>(otherNegotiate));
    return *this;
};


 void Negotiate::print(ostream& os) const{
        os << "NEGOTIATE ORDER INFORMATION" << endl;
        os << "-----------------------------------------------" << endl;
        Orders::print(os);   // base info
    }

  ostream& operator<<(ostream& os, const Negotiate& negotiate) {
        negotiate.print(os);      // reuse same print()
        return os;
    }

  void Negotiate::execute(){
  cout<<"Negotiate order is getting executed";
  };

  void Negotiate::validate(){
  cout<<"Negotiate order is validated";
  };


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

    void Bomb::execute(){
  cout<<"Bomb order is getting executed";
  };

  void Bomb::validate(){
  cout<<"Bomb order is validated";
  };


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

  void Advance::execute(){
  cout<<"Advance order is getting executed";
  };

  void Advance::validate(){
  cout<<"Advance order is validated";
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

  
  void Airlift::execute(){
  cout<<"Airlift order is getting executed";
  };

  void Airlift::validate(){
  cout<<"Airlift order is validated";
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

  
  void Blockade::execute(){
  cout<<"Blockade order is getting executed";
  };

  void Blockade::validate(){
  cout<<"Blockade order is validated";
  };

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
//my idea is that reuse the remove method to first remove the order 
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
            //check for the equality of the rest of paramters
           if((*this->orderList[i]).getNumberOfArmyUnits() == order.getNumberOfArmyUnits() &&
            (*this->orderList[i]).getSourceTerritory() == order.getSourceTerritory() &&
            (*this->orderList[i]).getTargetTerritory() == order.getTargetTerritory()){
            
            from = i;
            break;
           }
        }
    }
 auto saved = std::move(this->orderList[from]);
this->orderList.erase(this->orderList.begin() + from);

this->orderList.insert(
    this->orderList.begin() + index,
    std::move(saved)
);

 
}





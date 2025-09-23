#include <iostream>
#include "orders.h"
using namespace std;

Orders::Orders(int numberOfArmyUnits , string sourceTerritory , string targetTerritory){
  (*this).numberOfArmyUnits = make_shared<int>(numberOfArmyUnits); //another way
  this->sourceTerritory = make_shared<string>(sourceTerritory);
  this->targetTerritory = make_shared<string>(targetTerritory);
}



Orders::Orders(const Orders& otherOrder){
  numberOfArmyUnits = make_shared<int>(*otherOrder.numberOfArmyUnits);
  //why do we use new  , so that each orders mebers have a separate location in the memory
  //as the memebers are pointers we do not want multiple pointers pointing to the same location in memory
  //that would be a shallow copy and could cause problems suppose we deleted on pointer the other would become a dangling pointer

  sourceTerritory = make_shared<string>(*otherOrder.sourceTerritory);
  targetTerritory = make_shared<string>(*otherOrder.targetTerritory);

}

Orders& Orders::operator=(const Orders& otherOrder){
  if(this != &otherOrder){
    // delete numberOfArmyUnits;
    // delete sourceTerritory;
    // delete targetTerritory;

    numberOfArmyUnits =  make_shared<int>(*otherOrder.numberOfArmyUnits);
    sourceTerritory =  make_shared<string>(*otherOrder.sourceTerritory);
    targetTerritory = make_shared<string>(*otherOrder.targetTerritory);
  }
  return *this;


}

int Orders::getNumberOfArmyUnits(){
  return *numberOfArmyUnits;
}
string Orders::getSourceTerritory() {
  return *sourceTerritory;
}
string Orders::getTargetTerritory() {
  return *targetTerritory;
}
void Orders::setNumberOfArmyUnits(int numberOfArmyUnits) {
  *this->numberOfArmyUnits = numberOfArmyUnits;
}

void Orders::setSourceTerritory(string sourceTerritory) {
  *this->sourceTerritory = sourceTerritory;
}
void Orders::setTargetTerritory(string targetTerritory) {
  *this->targetTerritory = targetTerritory;
}

// Orders::~Orders(
//     delete numberOfArmyUnits;
//     delete sourceTerritory;
//     delete targetTerritory;
// }


ostream& operator<<(ostream& os , const Orders& otherOrder){
  os << "Number of Army Units:" <<*otherOrder.numberOfArmyUnits <<endl ; 
  os << " Source Territory:" << *otherOrder.sourceTerritory <<endl;
  os << " Target Territory:" << *otherOrder.targetTerritory <<endl;
  return os;
};



int main(){
  Orders order1 = Orders(10 , "A" , "B");
  Orders order2 = order1; //copy constructor

  order1.setNumberOfArmyUnits(20);
  cout << order1 << endl;
  cout << order2 << endl; //should still be 10 if deep copy worked
  return 0;

}




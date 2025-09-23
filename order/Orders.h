#ifndef ORDERS_H
#define ORDERS_H
#include <memory>
#include <string>
using namespace std;


//now we will decalre the class orders 
class Orders{
  protected:
    shared_ptr<int> numberOfArmyUnits;
    shared_ptr<string> sourceTerritory;
    shared_ptr<string> targetTerritory;
    //player* targetPlayer; //Once Jimmy done with the player class

    public:
      Orders(int numberOfArmyUnits , string sourceTerritory , string targetTerritory);
      Orders(const Orders& otherOrder);
      Orders& operator=(const Orders& otherOrder);
      friend ostream& operator<<(ostream& os , const Orders& otherOrder);
      int getNumberOfArmyUnits();
      string getSourceTerritory();
      string getTargetTerritory();
      void setNumberOfArmyUnits(int numberOfArmyUnits);
      void setSourceTerritory(string sourceTerritory);
      void setTargetTerritory(string targetTerritory);
      void validate( ); 


     





  
};

#endif







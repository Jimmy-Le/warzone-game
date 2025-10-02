#ifndef ORDERS_H
#define ORDERS_H
#include  <typeinfo>
#include <memory>
#include <string>
#include <iostream>
#include <vector>
using namespace std;


//now we will decalre the class orders 
class Orders{
  protected:
    unique_ptr<int> numberOfArmyUnits;
    unique_ptr<string> sourceTerritory;
    unique_ptr<string> targetTerritory;
    //player* targetPlayer; //Once Jimmy done with the player class

    public:
      Orders();
      Orders(int numberOfArmyUnits , string sourceTerritory , string targetTerritory);
      Orders(const Orders& otherOrder);
      Orders& operator=(const Orders& otherOrder);
      int getNumberOfArmyUnits() const;
      string getSourceTerritory() const;
      string getTargetTerritory() const;
      void setNumberOfArmyUnits(int numberOfArmyUnits);
      void setSourceTerritory(string sourceTerritory);
      void setTargetTerritory(string targetTerritory);
      void validate( ); 
      virtual ~Orders()  = default; //virtual destructor/

      friend ostream& operator<<(ostream& os , const Orders& otherOrder);


  
};

class DeployOrder : public Orders{
    public:
      DeployOrder(int numberOfArmyUnits , string sourceTerritory , string targetTerritory) ;

      friend ostream& operator<<(ostream& os , const DeployOrder& deploy);
   
 };



class Negotiate : public Orders{
  Negotiate(int numberOfArmyUnits , string sourceTerritory , string targetTerritory);
  Negotiate(const Negotiate& otherNegotiate);
  Negotiate& operator=(const Negotiate& otherNegotiate);

  friend ostream& operator<<(ostream& os , const Negotiate& negotiate);
};


class Bomb : public Orders{
  public:
  Bomb(int numberOfArmyUnits, string sourceTerritory, string targetTerritory);
  Bomb(const Bomb& otherBomb);
  Bomb& operator=(const Bomb& otherBomb);

  friend ostream& operator<<(ostream& os , const Bomb& bomb);
};


class Airlift : public Orders{
  public:
  Airlift(int numberOfArmyUnits , string sourceTerritory , string targetTerritory);
  Airlift(const Airlift& otherAirlift);
  Airlift& operator=(const Airlift& otherAirlift );

  friend ostream& operator<<(ostream& os , const Airlift& airlift);
};


class Advance : public Orders{
  public:
    Advance(int numberOfArmyUnits, string sourceTerritory, string targetTerritory);
    Advance(const Advance& otherAdvance);
    Advance& operator=(const Advance& otherAdvance);

    friend ostream& operator<<(ostream& os , const Advance& advance);
};

class Orderlist {
public:
    Orderlist() = default;
    std::vector<std::unique_ptr<Orders>> orderList;//the data member of orderlist 
    void remove(Orders& order);
    void move(Orders& order , int index);
};



#endif






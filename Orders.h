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
      virtual void validate( ); //only in case we have base pointer ti an object of child class 
      virtual void execute();
      virtual ~Orders()  = default; //virtual destructor// do i need this maybe not i will remove 
      friend ostream& operator<<(ostream& os , const Orders& otherOrder);
      virtual void print(ostream& os) const;

  
};

class DeployOrder : public Orders{
    public:
      DeployOrder();
      DeployOrder(int numberOfArmyUnits , string sourceTerritory , string targetTerritory) ;
      DeployOrder(const DeployOrder& deploy);
      friend ostream& operator<<(ostream& os , const DeployOrder& deploy);
      DeployOrder& operator=(const DeployOrder& otherDeployOrder);
      void execute();
      void validate();
      void print(ostream& os) const;

   
 };



class Negotiate : public Orders{
  public:
    Negotiate();
    Negotiate(int numberOfArmyUnits , string sourceTerritory , string targetTerritory);
    Negotiate(const Negotiate& otherNegotiate);
    Negotiate& operator=(const Negotiate& otherNegotiate);
    void print(ostream& os) const;
    void execute();
    void validate();
    friend ostream& operator<<(ostream& os , const Negotiate& negotiate);


};


class Bomb : public Orders{
  public:
    Bomb();
    Bomb(int numberOfArmyUnits, string sourceTerritory, string targetTerritory);
    Bomb(const Bomb& otherBomb);
    Bomb& operator=(const Bomb& otherBomb);
    friend ostream& operator<<(ostream& os , const Bomb& bomb);
    void execute();
    void validate();
    void print(ostream& os) const;

};


class Airlift : public Orders{
  public:
    Airlift();
    Airlift(int numberOfArmyUnits , string sourceTerritory , string targetTerritory);
    Airlift(const Airlift& otherAirlift);
    Airlift& operator=(const Airlift& otherAirlift );
    friend ostream& operator<<(ostream& os , const Airlift& airlift);
    void execute();
    void validate();
    void print(ostream& os) const;

};


class Advance : public Orders{
  public:
    Advance();
    Advance(int numberOfArmyUnits, string sourceTerritory, string targetTerritory);
    Advance(const Advance& otherAdvance);
    Advance& operator=(const Advance& otherAdvance);
    friend ostream& operator<<(ostream& os , const Advance& advance);
    void execute();
    void validate();
    void print(ostream& os) const;

};

class Blockade : public Orders{
  public:
    Blockade();
    Blockade(int numberOfArmyUnits, string sourceTerritory, string targetTerritory);
    Blockade(const Blockade& otherBlockade);
    Blockade& operator=(const Blockade& otherBlockade);
    friend ostream& operator<<(ostream& os , const Advance& advance);
    void execute();
    void validate();
    void print(ostream& os) const;

};



class Orderlist {
public:
    Orderlist() = default;
    std::vector<std::unique_ptr<Orders>> orderList;//the data member of orderlist 
    void remove(Orders& order);
    void move(Orders& order , int index);


};



#endif






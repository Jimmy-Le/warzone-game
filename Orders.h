#ifndef ORDERS_H
#define ORDERS_H
#include  <typeinfo>
#include <memory>
#include <algorithm>
#include <cctype>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "LoggingObserver.h"
class Player; //forward declaration to avoid circular dependency

using namespace std;


//now we will decalre the class orders 
class Orders : public Subject, public ILoggable {
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
      virtual bool validate(Player& player ) ; //only in case we have base pointer ti an object of child class 
      virtual int execute(Player& player);     // returns the status
      virtual ~Orders()  = default; //virtual destructor// do i need this maybe not i will remove 
      friend ostream& operator<<(ostream& os , const Orders& otherOrder);
      virtual void print(ostream& os) const;
      std::string stringToLog() override;

  
};

class DeployOrder : public Orders{
    public:
      DeployOrder();
      DeployOrder(int numberOfArmyUnits , string sourceTerritory , string targetTerritory) ;
      DeployOrder(const DeployOrder& deploy);
      friend ostream& operator<<(ostream& os , const DeployOrder& deploy);
      DeployOrder& operator=(const DeployOrder& otherDeployOrder);
      int execute(Player& player);
      bool validate(Player& player);
      void print(ostream& os) const;

   
 };



class Negotiate : public Orders{
  public:
    Negotiate();
    Negotiate(int numberOfArmyUnits , string sourceTerritory , string targetTerritory , string enemy);
    Negotiate(const Negotiate& otherNegotiate);
    Negotiate& operator=(const Negotiate& otherNegotiate);
    void print(ostream& os) const;
    int execute(Player& player);
    bool validate(Player& player);
    friend ostream& operator<<(ostream& os , const Negotiate& negotiate);
    string getEnemy() const { return enemy ; }; //TODO: I BELIEVE THE GET IS SPECIFIC METHOD FOR THE UNIQUE PTR
    void setEnemy( string enemy){ this->enemy = enemy ; };
    private:
      string enemy;


};


class Bomb : public Orders{
  public:
    Bomb();
    Bomb(int numberOfArmyUnits, string sourceTerritory, string targetTerritory);
    Bomb(const Bomb& otherBomb);
    Bomb& operator=(const Bomb& otherBomb);
    friend ostream& operator<<(ostream& os , const Bomb& bomb);
    int execute(Player& player);
    bool validate(Player& player);
    void print(ostream& os) const;

};


class Airlift : public Orders{
  public:
    Airlift();
    Airlift(int numberOfArmyUnits , string sourceTerritory , string targetTerritory);
    Airlift(const Airlift& otherAirlift);
    Airlift& operator=(const Airlift& otherAirlift );
    friend ostream& operator<<(ostream& os , const Airlift& airlift);
    int execute(Player& player);
    bool validate(Player& player);
    void print(ostream& os) const;

};


class Advance : public Orders{
  public:
    Advance();
    Advance(int numberOfArmyUnits, string sourceTerritory, string targetTerritory);
    Advance(const Advance& otherAdvance);
    Advance& operator=(const Advance& otherAdvance);
    friend ostream& operator<<(ostream& os , const Advance& advance);
    int execute(Player& player);
    bool validate(Player& player);
    void print(ostream& os) const;

};

class Blockade : public Orders{
  public:
    Blockade();
    Blockade(int numberOfArmyUnits, string sourceTerritory, string targetTerritory);
    Blockade(const Blockade& otherBlockade);
    Blockade& operator=(const Blockade& otherBlockade);
    friend ostream& operator<<(ostream& os , const Advance& advance);
    int execute(Player& player);
    bool validate(Player& player);
    void print(ostream& os) const;

};



class Orderlist : public Subject, public ILoggable {
public:
    Orderlist() = default;
    std::vector<std::unique_ptr<Orders>> orderList;//the data member of orderlist 
    void remove(Orders& order);
    void move(Orders& order , int index);
    std::string stringToLog() override;


};

#endif









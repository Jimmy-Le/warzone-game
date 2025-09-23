#ifndef DEPLOYORDER_H
#define DEPLOYORDER_H
#include "Orders.h"
#include <iostream>
using namespace std;



 class DeployOrder : public Orders{
    public:
    friend ostream& operator<<(ostream& os , const DeployOrder& deploy);//friend methods are not inherited
    DeployOrder(int numberOfArmyUnits , string sourceTerritory , string targetTerritory);
 
 };
#endif
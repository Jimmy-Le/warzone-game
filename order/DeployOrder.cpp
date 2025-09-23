#include "DeployOrder.h"


ostream& operator<<(ostream& os , const DeployOrder& deploy){
os <<"DEPLOY ORDER DETAILS: "<<endl;
os << *deploy.numberOfArmyUnits <<" army units are deployed from " ;
os << *deploy.sourceTerritory <<" to " << *deploy.targetTerritory << endl;

return os; 
}

DeployOrder::DeployOrder(int numberOfArmyUnits , string sourceTerritory , string targetTerritory)
    : Orders(numberOfArmyUnits , sourceTerritory , targetTerritory) { // ':' this to call parents class constructor 
}


int main(){
  DeployOrder deploy1 = DeployOrder(10 , "A" , "B");
  cout << deploy1 << endl; //operator overloading
  return 0;
}
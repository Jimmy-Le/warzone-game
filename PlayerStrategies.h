#ifndef PLAYER_STRATEGIES_H
#define PLAYER_STRATEGIES_H
#include <string>
#include <vector>
#include <iostream>
#include "Player.h"
#include <cmath>
using namespace std;


class Player;
class Territory;

//TODO: Make Constructors and Destructors

/*** 
 * --------- Base Strategy class ---------
 * This class is the base class for all player strategies.
 * It holds a pointer to the player it is associated with.
 */
class PlayerStrategy {
    //kindof reversed the Strategy pattern by adding a data member Player to the Strategy rather than having the Player hold a pointer to the strategy
    //Player is context it has a strategy .
    //PlayerStrategy is suppose to be an abstract class / interface;
    protected:
        Player* player;
    public:

        PlayerStrategy(Player* p);
        virtual void issueOrder() = 0;
        virtual std::vector<Territory*>* toAttack() = 0;
        virtual std::vector<Territory*>* toDefend() = 0;

        virtual ~PlayerStrategy();; 
        
};


/*** 
 * --------- Human Player Strategy class ---------
 * This class represents a human player strategy.
 * It basically implements the current Player methods. (allow user input)
 */
class HumanPlayerStrategy : public PlayerStrategy {
    public:
        HumanPlayerStrategy(Player* p);
        void issueOrder() override;
        ~HumanPlayerStrategy();
        std::vector<Territory*>* toAttack() override;
        std::vector<Territory*>* toDefend() override;


};


/***
 * --------- Aggressive Player Strategy class ---------
 * This class represents an aggressive player strategy.
 * It focuses on stacking armies on its strongest territory and attacking.
 * It will also prioritize using offensive cards
 */
class AggressivePlayerStrategy : public PlayerStrategy {
    public:
        AggressivePlayerStrategy(Player* p);
        void issueOrder() override;
        ~AggressivePlayerStrategy();
        std::vector<Territory*>* toAttack() override;
        std::vector<Territory*>* toDefend() override;
};

/*** 
 * --------- Benevolent Player Strategy class ---------
 * This class represents a benevolent player strategy.
 * It focuses on defending its weakest territories and avoids attacking.
 * It will also prioritize using defensive cards
 */
class BenevolentPlayerStrategy : public PlayerStrategy {
    public:
        BenevolentPlayerStrategy(Player *p);
        ~BenevolentPlayerStrategy();
        void issueOrder() override;
        std::vector<Territory*>* toAttack() ;
        std::vector<Territory*>* toDefend() override;
};

/*** 
 * --------- Neutral Player Strategy class ---------
 * This class represents a neutral player strategy.
 * It doesn't do anything until attacked, then it becomes aggressive.
 */
class NeutralPlayerStrategy : public PlayerStrategy {
    public:
        NeutralPlayerStrategy(Player* p);
        ~NeutralPlayerStrategy();
        void issueOrder() override;
        std::vector<Territory*>* toAttack() override;
        std::vector<Territory*>* toDefend() override;
};

/***
 * --------- Cheater Player Strategy class ---------
 * This class represents a cheater player strategy.
 * It automatically conquers all adjacent territories without any combat.
 */
class CheaterPlayerStrategy : public PlayerStrategy {
    public:
        CheaterPlayerStrategy(Player* p);
        void issueOrder() override;
        ~CheaterPlayerStrategy();
        std::vector<Territory*>* toAttack() override;
        std::vector<Territory*>* toDefend() override;
};





























#endif // PLAYER_STRATEGIES_H

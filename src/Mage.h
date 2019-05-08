#ifndef CARDRPG_MAGE_H
#define CARDRPG_MAGE_H

#include <iostream>
#include "Hero.h"

using namespace std;

class Mage : public Hero {
private:
    const int maxShield;
    int currShield;
public:
    Mage (const string & name);

    void removeShield (int amount);
    void addShield (int amount);

    void removeHealth( int amount );

    int getCurrShield() const { return this->currShield; }
    int getMaxShield() const { return this->maxShield; }
    void setCurrShield( int value ) { this->currShield= value; }
};

#endif //CARDRPG_MAGE_H

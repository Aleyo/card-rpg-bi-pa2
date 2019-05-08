#include "Mage.h"

Mage::Mage (const string & name)
        : Hero(name, HeroType::MAGE, 50, 10),
          maxShield(50),
          currShield(0) {
}

void Mage::removeShield(int amount) {
    this->currShield -= amount;
}

void Mage::addShield(int amount) {
    this->currShield += amount;
    if ( this->currShield > this->maxShield )
        this->currShield = this->maxShield;
}

void Mage::removeHealth( int amount ) {
    this->currShield -= amount;
    if(currShield < 0) {
        this->currHealth += currShield;
        this->currShield = 0;
    }
}
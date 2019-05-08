#include "Hero.h"

Hero::Hero(const string &name, HeroType type, int maxHealth, int maxMana)
        : name(name),
          type(type),
          maxHealth(maxHealth),
          maxMana(maxMana),
          currHealth(maxHealth),
          currMana(maxMana / 2) {

}

Hero::~Hero() {

}

void Hero::removeHealth(int amount) {
    this->currHealth -= amount;
}

void Hero::addHealth(int amount) {
    this->currHealth += amount;
    if ( this->currHealth > this->maxHealth )
        this->currHealth = this->maxHealth;
}

void Hero::removeMana(int amount) {
    this->currMana -= amount;
}

void Hero::addMana(int amount) {
    this->currMana += amount;
    if ( this->currMana > this->maxMana )
        this->currMana = this->maxMana;
}

void Hero::insertIntoDeck ( Card * c ) {
    this->deck.push(c);
}

void Hero::insertIntoHand ( Card * c ) {
    this->hand.push_back(c);
}

void Hero::drawCard(int count) {
    for (int i = 0; i < count; i++) {
        if (this->deck.empty())
            break;
        Card * card = this->deck.top();
        this->hand.push_back(card);
        this->deck.pop();
    }
}

void Hero::removeCardHand( int index ) {
    this->hand.erase(this->hand.begin() + index);
}
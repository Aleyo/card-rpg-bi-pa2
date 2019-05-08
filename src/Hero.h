#ifndef CARDRPG_HERO_H
#define CARDRPG_HERO_H

#include "HeroType.h"
#include "Card.h"
#include <iostream>
#include <vector>
#include <map>
#include <stack>

class Card;

using namespace std;

class Hero {
protected:
    const string   name;
    const HeroType type;
    const int      maxHealth;
    const int      maxMana;

    int currHealth;
    int currMana;
    stack<Card *> deck;
    vector<Card *> hand;
public:
    Hero ( const string & name, HeroType type, int maxHealth, int maxMana );
    virtual ~Hero();

    virtual void removeHealth ( int amount );
    void addHealth    ( int amount );

    void removeMana ( int amount );
    void addMana    ( int amount );

    void insertIntoDeck ( Card * c );
    void insertIntoHand ( Card * c );
    void drawCard( int count );
    void removeCardHand( int index );

    vector<Card *> getHand() const { return this->hand; }
    stack<Card *> getDeck() const { return this->deck; }
    string getName() const { return this->name; }
    int getCurrHealth() const { return this->currHealth; }
    int getMaxHealth() const { return this->maxHealth; }
    int getCurrMana() const { return this->currMana; }
    int getMaxMana() const { return this->maxMana; }
    HeroType getHeroType() const { return this->type; }

    void setCurrHealth( int value ) { this->currHealth = value; }
    void setCurrMana( int value ) { this->currMana = value; }
};

#endif //CARDRPG_HERO_H

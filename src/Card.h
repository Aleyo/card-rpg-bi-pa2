#ifndef CARDRPG_CARD_H
#define CARDRPG_CARD_H

class Hero;

#include "HeroType.h"
#include "Hero.h"
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class Card {
protected:
    const int id;
    const HeroType heroType;
    const string name;
    const string text;
    const int manaCost;
    vector<string> effects;
public:
    Card(int id, HeroType heroType,
         int manaCost, const string & name,
         const string & text, vector<string> effects);

    void makeEffects(Hero * me, Hero * enemy);

    int getId () const { return this->id; }
    string getName() const { return this->name; }
    string getText() const { return this->text; }
    vector<string> getEffects() const { return this->effects; }
    int getManaCost() const { return this->manaCost; }
    HeroType getHeroType() const { return this->heroType; }
};

#endif //CARDRPG_CARD_H

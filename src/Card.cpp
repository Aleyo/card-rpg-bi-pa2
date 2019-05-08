#include "Card.h"
#include "Mage.h"

Card::Card(int id, HeroType heroType,
           int manaCost, const string & name,
           const string & text, vector<string> effects)
        : id(id),
          heroType(heroType),
          name(name),
          text(text),
          manaCost(manaCost),
          effects( move(effects) ) {
}

void Card::makeEffects(Hero * me, Hero * enemy) {
    for (auto const & effect: this->effects) {
        stringstream ss(effect);
        vector<string> effectsParsed;

        while( ss.good() ) {
            string substring;
            getline( ss, substring, ' ' );
            effectsParsed.push_back( substring );
        }

        Hero * target;
        if (effectsParsed[0] == "me")
            target = me;
        else if (effectsParsed[0] == "enemy")
            target = enemy;

        if (effectsParsed[1] == "health") {
            if (effectsParsed[2][0] == '+') {
                effectsParsed[2].erase( effectsParsed[2].begin() );
                target->addHealth( stoi(effectsParsed[2]) );
            } else if (effectsParsed[2][0] == '-') {
                effectsParsed[2].erase( effectsParsed[2].begin() );
                target->removeHealth( stoi(effectsParsed[2]) );
            }
        } else if (effectsParsed[1] == "mana") {
            if (effectsParsed[2][0] == '+') {
                effectsParsed[2].erase( effectsParsed[2].begin() );
                target->addMana( stoi(effectsParsed[2]) );
            } else if (effectsParsed[2][0] == '-') {
                effectsParsed[2].erase( effectsParsed[2].begin() );
                target->removeMana( stoi(effectsParsed[2]) );
            }
        } else if (effectsParsed[1] == "shield") {
            if (target->getHeroType() == HeroType::MAGE) {
                if (effectsParsed[2][0] == '+') {
                    effectsParsed[2].erase( effectsParsed[2].begin() );
                    ((Mage *) target)->addShield( stoi(effectsParsed[2]) );
                } else if (effectsParsed[2][0] == '-') {
                    effectsParsed[2].erase( effectsParsed[2].begin() );
                    ((Mage *) target)->removeShield( stoi(effectsParsed[2]) );
                }
            }
        }
    }
    me->removeMana(this->manaCost);
}

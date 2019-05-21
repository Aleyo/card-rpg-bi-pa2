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

/*!
 * \brief Abstract Hero class. It's parent for all types of heroes (mage, warrior, ..)
 */
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

    /*!
     * \brief Virtual method for removing health of a Hero. In some types of heroes wee need to overwrite this method
     * to do something different (mage and his shield).
     * \param amount - amount of health to be removed
     */
    virtual void removeHealth ( int amount );
    void addHealth    ( int amount );

    void removeMana ( int amount );
    void addMana    ( int amount );

    /*!
     * \brief Method for inserting card into players deck
     * \param c - card instance to be inserted
     */
    void insertIntoDeck ( Card * c );

    /*!
     * \brief Method for inserting card into players hand
     * \param c - card instance to be inserted
     */
    void insertIntoHand ( Card * c );

    /*!
     * \brief Method for drawing card from deck. This method draws the top x cards from his deck. If the deck is empty
     * then it does nothing.
     * \param count - number of cards to be drawn
     */
    void drawCard( int count );

    /*!
     * \brief Removes card from players hand on specified index.
     * \param index - index of a card to be removed
     */
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

#ifndef CARDRPG_GAME_H
#define CARDRPG_GAME_H

#include "Hero.h"
#include "OutFunctions.h"
#include "IOhandler.h"

/*!
 * \brief Enum for state of a game (running, game over).
 */
enum class GameState : char;

/*!
 * \brief This class stores details about the specified game.
 */
class Game {
private:
    bool vsAI;

    map<int, Card *> * cards;

    GameState gameState;
    Hero * winner;

    Hero * player1;
    Hero * player2;

    int turn;

    Hero * onTurn;

    void initGame();
    void initGameLoad();
    void loadCardDefinitions();

    /*!
     * \brief Is responsible of cycle of a game. Check if you are on turn or waiting, check input from a player
     * (which card he wants to play) and so.
     */
    void gameLoop();
    void setStartingPlayer();

    /*!
     * \brief This fills the deck of a specified player with random cards loaded from definitions
     * on the start of a game.
     * \param p - pointer to hero who's deck should be filled.
     */
    void createDeck( Hero * p );

    /*!
     * \brief This fills the hand of a specified player on the start of a game.
     * \param p - pointer to hero who's hand should be filled
     */
    void giveCards( Hero * p );

    /*!
     * \brief Get the decision of AI (if playing vs one) on which option to choose (cards, next turn, ...).
     */
    char getAIDecision();
public:
    Game ( Hero * player1, Hero * player2, bool vsAI );
    Game ( const string & src );
    ~Game ();

    /*!
     * \brief End turn for playing player and start turn for other one.
     */
    void nextTurn();

    int getTurn() const { return this->turn; }
    int getVsAI() const { return this->vsAI; }
    Hero *  getPlayer1() const { return this->player1; }
    Hero *  getPlayer2() const { return this->player2; }
    Hero *  getOnTurn() const { return this->onTurn; }
    map<int, Card *> * getCards() const { return this->cards; }

    void setTurn( int value ) { this->turn = value; }
    void setVsAI( int value ) { this->vsAI = value; }
    void setOnTurn ( Hero * hero ) { this->onTurn = hero; }
    void setPlayer1 ( Hero * hero ) { this->player1 = hero; }
    void setPlayer2 ( Hero * hero ) { this->player2 = hero; }
};


#endif //CARDRPG_GAME_H

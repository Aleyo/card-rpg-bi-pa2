#ifndef CARDRPG_GAME_H
#define CARDRPG_GAME_H

#include "Hero.h"
#include "OutFunctions.h"
#include "IOhandler.h"

enum class GameState : char;

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
    void gameLoop();
    void setStartingPlayer();
    void createDeck( Hero * p );
    void giveCards( Hero * p );
    char getAIDecision();
public:
    Game ( Hero * player1, Hero * player2, bool vsAI );
    Game ( const string & src );
    ~Game ();

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

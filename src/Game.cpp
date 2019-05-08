#include "Game.h"

enum class GameState : char { RUNNING, GAME_OVER };

Game::Game(Hero * player1, Hero * player2, bool vsAI)
        : vsAI(vsAI),
          player1(player1),
          player2(player2) {
    this->initGame();
    this->gameLoop();
    if (this->gameState == GameState::GAME_OVER) {
        printWinner(cout, *this->onTurn);
    }
}

Game::Game( const string & src ) {
    this->initGameLoad();
    IOhandler h(src);
    h.loadGame( this );
    this->gameLoop();
    if (this->gameState == GameState::GAME_OVER) {
        printWinner(cout, *this->onTurn);
    }
}

Game::~Game() {
    for (auto const & x : *cards)
        delete x.second;
    delete cards;
    delete player1;
    delete player2;
}

void Game::initGameLoad() {
    this->cards = new map<int, Card *>;
    clearScreen(cout);
    this->loadCardDefinitions();
    this->gameState = GameState::RUNNING;
}

void Game::initGame() {
    this->cards = new map<int, Card *>;
    clearScreen(cout);
    this->loadCardDefinitions();
    this->createDeck(player1);
    this->createDeck(player2);
    this->giveCards(player1);
    this->giveCards(player2);
    this->turn = 1;
    this->gameState = GameState::RUNNING;
    this->setStartingPlayer();
}

void Game::loadCardDefinitions() {
    IOhandler h("./examples/cards.txt");
    h.loadCardDefinition(this->cards);
}

void Game::createDeck( Hero * p ) {
    srand((unsigned int) time(nullptr));
    while (p->getDeck().size() < 30) {
        Card * card = this->cards->find(rand() % this->cards->size())->second;
        if ( card->getHeroType() == p->getHeroType() )
            p->insertIntoDeck(card);
    }
}

void Game::giveCards( Hero * p ) {
    p->drawCard(5);
}

char Game::getAIDecision() {
    for (int i = 0; i < (int) player2->getHand().size(); i++) {
        Card * c = player2->getHand()[i];
        for (int y = 0; y < (int) c->getEffects().size(); y++) {
            if (c->getEffects()[y].substr(0,11) == "me health +"
                    && player2->getCurrHealth() != player2->getMaxHealth()
                    && player2->getCurrMana() >= c->getManaCost()) {
                return (char) (i + 49);
            } else if (c->getEffects()[y].substr(0,14) == "enemy health -"
                       && player2->getCurrMana() >= c->getManaCost()){
                return (char) (i + 49);
            }
        }
    }

    return 'e';
}

void Game::gameLoop() {
    while(this->gameState == GameState::RUNNING) {
        if (!vsAI)
            waitForPlayer(cout, *onTurn);

        while (true) {
            char option;
            if (!vsAI || onTurn == player1) {
                printHeroDetails(std::cout, *onTurn);
                printHeroDetails(std::cout, (onTurn == player1) ? *player2 : *player1);
                printHand(std::cout, *onTurn);
            }
            if (!vsAI || onTurn == player1)
                cout << "Option: ";
            if (onTurn == player2 && vsAI) {
                option = getAIDecision();
            } else
                cin >> option;
            bool validOption = false;
            bool notEnoughMana = false;
            for ( int i = 1; i <= (int) this->onTurn->getHand().size(); i++) {
                if (option == (i + 48)) {
                    if (onTurn->getCurrMana() < onTurn->getHand()[i-1]->getManaCost()) {
                        notEnoughMana = true;
                        validOption = true;
                        break;
                    }
                    this->onTurn
                            ->getHand()[i-1]
                            ->makeEffects(onTurn, (onTurn == player1) ? player2 : player1);
                    this->onTurn->removeCardHand(i-1);

                    // Check if players lost
                    if (player1->getCurrHealth() <= 0) {
                        this->winner = player1;
                        this->gameState = GameState::GAME_OVER;
                    }
                    if (player2->getCurrHealth() <= 0) {
                        this->winner = player2;
                        this->gameState = GameState::GAME_OVER;
                    }
                    validOption = true;
                }
            }
            if (!vsAI || onTurn == player1)
                clearScreen(cout);

            if (this->gameState == GameState::GAME_OVER)
                break;
            if (option == 'e')
                break;
            if (option == 's') {
                IOhandler h("./examples/save.txt");
                h.saveGame( this );
                cout << "Game saved!" << endl;
                printSeparator(std::cout);
                validOption = true;
            }
            if (!validOption && (!vsAI || onTurn == player1)) {
                cout << "Invalid option!" << endl;
                printSeparator(std::cout);
            }
            if (notEnoughMana && (!vsAI || onTurn == player1)) {
                cout << "Not enough mana!" << endl;
                printSeparator(std::cout);
            }
        }

        if (this->gameState == GameState::GAME_OVER)
            break;

        this->onTurn->drawCard(1);
        this->onTurn->addMana(2);
        this->nextTurn();
    }
}

void Game::setStartingPlayer() {
    srand((unsigned int) time(nullptr));
    this->onTurn = rand() % 2 == 1 ? player1 : player2;
}

void Game::nextTurn() {
    this->onTurn = this->onTurn == this->player1 ? this->player2 : this->player1;
    this->turn++;
}


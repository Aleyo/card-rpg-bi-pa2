#include "IOhandler.h"
#include "Warrior.h"

IOhandler::IOhandler (string src) :src(src) {

}

bool IOhandler::loadGame( Game * game ) {
    ifstream inFile(this->src);

    if (!inFile)
        return false;

    try {
        string x;
        string onTurn, player1Name, player2Name;
        getline(inFile, x);
        if (x == "1")
            game->setVsAI(true);
        else
            game->setVsAI(false);
        getline(inFile, x);
        game->setTurn(stoi(x));
        getline(inFile, onTurn);

        // Load player1
        getline(inFile, player1Name);
        getline(inFile, x);
        if (x == "warrior")
            game->setPlayer1(new Warrior(player1Name));
        else
            game->setPlayer1(new Mage(player1Name));
        getline(inFile, x); // SKIP, maxHealth is constant (for future updates)
        getline(inFile, x); // SKIP, maxHealth is constant (for future updates)
        getline(inFile, x);
        game->getPlayer1()->setCurrHealth(stoi(x));
        getline(inFile, x);
        game->getPlayer1()->setCurrMana(stoi(x));

        if (game->getPlayer1()->getHeroType() == HeroType::MAGE) {
            getline(inFile, x);
            ((Mage *) game->getPlayer1())->setCurrShield(stoi(x));
            getline(inFile, x);
        }

        // Load player2
        getline(inFile, player2Name);
        getline(inFile, x);
        if (x == "warrior")
            game->setPlayer2(new Warrior(player2Name));
        else
            game->setPlayer2(new Mage(player2Name));
        getline(inFile, x); // SKIP, maxHealth is constant (for future updates)
        getline(inFile, x); // SKIP, maxHealth is constant (for future updates)
        getline(inFile, x);
        game->getPlayer2()->setCurrHealth(stoi(x));
        getline(inFile, x);
        game->getPlayer2()->setCurrMana(stoi(x));

        if (game->getPlayer2()->getHeroType() == HeroType::MAGE) {
            getline(inFile, x);
            ((Mage *) game->getPlayer2())->setCurrShield(stoi(x));
            getline(inFile, x);
        }


        // Load player onTurn
        if (onTurn == "1")
            game->setOnTurn(game->getPlayer1());
        else
            game->setOnTurn(game->getPlayer2());

        // Load cards
        while (getline(inFile, x)) {
            // Explode line to vector
            stringstream ss(x);
            vector <string> card;

            if (count(x.begin(), x.end(), ' ') != 2)
                return false;

            while (ss.good()) {
                string substring;
                getline(ss, substring, ' ');
                card.push_back(substring);
            }
            // Load player 1 cards
            if (card[1] == "1") {
                Card *tmpCard = game->getCards()->find(stoi(card[0]))->second;
                if (card[2] == "deck")
                    game->getPlayer1()->insertIntoDeck(tmpCard);
                else if (card[2] == "hand")
                    game->getPlayer1()->insertIntoHand(tmpCard);
            }

            // Load player 1 cards
            if (card[1] == "2") {
                Card *tmpCard = game->getCards()->find(stoi(card[0]))->second;
                if (card[2] == "deck")
                    game->getPlayer2()->insertIntoDeck(tmpCard);
                else if (card[2] == "hand")
                    game->getPlayer2()->insertIntoHand(tmpCard);
            }

        }
    } catch (std::exception & e) {
        return false;
    }

    inFile.close();
    return true;
}

bool IOhandler::saveGame( Game * game ) {
    ofstream file (this->src, ios::out | ios::trunc);
    if (!file.is_open())
        return false;

    // Global data
    file << game->getVsAI() << endl;
    file << game->getTurn() << endl;
    file << (game->getOnTurn() == game->getPlayer1() ? '1': '2') << endl;
    // Player 1 data
    file << game->getPlayer1()->getName() << endl;
    file << (game->getPlayer1()->getHeroType() == HeroType::WARRIOR ?
             "warrior": "mage") << endl;
    file << game->getPlayer1()->getMaxHealth() << endl;
    file << game->getPlayer1()->getMaxMana() << endl;
    file << game->getPlayer1()->getCurrHealth() << endl;
    file << game->getPlayer1()->getCurrMana() << endl;
    if (game->getPlayer1()->getHeroType() == HeroType::MAGE) {
        file << ((Mage *) game->getPlayer1())->getCurrShield() << endl;
        file << ((Mage *) game->getPlayer1())->getMaxShield() << endl;
    }

    // Player 2 data
    file << game->getPlayer2()->getName() << endl;
    file << (game->getPlayer2()->getHeroType() == HeroType::WARRIOR ?
             "warrior": "mage") << endl;
    file << game->getPlayer2()->getMaxHealth() << endl;
    file << game->getPlayer2()->getMaxMana() << endl;
    file << game->getPlayer2()->getCurrHealth() << endl;
    file << game->getPlayer2()->getCurrMana() << endl;
    if (game->getPlayer2()->getHeroType() == HeroType::MAGE) {
        file << ((Mage *) game->getPlayer2())->getCurrShield() << endl;
        file << ((Mage *) game->getPlayer2())->getMaxShield() << endl;
    }

    // Player 1 deck stack data
    stack<Card *> tmp = game->getPlayer1()->getDeck();
    while (!tmp.empty()) {
        file << tmp.top()->getId() << " 1 deck" << endl;
        tmp.pop();
    }

    // Player 1 hand cards
    for(auto const & card: game->getPlayer1()->getHand()) {
        file << card->getId() << " 1 hand" << endl;
    }

    // Player 2 deck stack data
    stack<Card *> tmp2 = game->getPlayer2()->getDeck();
    while (!tmp2.empty()) {
        file << tmp2.top()->getId() << " 2 deck" << endl;
        tmp2.pop();
    }

    // Player 2 hand cards
    for(auto const & card: game->getPlayer2()->getHand()) {
        file << card->getId() << " 2 hand" << endl;
    }

    file.close();
    return true;
}



bool IOhandler::loadCardDefinition( map<int, Card * > * cards ) {
    ifstream inFile(this->src);

    if (!inFile)
        return false;

    int attribute = 0;
    string x;
    int id, manaCost;
    string name, heroType, text;
    vector<string> effects;

    try {
        while (getline(inFile, x)) {
            if (x[0] != '#') {
                switch (attribute) {
                    case 0:
                        id = stoi(x);
                        break;
                    case 1:
                        name = x;
                        break;
                    case 2:
                        heroType = x;
                        break;
                    case 3:
                        manaCost = stoi(x);
                        break;
                    case 4:
                        text = x;
                        break;
                    default:
                        if (x == "") {
                            if (effects.empty())
                                return false;

                            attribute = 0;
                            HeroType type = (heroType == "warrior") ? HeroType::WARRIOR : HeroType::MAGE;
                            cards->insert({id, new Card(id, type, manaCost, name, text, effects)});
                            effects.clear();
                            continue;
                        } else {
                            if (count(x.begin(), x.end(), ' ') != 2)
                                return false;
                            effects.push_back(x);
                        }
                        break;
                }
                attribute++;
            }
        }
    } catch (std::exception &e) {
        return false;
    }

    inFile.close();
    return true;
}

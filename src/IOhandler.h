#ifndef CARDRPG_IOHANDLER_H
#define CARDRPG_IOHANDLER_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "Game.h"
#include "Card.h"

class Game;

using namespace std;

class IOhandler {
private:
    string src;
public:
    IOhandler (string src);

    bool loadCardDefinition( map<int, Card *> * cards );
    bool saveGame( Game * game );
    bool loadGame( Game * game );
};


#endif //CARDRPG_IOHANDLER_H

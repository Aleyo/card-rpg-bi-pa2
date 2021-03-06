#ifndef CARDRPG_IOHANDLER_H
#define CARDRPG_IOHANDLER_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <vector>
#include "Game.h"
#include "Card.h"

class Game;

using namespace std;

/*!
 * \brief Class that parse files and load them.
 */
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

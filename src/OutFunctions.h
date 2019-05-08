#ifndef CARDRPG_OUTFUNCTIONS_H
#define CARDRPG_OUTFUNCTIONS_H

#include "Hero.h"
#include "Mage.h"

using namespace std;

ostream & printHand (ostream & os, Hero & hero);
ostream & printHeroDetails (ostream & os, Hero & hero);
ostream & printSeparator (ostream & os);
ostream & clearScreen (ostream & os);
ostream & waitForPlayer (ostream & os, Hero & hero);
ostream & printWinner (ostream & os, Hero & hero);


#endif //CARDRPG_OUTFUNCTIONS_H

#include "OutFunctions.h"

ostream & printSeparator (ostream & os) {
    os << "======================================" << endl;
    return os;
}

ostream & printHand (ostream & os, Hero & hero) {
    int index = 1;
    os << hero.getName() << "'s hand:" << endl;
    for (auto const & card: hero.getHand()) {
        os << "    " << index++ << ". " << card->getName() << " ("
           << card->getManaCost() << "): "
           << card->getText() << endl;
    }
    os << "--------------------------------------"<< endl;
    os << "    e) end turn" << endl;
    os << "    s) save game" << endl;
    printSeparator(os);
    return os;
}

ostream & printHeroDetails (ostream & os, Hero & hero) {
    os << hero.getName() << " ["
       << (hero.getHeroType() == HeroType::WARRIOR ? "Warrior" : "Mage")
       << "]: " << endl;
    if (hero.getHeroType() == HeroType::MAGE)
        os << "    Shield: " << ((Mage &) hero).getCurrShield()
           << "/" << ((Mage &) hero).getMaxShield() << endl;
    os << "    Health: " << hero.getCurrHealth() << "/" << hero.getMaxHealth() << endl
       << "    Mana: " << hero.getCurrMana() << "/" << hero.getMaxMana() << endl;
    printSeparator(os);
    return os;
}

ostream & printWinner (ostream & os, Hero & hero) {
    os << "!Player " << hero.getName() << " WON!" << endl << endl;
    return os;
}

ostream & clearScreen (ostream & os) {
    os << "\033[2J\033[1;1H";
    return os;
}

ostream & waitForPlayer (ostream & os, Hero & hero) {
    clearScreen(os);
    os << "Press enter when player " << hero.getName() << " is ready" << endl;
    getchar();
    getchar();
    clearScreen(os);
    return os;
}

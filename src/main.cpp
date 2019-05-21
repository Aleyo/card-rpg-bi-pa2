#include "Game.h"
#include "Warrior.h"
#include "Mage.h"
#include "Hero.h"

int main() {

    char option;
    clearScreen(cout);
    while (true) {
        cout << "Card RPG menu: " << endl;
        cout << "   1) New game (2 players)" << endl;
        cout << "   2) New game (vs AI)" << endl;
        cout << "   3) Continue game" << endl;
        cout << "   4) Exit game" << endl;
        cin >> option;

        clearScreen(cout);
        if (option == '1') {
            Hero * p1;
            Hero * p2;
            string player1Name, player2Name;
            while (true) {
                // init player 1
                clearScreen(cout);
                cout << "Enter player 1 name: " << endl;
                cin.ignore();
                getline(cin, player1Name);
                if (player1Name == "")
                    continue;

                while (true) {
                    clearScreen(cout);
                    char p1Hero;
                    cout << "Select " << player1Name << "'s hero:" << endl;
                    cout << "   1) Warrior" << endl;
                    cout << "   2) Mage" << endl;
                    cin >> p1Hero;
                    if (p1Hero == '1')
                        p1 = new Warrior(player1Name);
                    else if (p1Hero == '2')
                        p1 = new Mage(player1Name);
                    else
                        continue;
                    break;
                }
                break;
            }

            while (true) {
                // init player 2
                clearScreen(cout);
                cout << "Enter player 2 name: " << endl;
                cin.ignore();
                getline(cin, player2Name);
                if (player2Name == "")
                    continue;

                while (true) {
                    clearScreen(cout);
                    char p2Hero;
                    cout << "Select " << player2Name << "'s hero:" << endl;
                    cout << "   1) Warrior" << endl;
                    cout << "   2) Mage" << endl;
                    cin >> p2Hero;
                    if (p2Hero == '1')
                        p2 = new Warrior(player2Name);
                    else if (p2Hero == '2')
                        p2 = new Mage(player2Name);
                    else
                        continue;
                    break;
                }
                break;
            }

            Game(p1, p2, false);
        } else if (option == '2') {
            Hero * p1;
            Hero * p2;
            string player1Name;
            while (true) {
                // init player 1
                clearScreen(cout);
                cout << "Enter player name: " << endl;
                cin.ignore();
                getline(cin, player1Name);
                if (player1Name == "")
                    continue;

                while (true) {
                    clearScreen(cout);
                    char p1Hero;
                    cout << "Select " << player1Name << "'s hero:" << endl;
                    cout << "   1) Warrior" << endl;
                    cout << "   2) Mage" << endl;
                    cin >> p1Hero;
                    if (p1Hero == '1')
                        p1 = new Warrior(player1Name);
                    else if (p1Hero == '2')
                        p1 = new Mage(player1Name);
                    else
                        continue;
                    break;
                }
                break;
            }
            p2 = new Warrior("xt-002 destructor");
            Game(p1, p2, true);
        } else if (option == '3') {
            fstream ifile("./examples/save.txt");
            if (!ifile)
                continue;
            Game("./examples/save.txt");
        } else if (option == '4') {
            exit(0);
        }
    }

    return 0;
}
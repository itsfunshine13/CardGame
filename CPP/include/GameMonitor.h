#ifndef GAME_MONITOR_H_
#define GAME_MONITOR_H_

#include "Card.h"
#include "Profile.h"

#include <string>
#include <map>
#include <iostream>

using namespace std;

class GameMonitor
{
private:
    Profile m_currProfile;
    Deck    m_currDeck;

    map<int, Card>       *ptr_masterCardList;
    map<string, Profile> *ptr_profileDB;

    bool m_profileSet;
    bool m_deckSet;
    
public:
    GameMonitor(map<int, Card> *masterCardList, map<string, Profile> *profileDB);
    ~GameMonitor();

    // Helper functions
    void displayCardSet(Rarity rType);
    void displayDeckCreation(vector<Card> cards);

    // Menu functions
    void mainMenu();
    void playGameMenu();
    void cardInformationMenu();
    void gameRulesMenu();

    void loadProfileMenu();
    void changeProfileMenu();
    void newProfileMenu();

    void changeDeckMenu();
    void createDeckMenu();

    string editDeckNameMenu();
    void addBasicCardMenu(Deck *deck);
    void addAdvCardMenu(Deck *deck);
    void removeCardMenu(Deck *deck);


};


#endif

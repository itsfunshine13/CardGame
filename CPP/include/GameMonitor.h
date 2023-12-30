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

    void displayCardSet(Rarity rType);

    void mainMenu();
    void playGameMenu();
    void loadProfileMenu();
    void cardInformationMenu();
    void gameRulesMenu();
    void changeDeckMenu();
    void createDeckMenu();
    void changeProfileMenu();
    void newProfileMenu();

};


#endif

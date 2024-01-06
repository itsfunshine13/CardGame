#ifndef GAME_MONITOR_H_
#define GAME_MONITOR_H_

#include "Card.h"
#include "Profile.h"
#include "BattleMonitor.h"

#include <string>
#include <map>
#include <iostream>

using namespace std;

class GameMonitor
{
private:
    BattleMonitor m_battleMonitor;
    Profile       m_currProfile;
    Deck          m_currDeck;

    // Set these bools if profile/deck is picked or created
    bool m_profileSet;
    bool m_deckSet;
    
public:
    GameMonitor();
    ~GameMonitor();

    // Helper functions
    void displayCardSet(Rarity rType);
    void displayDeck(vector<Card> cards);
    bool addCardValidation(Deck *deck, string cardID, uint8_t limit);
    Deck getRdmBotDeck();
    // Basic Cards: choice = 0 | Adv Cards: choice = 0
    string cardVectorToJsonStr(vector<Card> cards, int choice);
    void addDeckToProfileDB();
    void saveAll();

    // Menu functions
    void mainMenu();
    void playGameMenu();
    void cardInformationMenu();
    void gameRulesMenu();
    void saveMenu();

    // Profile Menus
    void loadProfileMenu();
    void changeProfileMenu();
    void newProfileMenu();

    // Deck Menus
    void changeDeckMenu();
    void createDeckMenu();
    string editDeckNameMenu();
    void addOrRmBasicCardMenu(Deck *deck);
    void addOrRmAdvCardMenu(Deck *deck);

};


#endif

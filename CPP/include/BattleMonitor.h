#ifndef BATTLE_MONITOR_H_
#define BATTLE_MONITOR_H_

#include "Deck.h"
#include "Player.h"
#include "Profile.h"

#include <iostream>
#include <string>

using namespace std;

class BattleMonitor
{
private:
    Profile m_palyerProfile;
    Profile m_otherProfile;
    Deck    m_playerDeck;
    Deck    m_otherDeck;

    Player m_player;
    Player m_otherPlayer;


public:
    BattleMonitor();
    ~BattleMonitor();

    void newBattle(Profile t_palyerProfile, 
                   Profile t_otherProfile,
                      Deck t_playerDeck, 
                      Deck t_otherDeck);

    // Helper functions
    string fmtBattleRoundStr(string yourCard, string otherCard);
};


#endif
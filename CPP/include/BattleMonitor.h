#ifndef BATTLE_MONITOR_H_
#define BATTLE_MONITOR_H_

#include "Deck.h"
#include "Player.h"
#include "Profile.h"

#include <iostream>
#include <string>

using namespace std;

#define DEFAULT_MAX_PHASE 5

class BattleMonitor
{
private:
    Profile m_palyerProfile;
    Profile m_otherProfile;
    Deck    m_playerDeck;
    Deck    m_otherDeck;

    Player m_player;
    Player m_otherPlayer;

    uint8_t m_currPhaseNumber;
    uint8_t m_CCRemainingPlayer;
    uint8_t m_CCRemainingOther;
    Card    m_playerPlayedCard;
    Card    m_otherPlayedCard;

public:
    BattleMonitor();
    ~BattleMonitor();

    void newBattle(Profile t_palyerProfile, 
                   Profile t_otherProfile,
                      Deck t_playerDeck, 
                      Deck t_otherDeck);

    void procBattle(Card playerCard, Card otherCard);

    // Helper functions
    void displayBattleScreen(string t_playerCardsPlayed[5], string  t_otherCardsPlayed[5]);
    string fmtBattleRoundStr(string yourCard, string otherCard);
    bool validatePlayerCardPick(char t_inputChar, bool *mustPlayCore);
    Card getPlayedCardOther();
};


#endif
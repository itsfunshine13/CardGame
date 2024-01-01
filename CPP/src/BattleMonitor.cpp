#include "../include/BattleMonitor.h"
#include "../include/Deck.h"
#include "../include/Profile.h"

#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

#define DEFAULT_HP 5
#define PAD_LENGTH 18

static char   t_inputChar;
static string t_inputStr;

BattleMonitor::BattleMonitor() {}
BattleMonitor::~BattleMonitor() {}

void BattleMonitor::newBattle(Profile t_palyerProfile, Profile t_otherProfile, Deck t_playerDeck, Deck t_otherDeck)
{
    // CHANGE BACK
    bool t_battleEnd = true;

    string t_playerCardsPlayed[7] = {"","","","","","",""};
    string t_otherCardsPlayed[7]  = {"","","","","","",""};
    
    this->m_player      = Player(t_palyerProfile.getProfileName(), t_playerDeck, DEFAULT_HP);
    this->m_otherPlayer = Player(t_otherProfile.getProfileName(),  t_otherDeck, DEFAULT_HP);

    // Rebuild player's playdeck and shuffle cards
    this->m_player.getDeck()->rebuildPlayDeck();
    this->m_player.getDeck()->shufflePlayDeck();
    // Rebuild other's playdeck and shuffle cards
    this->m_otherPlayer.getDeck()->rebuildPlayDeck();
    this->m_otherPlayer.getDeck()->shufflePlayDeck();

    // Player draws cards
    this->m_player.initHand();
    this->m_player.fillHand();
    this->m_player.displayHand();

    while (t_battleEnd == false)
    {
        //clear console screen
        system("cls");

        cout << "Profile: " << t_palyerProfile.getProfileName() << endl;
        cout << "   Deck: " << t_playerDeck.getDeckName() << endl;
        cout << endl;
        cout << "========================================" << endl;
        cout << "You - " << this->m_player.getHP() << "          |Bot - " << this->m_otherPlayer.getHP() << endl;
        cout << "1. " << fmtBattleRoundStr(t_playerCardsPlayed[0], t_otherCardsPlayed[0]) << endl;
        cout << "2. " << fmtBattleRoundStr(t_playerCardsPlayed[1], t_otherCardsPlayed[1]) << endl;
        cout << "3. " << fmtBattleRoundStr(t_playerCardsPlayed[2], t_otherCardsPlayed[2]) << endl;
        cout << "4. " << fmtBattleRoundStr(t_playerCardsPlayed[3], t_otherCardsPlayed[3]) << endl;
        cout << "5. " << fmtBattleRoundStr(t_playerCardsPlayed[4], t_otherCardsPlayed[4]) << endl;
        cout << "6. " << fmtBattleRoundStr(t_playerCardsPlayed[5], t_otherCardsPlayed[5]) << endl;
        cout << "7. " << fmtBattleRoundStr(t_playerCardsPlayed[6], t_otherCardsPlayed[6]) << endl;
        cout << endl;
        cout << "Your Cards:" << endl;
        this->m_player.displayHand();
        cout << endl;
        cout << "0. Quit Battle" << endl; 
        cout << "Play Card [0-7]: ";
        cin >> t_inputChar;

        switch (t_inputChar)
        {
        case '1': 
            break;
        case '2': 
            break;
        case '3': 
            break;
        case '4': 
            break;
        case '5': 
            break;
        case '6': 
            break;
        case '7': 
            break;
        default:
            cout << endl;
            cout << "Invalid Input" << endl;
            sleep(2); //sleep for 2s
            break;
        } //eos
    } //eow
    
} //eo newBattle

string BattleMonitor::fmtBattleRoundStr(string yourCard, string otherCard)
{
    string ret_string = " " + yourCard;

    while (ret_string.length() < PAD_LENGTH)
    {
        ret_string.append(" ");
    }
    ret_string.append("| ");
    ret_string.append(otherCard);
    return ret_string;
}//eo fmtBattleRoundStr
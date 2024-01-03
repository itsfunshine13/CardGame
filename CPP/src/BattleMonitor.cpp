#include "../include/BattleMonitor.h"
#include "../include/Deck.h"
#include "../include/Profile.h"
#include "../include/commonTypes.h"

#include <iostream>
#include <map>
#include <string>
#include <unistd.h>

using namespace std;

#define PAD_LENGTH 18

// Define Global variables
extern map<int, Card> masterCardList;
extern map<string, Profile> profileDB;

static char   t_inputChar;
static string t_inputStr;

BattleMonitor::BattleMonitor() {}

BattleMonitor::~BattleMonitor() {}

void BattleMonitor::newBattle(Profile t_palyerProfile, Profile t_otherProfile, Deck t_playerDeck, Deck t_otherDeck)
{
    // Temp Battle variables
    bool    t_battleEnd     = false;
    bool    t_procBattle    = true;
    bool    t_mustPlayCore  = false;
    
    this->m_currPhaseNumber       = 1;
    this->m_CCRemainingPlayer = 3;
    this->m_CCRemainingOther  = 3;

    string  t_playerCardsPlayed[5] = {"","","","",""};
    string  t_otherCardsPlayed[5]  = {"","","","",""};

    Card t_playedCardPlayer;
    Card t_playedCardOther;

    // Set each players HP
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
    
    // Other Player draws cards
    this->m_otherPlayer.initHand();
    this->m_otherPlayer.fillHand();

    while (t_battleEnd == false)
    {
        //clear console screen
        system("cls");

        cout << "Profile: " << t_palyerProfile.getProfileName() << endl;
        cout << "   Deck: " << t_playerDeck.getDeckName() << endl;
        cout << endl;
        cout << "========================================" << endl;
        cout << "You - " << this->m_player.getHP() << " HP           |Bot - " << this->m_otherPlayer.getHP() << "HP" << endl;
        cout << "1. " << fmtBattleRoundStr(t_playerCardsPlayed[0], t_otherCardsPlayed[0]) << endl;
        cout << "2. " << fmtBattleRoundStr(t_playerCardsPlayed[1], t_otherCardsPlayed[1]) << endl;
        cout << "3. " << fmtBattleRoundStr(t_playerCardsPlayed[2], t_otherCardsPlayed[2]) << endl;
        cout << "4. " << fmtBattleRoundStr(t_playerCardsPlayed[3], t_otherCardsPlayed[3]) << endl;
        cout << "5. " << fmtBattleRoundStr(t_playerCardsPlayed[4], t_otherCardsPlayed[4]) << endl;
        cout << endl;
        cout << "Your Cards:" << endl;
        this->m_player.displayHand();
        cout << endl;
        cout << "0. Quit Battle" << endl; 
        cout << "Play Card: ";
        cin >> t_inputChar;

        if(t_inputChar == '0')
        {
            t_battleEnd = true;
        }
        else if (validatePlayerCardPick(t_inputChar, &t_mustPlayCore))
        {
            int t_handIdx = t_inputChar - '0';
            t_playedCardPlayer = this->m_player.playCard(t_handIdx-1);
            t_playedCardOther  = getPlayedCardOther();

            t_playerCardsPlayed[this->m_currPhaseNumber-1] = t_playedCardPlayer.getCardName();
            t_otherCardsPlayed[this->m_currPhaseNumber-1]  = t_playedCardOther.getCardName();
            
            // Decrement remaining CoreCards thats must be played
            if (t_playedCardPlayer.isCore()) { this->m_CCRemainingPlayer--; }
            if (t_playedCardOther.isCore())  { this->m_CCRemainingOther--;  }
            this->m_currPhaseNumber++;
        }
        else
        {
            if (t_mustPlayCore)
            {
                cout << "Must play a Core Card!" << endl;
                sleep(2);
            }
            else
            {
                cout << "Invalid Input" << endl;
                sleep(2); //sleep for 2s
            }  
        }
        
        if(this->m_currPhaseNumber > DEFAULT_MAX_PHASE)
        {
            // Reset everything
        }
    } //eow
    
} //eo newBattle

string BattleMonitor::fmtBattleRoundStr(string yourCard, string otherCard)
{
    string ret_string = yourCard;

    while (ret_string.length() < PAD_LENGTH)
    {
        ret_string.append(" ");
    }
    ret_string.append("| ");
    ret_string.append(otherCard);
    return ret_string;
}//eo fmtBattleRoundStr

bool BattleMonitor::validatePlayerCardPick(char t_inputChar, bool *mustPlayCore)
{ 
    int t_handIdx = t_inputChar - '0';
    int remainingPhases = (DEFAULT_MAX_PHASE-this->m_currPhaseNumber)+1;
    // Must pick from hand and core restriction
    if(((t_handIdx-1) < int(this->m_player.getHand().size())) && 
        (m_CCRemainingPlayer < remainingPhases))
    {
        return true;
    } // eoi
    else if ((m_CCRemainingPlayer == remainingPhases) && (t_handIdx <= remainingPhases))
    {
        return true;
    }
    else if ((m_CCRemainingPlayer == remainingPhases) && (t_handIdx > remainingPhases))
    {
        *mustPlayCore = true;
    }
    return false;
} //eo validateCardPick

Card BattleMonitor::getPlayedCardOther()
{
    Card retCard;
    int  t_handIdx;
    bool mustPlayCore = ((m_CCRemainingOther) <= ((DEFAULT_MAX_PHASE-this->m_currPhaseNumber)+1));
    bool findNewCard = true;

    while (findNewCard)
    {
        t_handIdx = rand() % int(this->m_otherPlayer.getHand().size());
        retCard = this->m_otherPlayer.getHand().at(t_handIdx);
        findNewCard = false;
    } //eow
    return retCard;
} //eo getOtherPlayerCard
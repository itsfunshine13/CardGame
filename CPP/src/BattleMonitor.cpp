#include "../include/BattleMonitor.h"
#include "../include/Deck.h"
#include "../include/Profile.h"
#include "../include/commonTypes.h"

#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <unistd.h>

using namespace std;

#define PAD_LENGTH 18

typedef void (*ActionPtr) (Player*, int);

// Define Global variables
extern map<int, Card> masterCardList;
extern map<string, Profile> profileDB;

static char   t_inputChar;
static string t_inputStr;

void TakeDmg(Player *player, int amt)
{
    player->takeDmg(amt);
} //eo takeDmg

void Heal(Player *player, int amt)
{
    player->heal(amt);
} //eo heal

void IncreaseMaxHP(Player *player, int amt)
{
    player->increaseMaxHP(amt);
} //eo increaseMaxHP

BattleMonitor::BattleMonitor() {}

BattleMonitor::~BattleMonitor() {}

void BattleMonitor::newBattle(Profile t_palyerProfile, Profile t_otherProfile, Deck t_playerDeck, Deck t_otherDeck)
{
    // Temp Battle variables
    bool    t_battleEnd     = false;
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

    // BATTLE LOOP
    while (t_battleEnd == false)
    {
        displayBattleScreen(t_playerCardsPlayed, t_otherCardsPlayed);
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

            // Process Battle Phase
             procBattle(t_playedCardPlayer, t_playedCardOther);
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
        // Reset everything for new round
        if(this->m_currPhaseNumber > DEFAULT_MAX_PHASE)
        {
            displayBattleScreen(t_playerCardsPlayed, t_otherCardsPlayed);
            sleep(3);

            this->m_currPhaseNumber = 1;
            this->m_player.fillHand();
            this->m_otherPlayer.fillHand();

            for (int i = 0; i < 5; i++)
            {
                t_playerCardsPlayed[i] = "";
                t_otherCardsPlayed[i]  = "";
            }//eof
            
        }

        // CHECK FOR PLAYER DEFEAT
        if (this->m_player.getHP() == 0)
        {
            cout << this->m_otherProfile.getProfileName() << " WINS" << endl;
            sleep(3);
            t_battleEnd = true;
        }
        else if (this->m_otherPlayer.getHP() == 0)
        {
            cout << this->m_palyerProfile.getProfileName() << " WINS" << endl;
            sleep(3);
            t_battleEnd = true;
        }
        
    } //eow
    
}//eo newBattle

void BattleMonitor::procBattle(Card playerCard, Card otherCard)
{
    queue<ActionPtr> actionQueue;
    queue<pair<Player*, int>> pairQueue;

    void (*ActionPtr) (Player*, int);

    pair<Action,Action> t_actionList[TOTAL_CARD_ACTIONS];
    t_actionList[0] = pair<Action,Action>(playerCard.getFirstAction(), otherCard.getFirstAction());
    t_actionList[1] = pair<Action,Action>(playerCard.getSecondAction(), otherCard.getSecondAction());

    for (uint8_t actionIdx = 0; actionIdx < TOTAL_CARD_ACTIONS; actionIdx++)
    {
        // PLAYER ACTION ONE: Attack - check if MS
        // PLAYER ACTION ONE: Defend
        // PLAYER ACTION ONE: Heal - check if LB

        switch (t_actionList[actionIdx].first)
        {
        case ATTACK_ACTION:
            switch (t_actionList[actionIdx].second)
            {
                case ATTACK_ACTION:
                    // Mighty Swing vs Mighty Swing
                    if ((playerCard.getID().compare(to_string(ADV_MIGHTY_SWING_ID)) == 0) && 
                        (otherCard.getID().compare(to_string(ADV_MIGHTY_SWING_ID))) == 0)
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_player,      2));
                        pairQueue.push(pair<Player*, int>(&this->m_otherPlayer, 2));
                    }
                    // Attack vs Mighty Swing
                    else if ((playerCard.getID().compare(to_string(ADV_MIGHTY_SWING_ID)) != 0) && 
                             (otherCard.getID().compare(to_string(ADV_MIGHTY_SWING_ID))) == 0)
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_player,      2));
                        pairQueue.push(pair<Player*, int>(&this->m_otherPlayer, 1));
                    }
                    // Mighty Swing vs Attack
                    else if ((playerCard.getID().compare(to_string(ADV_MIGHTY_SWING_ID)) == 0) && 
                             (otherCard.getID().compare(to_string(ADV_MIGHTY_SWING_ID))) != 0)
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_player,      1));
                        pairQueue.push(pair<Player*, int>(&this->m_otherPlayer, 2));
                    }
                    // Attack vs Attack
                    else
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_player,      1));
                        pairQueue.push(pair<Player*, int>(&this->m_otherPlayer, 1));
                    }
                    ActionPtr = TakeDmg;
                    actionQueue.push(ActionPtr);
                    actionQueue.push(ActionPtr);
                    break;
                case DEFEND_ACTION:
                    // Attack vs Block - Do nothing
                    break;
                case HEAL_ACTION:
                    // Mighty Swing vs Heal
                    if ((playerCard.getID().compare(to_string(ADV_MIGHTY_SWING_ID)) == 0))
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_otherPlayer, 3));
                    }
                    // Attack vs Heal
                    else
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_otherPlayer, 1));
                    }
                    ActionPtr = TakeDmg;
                    actionQueue.push(ActionPtr);
                    break;
                case NO_ACTION:
                    // 2nd Action Attack vs 2nd Action None
                    pairQueue.push(pair<Player*, int>(&this->m_otherPlayer, 1));
                    ActionPtr = TakeDmg;
                    actionQueue.push(ActionPtr);
                    break;
                default:
                    break;
            } //eo inner switch
            break;
        case DEFEND_ACTION:
            switch (t_actionList[actionIdx].second)
            {
                case ATTACK_ACTION:
                    // Block vs Attack - Do nothing
                    break;
                case DEFEND_ACTION:
                    // Block vs Block - Do nothing
                    break;
                case HEAL_ACTION:
                    // Block vs Super Heal
                    if ((otherCard.getID().compare(to_string(ADV_SUPER_HEAL_ID)) == 0))
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_otherPlayer, 2));
                    }
                    // Block vs Life Boost
                    else if ((otherCard.getID().compare(to_string(ADV_LIFE_BOOST_ID)) == 0))
                    {
                        // First action
                        if (actionIdx == 0)
                        {
                            pairQueue.push(pair<Player*, int>(&this->m_otherPlayer, 1));
                            ActionPtr = IncreaseMaxHP;
                            actionQueue.push(ActionPtr);
                        }
                        // Second action
                        else
                        {
                            pairQueue.push(pair<Player*, int>(&this->m_otherPlayer, 1));
                            ActionPtr = Heal;
                            actionQueue.push(ActionPtr);
                        }
                    }
                    // Block vs Heal
                    else
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_otherPlayer, 1));
                        ActionPtr = Heal;
                        actionQueue.push(ActionPtr);
                    }
                    break;
                case NO_ACTION:
                    // 2nd Action Block vs 2nd Action None - Do nothing
                    break;
                default:
                    break;
            } //eo inner switch
            break;
        case HEAL_ACTION:
            switch (t_actionList[actionIdx].second)
            {
                case ATTACK_ACTION:
                    // Heal vs Mighty Swing
                    if ((otherCard.getID().compare(to_string(ADV_MIGHTY_SWING_ID)) == 0))
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_player, 3));
                    }
                    // Heal vs Attack
                    else
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_player, 1));
                    }
                    ActionPtr = TakeDmg;
                    actionQueue.push(ActionPtr);
                    break;
                case DEFEND_ACTION:
                    // Super Heal vs Block
                    if ((playerCard.getID().compare(to_string(ADV_SUPER_HEAL_ID)) == 0))
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_player, 2));
                    }
                    // Life Boost vs Block
                    else if ((playerCard.getID().compare(to_string(ADV_LIFE_BOOST_ID)) == 0))
                    {
                        // First action
                        if (actionIdx == 0)
                        {
                            pairQueue.push(pair<Player*, int>(&this->m_player, 1));
                            ActionPtr = IncreaseMaxHP;
                            actionQueue.push(ActionPtr);
                        }
                        // Second action
                        else
                        {
                            pairQueue.push(pair<Player*, int>(&this->m_player, 1));
                            ActionPtr = Heal;
                            actionQueue.push(ActionPtr);
                        }
                    }
                    // Heal vs Block
                    else
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_player, 1));
                        ActionPtr = Heal;
                        actionQueue.push(ActionPtr);
                    }
                    break;
                case HEAL_ACTION:
                    // Super Heal -  Player
                    if ((playerCard.getID().compare(to_string(ADV_SUPER_HEAL_ID)) == 0))
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_player, 2));
                        ActionPtr = Heal;
                        actionQueue.push(ActionPtr);
                    }
                    // Life Boost -  Player
                    else if ((playerCard.getID().compare(to_string(ADV_LIFE_BOOST_ID)) == 0))
                    {
                        // First action
                        if (actionIdx == 0)
                        {
                            pairQueue.push(pair<Player*, int>(&this->m_player, 1));
                            ActionPtr = IncreaseMaxHP;
                            actionQueue.push(ActionPtr);
                        }
                        // Second action
                        else
                        {
                            pairQueue.push(pair<Player*, int>(&this->m_player, 1));
                            ActionPtr = Heal;
                            actionQueue.push(ActionPtr);
                        }
                    }
                    // Heal -  Player
                    else
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_player, 1));
                        ActionPtr = Heal;
                        actionQueue.push(ActionPtr);
                    }
                    // Super Heal -  Other Player
                    if ((otherCard.getID().compare(to_string(ADV_SUPER_HEAL_ID)) == 0))
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_otherPlayer, 2));
                        ActionPtr = Heal;
                        actionQueue.push(ActionPtr);
                    }
                    // Life Boost -  Other Player
                    else if ((otherCard.getID().compare(to_string(ADV_LIFE_BOOST_ID)) == 0))
                    {
                        // First action
                        if (actionIdx == 0)
                        {
                            pairQueue.push(pair<Player*, int>(&this->m_otherPlayer, 1));
                            ActionPtr = IncreaseMaxHP;
                            actionQueue.push(ActionPtr);
                        }
                        // Second action
                        else
                        {
                            pairQueue.push(pair<Player*, int>(&this->m_otherPlayer, 1));
                            ActionPtr = Heal;
                            actionQueue.push(ActionPtr);
                        }
                    }
                    // Heal -  Other Player
                    else
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_otherPlayer, 1));
                        ActionPtr = Heal;
                        actionQueue.push(ActionPtr);
                    }
                    break;
                case NO_ACTION:
                    // Heal vs 2nd Action
                    if ((playerCard.getID().compare(to_string(ADV_LIFE_BOOST_ID)) == 0))
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_player, 1));
                        ActionPtr = Heal;
                        actionQueue.push(ActionPtr);
                    }
                    break;
                default:
                    // Do nothing
                    break;
            } //eo inner switch
            break;
        case EQUIP_ACTION:
            break;
        case HERO_TYPE:
            break;
        case NO_ACTION:
             switch (t_actionList[actionIdx].second)
            {
                case ATTACK_ACTION:
                    // 2nd Action None vs Attack
                    pairQueue.push(pair<Player*, int>(&this->m_player, 1));
                    ActionPtr = TakeDmg;
                    actionQueue.push(ActionPtr);
                    break;
                case DEFEND_ACTION:
                    // 2nd Action None vs Block
                    break;
                case HEAL_ACTION:
                    // 2nd Action None vs Heal

                    // 2nd Action heal should only be Life Boost
                    if ((otherCard.getID().compare(to_string(ADV_LIFE_BOOST_ID)) == 0))
                    {
                        pairQueue.push(pair<Player*, int>(&this->m_otherPlayer, 1));
                        ActionPtr = TakeDmg;
                        actionQueue.push(ActionPtr);
                    }
                    break;
                default:
                    // Do nothing
                    break;
            }//eo inner switch
            break;
        default:
            break;
        } //eos

    }//eof 
    
    // loop through action queue and exec actions
    while (actionQueue.empty() == false)
    {
        // Get Player info for action
        pair<Player*, int> info = pairQueue.front();
        // Get action pointer and exec action
        ActionPtr = actionQueue.front();
        ActionPtr(info.first, info.second);
        // Pop action off from queue
        pairQueue.pop();
        actionQueue.pop();
    } //eow
}//eo procBattle

void BattleMonitor::displayBattleScreen(string t_playerCardsPlayed[5], string  t_otherCardsPlayed[5])
{
    //clear console screen
    system("cls");

    cout << "Profile: " << this->m_player.getPlayerName() << endl;
    cout << "   Deck: " << this->m_player.getDeck()->getDeckName() << endl;
    cout << endl;
    cout << "========================================" << endl;
    cout << "You - " << this->m_player.getHP() << " HP           | Bot - " << this->m_otherPlayer.getHP() << "HP" << endl;
    cout << "1. " << fmtBattleRoundStr(t_playerCardsPlayed[0], t_otherCardsPlayed[0]) << endl;
    cout << "2. " << fmtBattleRoundStr(t_playerCardsPlayed[1], t_otherCardsPlayed[1]) << endl;
    cout << "3. " << fmtBattleRoundStr(t_playerCardsPlayed[2], t_otherCardsPlayed[2]) << endl;
    cout << "4. " << fmtBattleRoundStr(t_playerCardsPlayed[3], t_otherCardsPlayed[3]) << endl;
    cout << "5. " << fmtBattleRoundStr(t_playerCardsPlayed[4], t_otherCardsPlayed[4]) << endl;
    cout << endl;
    cout << "Your Cards:" << endl;
    this->m_player.displayHand();
}//eo displayBattleScreen

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
    int remainingPhases = (DEFAULT_MAX_PHASE-this->m_currPhaseNumber)+1;
    bool mustPlayCore = (m_CCRemainingOther == remainingPhases);
    bool findNewCard = true;

    while (findNewCard)
    {
        t_handIdx = rand() % int(this->m_otherPlayer.getHand().size());
        retCard = this->m_otherPlayer.getHand().at(t_handIdx);

        if(mustPlayCore && retCard.isCore())
        {
            findNewCard = false;
            m_otherPlayer.playCard(t_handIdx);
        }
        else if(mustPlayCore == false)
        {
            findNewCard = false;
            m_otherPlayer.playCard(t_handIdx);
        }
        
    } //eow
    return retCard;
} //eo getOtherPlayerCard

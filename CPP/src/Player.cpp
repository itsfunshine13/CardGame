#include "../include/Player.h"
#include "../include/cardTypes.h"
#include "../include/commonTypes.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <unistd.h>

using namespace std;

extern map<int, Card> masterCardList;

Player::Player()
{
    this->m_playerName   = "Not Set";
    this->m_healthPoints = DEFAULT_HP;
    this->m_maxHP        = DEFAULT_MAX_HP;
}

Player::Player(string m_playerName, Deck m_playerDeck, int m_healthPoints)
{
    this->m_playerName   = m_playerName;
    this->m_playerDeck   = m_playerDeck;
    this->m_healthPoints = m_healthPoints;
    this->m_maxHP        = DEFAULT_MAX_HP;
}

Player::~Player()
{

}

Deck* Player::getDeck()
{
    return &(this->m_playerDeck);
} //eo getDeck

int Player::getHP()
{
    return this->m_healthPoints;
} //eo getHP

void Player::resetHP()
{
    this->m_healthPoints = DEFAULT_HP;
    this->m_maxHP        = DEFAULT_MAX_HP;
} //eo resetHP

void Player::increaseMaxHP(int amt)
{
    this->m_maxHP += amt;
} //eo increaseMaxHP

void Player::initHand()
{
    this->m_hand.push_back(masterCardList.at(CORE_ATTACK_ID));
    this->m_hand.push_back(masterCardList.at(CORE_BLOCK_ID));
    this->m_hand.push_back(masterCardList.at(CORE_HEAL_ID));
} // eo initHand

void Player::fillHand()
{
    while(this->m_hand.size() < DEFAULT_HAND_SIZE)
    {
        this->m_hand.push_back(this->m_playerDeck.drawCard());
    } //eow

    // Sort to be more readable
    sort( this->m_hand.begin(), this->m_hand.end());
} //eo fillHand

void Player::displayHand()
{
    for (uint8_t i = 0; i < this->m_hand.size(); i++)
    {
        cout << (i+1) << ". " << this->m_hand.at(i).getCardName() << endl;
    } //eof
} //eo displayHand

vector<Card> Player::getHand()
{
    return this->m_hand;
} //eo getHand

Card Player::playCard(int t_cardIdx)
{
    Card retCard = this->m_hand.at(t_cardIdx);
    this->m_hand.erase(this->m_hand.begin()+t_cardIdx);
    return retCard;
} //eo playCard
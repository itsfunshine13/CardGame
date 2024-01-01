#include "../include/Player.h"
#include "../include/cardTypes.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

extern map<int, Card> masterCardList;

Player::Player()
{
    this->m_playerName = "Not Set";
    this->m_healthPoints = 5;
}

Player::Player(string m_playerName, Deck m_playerDeck, uint8_t m_healthPoints)
{
    this->m_playerName   = m_playerName;
    this->m_playerDeck   = m_playerDeck;
    this->m_healthPoints = m_healthPoints;
}

Player::~Player()
{

}

uint8_t Player::getHP()
{
    return this->m_healthPoints;
} //eo getHP

Deck* Player::getDeck()
{
    return &(this->m_playerDeck);
}

void Player::initHand()
{
    this->m_hand.push_back(masterCardList.at(CORE_ATTACK_ID));
    this->m_hand.push_back(masterCardList.at(CORE_BLOCK_ID));
    this->m_hand.push_back(masterCardList.at(CORE_HEAL_ID));
} // eo initHand

void Player::fillHand()
{

} //eo fillHand

void Player::displayHand()
{

} //eo displayHand
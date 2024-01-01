#ifndef PLAYER_H
#define PLAYER_H

#include "Deck.h"
#include "Card.h"

#include <iostream>
#include <string>

using namespace std;

class Player
{
private:
    uint8_t m_healthPoints;
    string  m_playerName;
    Deck    m_playerDeck;

    vector<Card> m_hand;

public:
    Player(string m_playerName, Deck m_playerDeck, uint8_t m_healthPoints);
    Player();
    ~Player();

    uint8_t getHP();
    Deck* getDeck();

    void initHand();
    void fillHand();
    void displayHand();
};


#endif
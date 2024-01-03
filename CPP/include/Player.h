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
    int m_healthPoints;
    int m_maxHP;
    string  m_playerName;
    Deck    m_playerDeck;

    vector<Card> m_hand;

public:
    Player(string m_playerName, Deck m_playerDeck, int m_healthPoints);
    Player();
    ~Player();

    Deck* getDeck();
    int  getHP();
    void resetHP();
    void increaseMaxHP(int amt);

    void initHand();
    void fillHand();
    void displayHand();
    vector<Card> getHand();
    Card playCard(int t_cardIdx);
};


#endif
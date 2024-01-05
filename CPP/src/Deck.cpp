#include "../include/Deck.h"
#include "../include/Card.h"
#include "../include/commonTypes.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include <vector>

using namespace std;

Deck::Deck()
{ 
    this->deckName = "NO_NAME_SET";
    this->deckSizeLimit = 0; 
}

Deck::Deck(string deckName, uint8_t deckSizeLimit)
{
    this->deckName = deckName;
    this->deckSizeLimit = deckSizeLimit;
}

Deck::~Deck(){}

void Deck::setDeckName(string deckName)
{
    this->deckName = deckName;
}

void Deck::setDeckSizeLimit(uint8_t deckSizeLimit)
{
    this->deckSizeLimit = deckSizeLimit;
}

void Deck::overWriteOriginalDeck(vector<Card> newDeck)
{
    this->originalDeck = newDeck;
}

void Deck::addToOringalDeck(Card card)
{
    this->originalDeck.push_back(card);
    sortDeck();
}

int Deck::removeCard(string cardID)
{
    int retVal = RETVAL_ERROR;
    for (uint8_t i = 0; i < originalDeck.size(); i++)
    {
        if (this->originalDeck[i].getID().compare(cardID) == 0)
        {
            this->originalDeck.erase(this->originalDeck.begin()+i);
            return RETVAL_OK;
        }
    }
    return retVal;
}

void Deck::clearOriginalDeck()
{
    this->originalDeck.clear();
    this->playDeck.clear();
}

void Deck::rebuildPlayDeck()
{
    this->playDeck = this->originalDeck;
}

void Deck::shufflePlayDeck()
{
    Card temp;
    int tempIdx;

    // swap each card in deck
    for (int i = 0; i < int(this->playDeck.size()); i++)
    {
        tempIdx = rand() % int(this->playDeck.size());
        temp = this->playDeck[i];
        this->playDeck[i] = this->playDeck[tempIdx];
        this->playDeck[tempIdx] = temp;
    }//eof
    
}

void Deck::sortDeck()
{
    sort( this->originalDeck.begin(), this->originalDeck.end());
}

void Deck::displayDeck(uint8_t choice)
{
    vector<Card> deck;

    if (choice == 0 ) 
    { 
        deck = this->originalDeck;
    }
    else if (choice == 1)
    {
        deck = this->playDeck;
    }
    else
    {
        cout << "Invalid Deck Choice to Display Deck" << endl;
        return;
    }

    for (uint8_t i = 0; i < deck.size(); i++)
    {
        cout << (i+1) << ". " + deck.at(i).getCardName() << endl;
    }
}

Card Deck::drawCard()
{
    // Add discard pile back to deck and shuffle if no cards to draw
    if (this->playDeck.size() == 0)
    {
        discardPileToDeck();
        shufflePlayDeck();
    }
    Card card = this->playDeck.back();
    this->playDeck.pop_back();
    this->discardPile.push_back(card);
    return card;
}

vector<Card> Deck::getPlayDeck()
{
    return this->playDeck;
}

vector<Card> Deck::getOriginalDeck()
{
    return this->originalDeck;
}

int Deck::getOriginalDeckSize()
{
    return this->originalDeck.size();
}

int Deck::getRemainingCardsSize()
{
    return this->playDeck.size();
}

int Deck::getDeckSizeLimit()
{
    return this->deckSizeLimit;
}

string Deck::getDeckName()
{
    return this->deckName;
}

void Deck::sendToDiscardPile(Card card)
{
    this->discardPile.push_back(card);
}

void Deck::discardPileToDeck()
{
    for (uint8_t i = this->discardPile.size()-1; i >= 0 ; i--)
    {
        this->playDeck.push_back(this->discardPile[i]);
        this->discardPile.pop_back();
    }//eof
    
}
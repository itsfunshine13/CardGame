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

void Deck::addToOringalDeck(Card card)
{
    this->originalDeck.push_back(card);
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
}

void Deck::rebuildPlayDeck()
{
    this->playDeck = this->originalDeck;
}

void Deck::shufflePlayDeck()
{
    srand(time(NULL));

    auto rng = std::default_random_engine {};
    std::shuffle(begin(this->playDeck), end(this->playDeck), rng);
}

void Deck::sortDeck()
{
    cout << "TODO" << endl;
}

void Deck::displayDeck(uint8_t choice)
{
    vector<Card> *deck;

    if (choice == 0 ) 
    { 
        deck = &(this->originalDeck);
    }
    else if (choice == 1)
    {
        deck = &(this->playDeck);
    }
    else
    {
        cout << "Invalid Deck Choice to Display Deck" << endl;
        return;
    }

    for (uint8_t i = 1; i < deck->size()+1; i++)
    {
        cout << i + ". " + deck->at(i-1).getCardName() << endl;
    }
    
}

void Deck::drawCard(Card *card)
{
    card = &(this->playDeck.back());
    this->playDeck.pop_back();
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
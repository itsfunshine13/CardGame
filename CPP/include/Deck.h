#ifndef DECK_H_
#define DECK_H_

#include "Card.h"
#include <string>
#include <vector>

using namespace std;

class Deck
{
private:
    vector<Card> playDeck;
    vector<Card> originalDeck;
    uint8_t deckSizeLimit;

public:
    Deck();
    Deck(uint8_t deckSizeLimit);
    ~Deck();

    void addToOringalDeck(Card card);
    int  removeCard(string cardID);
    void clearOriginalDeck();
    void rebuildPlayDeck();
    void shufflePlayDeck();
    void sortDeck();

    void displayDeck(uint8_t choice);

    void drawCard(Card *card);

    vector<Card> getPlayDeck();
    vector<Card> getOriginalDeck();
    int getOriginalDeckSize();
    int getRemainingCardsSize();
    int getDeckSizeLimit();

};


#endif
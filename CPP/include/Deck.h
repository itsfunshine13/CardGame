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
    vector<Card> discardPile;
    
    uint8_t deckSizeLimit;
    string  deckName;
    int     wins;
    int     losses;

public:
    Deck();
    Deck(string deckName, uint8_t deckSizeLimit);
    ~Deck();

    void setDeckName(string deckName);
    void setDeckSizeLimit(uint8_t deckSizeLimit);
    void overWriteOriginalDeck(vector<Card> newDeck);

    void addToOringalDeck(Card card);
    int  removeCard(string cardID);
    void clearOriginalDeck();
    void rebuildPlayDeck();
    void shufflePlayDeck();
    void sortDeck();
    
    // 0 = original deck | 1 = playdeck
    void displayDeck(uint8_t choice);
    Card drawCard();

    vector<Card> getPlayDeck();
    vector<Card> getOriginalDeck();
    int getOriginalDeckSize();
    int getRemainingCardsSize();
    int getDeckSizeLimit();
    string getDeckName();
    void sendToDiscardPile(Card card);
    void discardPileToDeck();

    int  getWins();
    int  getLosses();
    void incrWins();
    void incrLosses();

};


#endif
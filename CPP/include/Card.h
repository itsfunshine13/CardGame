#ifndef CARD_H_
#define CARD_H_

#include "CardTypes.h"

#include <string>
#include <vector>
#include <stdlib.h>
#include <stdint.h>

using namespace std;

class Card{

private:
  string cardName;
  string cardDescription;
  string cardID;

  bool cardReleased;
  int deckLimit;

  Rarity    cardRarity;
  CardType  cardType;
  CardClass cardClass;
  CardClass cardSubclass;
  Action    firstAction;
  Action    secondAction;

public:
  Card(
    string cardName,
    string cardDescription,
    string cardID,
    string cardReleased,
    string deckLimit,
    string cardRarity,
    string cardType,
    string cardClass,
    string cardSubclass,
    string firstAction,
    string secondAction);
  Card();
  ~Card();
  string    getCardName();
  string    getID();
  bool      isReleased();
  bool      isCore();
  Rarity    getRarity();
  CardType  getCardType();
  CardClass getCardClass();
  int       getDeckLimit();
  Action    getFirstAction();
  Action    getSecondAction();
  string    getCardDescription();
  void      printCard();

};

#endif

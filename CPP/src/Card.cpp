#include "../include/Card.h"
#include "../include/cardTypes.h"
#include "../include/cardUtils.h"

#include <iostream>
#include <string>

using namespace std;


bool Card::operator< (const Card &other) const 
{
    return stoi(this->cardID) < stoi(other.cardID);
}

Card::Card(
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
  string secondAction)
{
  this->cardName        = cardName;
  this->cardDescription = cardDescription;
  this->cardID          = cardID;
  this->cardReleased    = (cardReleased.compare("RELEASED") == 0);
  this->deckLimit       = stoi(deckLimit);
  this->cardRarity      = stringToEnumRarity(cardRarity);
  this->cardType        = stringToEnumCardType(cardType);
  this->cardClass       = stringToEnumCardClass(cardClass);
  this->cardSubclass    = stringToEnumCardClass(cardSubclass);
  this->firstAction     = stringToEnumAction(firstAction);
  this->secondAction    = stringToEnumAction(secondAction);

}//eo constructor

Card::Card()
{
  this->cardName        = "Blank";
  this->cardDescription = "Blank Card";
  this->cardID          = "00000";
  this->cardReleased    = false;
  this->deckLimit       = 0;
  this->cardRarity      = RARITY_UNKNOWN;
  this->cardType        = NO_TYPE;
  this->cardClass       = NO_CLASS;
  this->cardSubclass    = NO_CLASS;
  this->firstAction     = NO_ACTION;
  this->secondAction    = NO_ACTION;
}

Card::~Card(){}

string Card::getCardName()
{
  return this->cardName;
}

string Card::getID()
{
  return this->cardID;
}

bool Card::isReleased()
{
  return this->cardReleased;
}

bool Card::isCore()
{
  return (this->cardRarity == RARITY_CORE);
}

Rarity Card::getRarity()
{
  return this->cardRarity;
}

CardType Card::getCardType()
{
  return this->cardType;
}

CardClass Card::getCardClass()
{
  return this->cardClass;
}

int Card::getDeckLimit()
{
  return this->deckLimit;
}

Action Card::getFirstAction()
{
  return this->firstAction;
}
Action Card::getSecondAction()
{
  return this->secondAction;
}

string Card::getCardDescription()
{
  return this->cardDescription;
}

// TODO: Finish function
void Card::printCard()
{
  cout << "ID:   " << this->getID() << endl;
  cout << "Name: " << this->getCardName() << endl;
  cout << "Description: " << this->getCardDescription() << endl;
  cout << "Released: " << this->isReleased() << endl;

}

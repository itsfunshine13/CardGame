#include "cardTypes.h"

#include <iostream>
#include <string>

using namespace std;

// TODO: Add enumToString functions for printCard()

Action stringToEnumAction(string action)
{
  Action retVal;

  if (action.compare("Attack") == 0)
  {
    retVal = ATTACK_ACTION;
  }
  else if (action.compare("Block") == 0)
  {
    retVal = DEFEND_ACTION;
  }
  else if (action.compare("Equip") == 0)
  {
    retVal = EQUIP_ACTION;
  }
  else if (action.compare("Heal") == 0)
  {
    retVal = HEAL_ACTION;
  }
  else if (action.compare("Hero") == 0)
  {
    retVal = HERO_ACTION;
  }
  else if (action.compare("Interrupt") == 0)
  {
    retVal = INTERRUPT_ACTION;
  }
  else if (action.compare("Special") == 0)
  {
    retVal = SPECIAL_ACTION;
  }
  else
  {
    retVal = NO_ACTION;
  }
  return retVal;
}

Rarity stringToEnumRarity(string rarity)
{
  Rarity retVal;

  if (rarity.compare("CORE") == 0)
  {
    retVal = RARITY_CORE;
  }
  else if (rarity.compare("BASIC") == 0)
  {
    retVal = RARITY_BASIC;
  }
  else if (rarity.compare("HIGHGRADE") == 0)
  {
    retVal = RARITY_HIGHGRADE;
  }
  else if (rarity.compare("UNIQUE") == 0)
  {
    retVal = RARITY_UNIQUE;
  }
  else if (rarity.compare("HERO") == 0)
  {
    retVal = RARITY_HERO;
  }
  else
  {
    retVal = RARITY_UNKNOWN;
  }
  return retVal;
}

CardType stringToEnumCardType(string cardType)
{
  CardType retVal;

  if (cardType.compare("ATTACK") == 0)
  {
    retVal = ATTACK_TYPE;
  }
  else if (cardType.compare("BLOCK") == 0)
  {
    retVal = BLOCK_TYPE;
  }
  else if (cardType.compare("HEAL") == 0)
  {
    retVal = HEAL_TYPE;
  }
  else if (cardType.compare("GEAR") == 0)
  {
    retVal = GEAR_TYPE;
  }
  else if (cardType.compare("HERO") == 0)
  {
    retVal = HERO_TYPE;
  }
  else
  {
    retVal = NO_TYPE;
  }
  return retVal;
}

CardClass stringToEnumCardClass(string cardClass)
{
  CardClass retVal;

  if (cardClass.compare("BERSERKER") == 0)
  {
    retVal = BERSERKER;
  }
  else if (cardClass.compare("NECROMANCER") == 0)
  {
    retVal = NECROMANCER;
  }
  else if (cardClass.compare("PALADIN") == 0)
  {
    retVal = PALADIN;
  }
  else if (cardClass.compare("SPECIAL") == 0)
  {
    retVal = SPECIAL;
  }
  else if (cardClass.compare("INTERRUPT") == 0)
  {
    retVal = INTERRUPT;
  }
  else
  {
    retVal = NO_CLASS;
  }
  return retVal;
}

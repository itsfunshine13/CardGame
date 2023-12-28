#ifndef CARDTYPES_H_
#define CARDTYPES_H_

enum Action
{
  ATTACK_ACTION,
  DEFEND_ACTION,
  EQUIP_ACTION,
  HEAL_ACTION,
  HERO_ACTION,
  INTERRUPT_ACTION,
  SPECIAL_ACTION,
  NO_ACTION
};

enum Rarity
{
  RARITY_CORE,
  RARITY_BASIC,
  RARITY_HIGHGRADE,
  RARITY_UNIQUE,
  RARITY_HERO,
  RARITY_UNKNOWN
};

enum CardType
{
  ATTACK_TYPE,
  BLOCK_TYPE,
  HEAL_TYPE,
  GEAR_TYPE,
  HERO_TYPE,
  NO_TYPE
};

enum CardClass
{
  BERSERKER,
  NECROMANCER,
  PALADIN,
  SPECIAL,
  INTERRUPT,
  NO_CLASS
};

#endif
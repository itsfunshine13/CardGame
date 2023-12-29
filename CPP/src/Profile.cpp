#include "../include/Profile.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

Profile::Profile()
{
    this->profileName = "NOT SET";
}

Profile::Profile(string profileName)
{
    this->profileName = profileName;
}

Profile::~Profile(){}

void Profile::setProfileName(string profileName)
{
    this->profileName = profileName;
}

void Profile::addDeck(Deck deck)
{
    this->decks.push_back(deck);
}

string Profile::getProfileName()
{
    return this->profileName;
}

vector<Deck> Profile::getAllDecks()
{
    return this->decks;
}

void Profile::displayAllDeckNames()
{
    for (uint8_t i = 1; i < this->decks.size()+1; i++)
    {
        cout << i << ". " << this->decks.at(i-1).getDeckName() << endl;
    }
    
}
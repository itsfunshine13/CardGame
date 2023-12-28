#include "../include/Profile.h"

#include <string>
#include <vector>

using namespace std;

Profile::Profile()
{
    this->profileName = "NOT SET";
}

Profile::~Profile(){}

string Profile::getProfileName()
{
    return this->profileName;
}

vector<Deck> Profile::getDecks()
{
    return this->decks;
}

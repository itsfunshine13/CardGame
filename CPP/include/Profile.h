#ifndef PROFILE_H_
#define PROFILE_H_

#include "Card.h"
#include "Deck.h"
#include <string>
#include <vector>

using namespace std;

class Profile
{
private:
    string profileName;
    vector<Deck> decks;

public:
    Profile();
    ~Profile();
    string getProfileName();
    vector<Deck> getDecks();
};

#endif

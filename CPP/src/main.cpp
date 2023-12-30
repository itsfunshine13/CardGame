#include "../include/fileUtils.h"
#include "../include/GameMonitor.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(){

  string tempFileString = "";
  map<int, Card> masterCardList;

  cout << "TEST START" << endl;
  loadCardData(tempFileString, &masterCardList, true);

  // for (int i = 1001; i < 1007; i++)
  // {
  //   cout << "card[1]: ";
  //   masterCardList.find(i)->second.printCard();
  //   cout << endl << endl;
  // }

  map<string, Profile> profileDB;
  loadProfileData(tempFileString, &profileDB, &masterCardList, true);

  Profile tmpProfile = profileDB.at("Funshine");
  vector<Deck> tmpDeckList = tmpProfile.getAllDecks();

  // for (uint8_t i; i < tmpDeckList.size(); i++)
  // {
  //   cout << "Deck: " << tmpDeckList.at(i).getDeckName() << endl;

  //   vector<Card> tmpCardList = tmpDeckList.at(i).getOriginalDeck();
  //   for (uint8_t j = 0; j < tmpCardList.size(); j++)
  //   {
  //     cout << "\t" << (j+1) << "." << tmpCardList.at(j).getCardName();
  //     cout << endl << endl;
  //   }
    
  // }

  GameMonitor gm(&masterCardList, &profileDB);
  gm.mainMenu();

  cout << "TEST END" << endl;

  return 0;
}


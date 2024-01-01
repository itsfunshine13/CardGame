#include "../include/fileUtils.h"
#include "../include/GameMonitor.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

map<int, Card> masterCardList;
map<string, Profile> profileDB;

int main(){

  string tempFileString = "";
  
  cout << "TEST START" << endl;

  // Load Data
  loadCardData(tempFileString, &masterCardList, true);
  loadProfileData(tempFileString, &profileDB, &masterCardList, true);

  // Profile tmpProfile = profileDB.at("Funshine");
  // vector<Deck> tmpDeckList = tmpProfile.getAllDecks();

  GameMonitor gm(&masterCardList, &profileDB);
  gm.mainMenu();

  cout << "TEST END" << endl;

  return 0;
}


#include "../include/fileUtils.h"
#include "../include/GameMonitor.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

map<int, Card> masterCardList;
map<string, Profile> profileDB;

int main(){

  srand(time(NULL));
  
  string tempFileString = "";
  

  cout << "TEST START" << endl;

  loadCardData(tempFileString, true);
  loadProfileData(tempFileString, true);

  // Profile tmpProfile = profileDB.at("Funshine");
  // vector<Deck> tmpDeckList = tmpProfile.getAllDecks();

  GameMonitor gm;
  gm.mainMenu();

  // cout << "core attack 1st action: " << masterCardList.at(CORE_ATTACK_ID).getFirstAction() << endl;
  // cout << "core attack 2nd action: " << masterCardList.at(CORE_ATTACK_ID).getSecondAction() << endl;

  cout << "TEST END" << endl;

  return 0;
}


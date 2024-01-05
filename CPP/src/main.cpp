#include "../include/fileUtils.h"
#include "../include/GameMonitor.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

extern VersionData cardlistVersion;

map<int, Card> masterCardList;
map<string, Profile> profileDB;

int main(){

  srand(time(NULL));
  
  string tempFileString = "";

  loadCardData(tempFileString, true);
  loadProfileData(tempFileString, true);

  masterCardList.at(ADV_MIGHTY_SWING_ID).printCard();

  GameMonitor gm;
  gm.mainMenu();

  return 0;
}


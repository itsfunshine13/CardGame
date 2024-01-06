#include "../include/fileUtils.h"
#include "../include/GameMonitor.h"

//DEBUG
#include "../include/Profile.h"

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

  loadCardData(DEFAULT_CARD_LIST_FILE, false);
  loadProfileData(PROFILES_SAVE_FILE, false);

  GameMonitor gm;
  gm.mainMenu();

  return 0;
}


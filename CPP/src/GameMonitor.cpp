#include "../include/GameMonitor.h"
#include "../include/Card.h"
#include "../include/Profile.h"
#include "../include/cardTypes.h"

#include <iostream>
#include <map>
#include <unistd.h>
#include <string>
#include <stdlib.h> 

using namespace std;


static char t_inputChar;
static string t_inputStr;

GameMonitor::GameMonitor(map<int, Card> *masterCardList, map<string, Profile> *profileDB)
{
    this->ptr_masterCardList = masterCardList;
    this->ptr_profileDB      = profileDB;
}

GameMonitor::~GameMonitor()
{
    delete this->ptr_masterCardList;
    delete this->ptr_profileDB;
}

// Helper functions
void GameMonitor::displayCardSet(Rarity rType)
{
    //clear console screen
    system("cls"); 
    map<int, Card>::iterator it;
    for (it = this->ptr_masterCardList->begin(); it != this->ptr_masterCardList->end(); it++)
    {
        if (it->second.getRarity() == rType)
        {
            cout << it->second.getCardName() << endl;
            cout << it->second.getCardDescription() << endl;
            cout << endl << endl;
        }
    } //eof
    cout << "Enter any key to go back" << endl;
    cin >> t_inputStr;
    cardInformationMenu();
}

void GameMonitor::mainMenu()
{
    //clear console screen
    system("cls"); 

    cout << "Main Menu" << endl;
    cout << "\t Profile Loaded: " << this->m_currProfile.getProfileName() << endl;
    cout << endl;
    cout << "1. Play Game" << endl;
    cout << "2. Load Profile" << endl;
    cout << "3. Card Information" << endl;
    cout << "4. Game Rules" << endl;
    cout << "5. Save All (Profiles and Decks)" << endl;
    cout << "6. Exit Game" << endl;
    cout << "Choice: ";
    cin >> t_inputChar;

    switch (t_inputChar)
    {
    case '1':
        cout << "going to playGameMenu" << endl;
        playGameMenu();
        break;
    case '2':
        cout << "going to loadProfileMenu" << endl;
        loadProfileMenu();
        break;
    case '3':
        cout << "going to cardInformationMenu" << endl;
        cardInformationMenu();
        break;
    case '4':
        cout << "going to gameRulesMenu" << endl;
        gameRulesMenu();
        break;
    case '5':
        cout << endl;
        cout << "NOT IMPLEMENTED" << endl;
        sleep(2); //sleep for 2s
        mainMenu();
        break;
    case '6':
        cout << "Exiting" << endl;
        sleep(1); //sleep for 2s
        return;
        break;
    default:
        cout << endl;
        cout << "Invalid Input" << endl;
        sleep(2); //sleep for 2s
        mainMenu();
        break;
    } //eos
}

void GameMonitor::playGameMenu() {}
void GameMonitor::loadProfileMenu() {}

void GameMonitor::cardInformationMenu()
{
    //clear console screen
    system("cls"); 

    cout << "Card Information" << endl << endl;

    cout << "Core Cards" << endl;
    cout << "\tAlways start your turn with all 3 Core cards" << endl << endl;

    cout << "Basic Cards" << endl;
    cout << "\tSingle action cards. Can only be Attack, Block, Heal." << endl;
    cout << "\tYou have 10 of these in a deck and at most 5 of one kind." << endl << endl;


    cout << "Advanced Cards" << endl;
    cout << "\tStronger versions of the Basic cards. They have at most 2 actions." << endl;
    cout << "\tYou have 10 of these in a deck and at most 2 of any kind." << endl << endl;

    cout << "1. Display Core Cards" << endl;
    cout << "2. Display Basic Cards" << endl;
    cout << "3. Display Advanced cards" << endl;
    cout << "4. Back" << endl;
    cout << "Choice: ";
    cin >> t_inputChar;

    cout << "input: " << t_inputChar << endl;
    switch (t_inputChar)
    {
    case '1': 
        displayCardSet(RARITY_CORE);
        break;
    case '2': 
        displayCardSet(RARITY_BASIC);
        break;
    case '3': 
        displayCardSet(RARITY_HIGHGRADE);
        break;
    case '4': 
        mainMenu();
        break;   
    default:
        cout << endl;
        cout << "Invalid Input" << endl;
        sleep(2); //sleep for 2s
        cardInformationMenu();
        break;
    } //eos
}

void GameMonitor::gameRulesMenu() {}


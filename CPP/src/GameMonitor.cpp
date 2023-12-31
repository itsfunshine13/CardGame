#include "../include/GameMonitor.h"
#include "../include/Card.h"
#include "../include/Profile.h"
#include "../include/cardTypes.h"
#include "../include/commonTypes.h"

#include <iostream>
#include <map>
#include <unistd.h>
#include <string>
#include <stdlib.h> 

using namespace std;


static char   t_inputChar;
static string t_inputStr;
static string t_loadedProfileName;
static string t_loadedDeckName;

GameMonitor::GameMonitor(map<int, Card> *masterCardList, map<string, Profile> *profileDB)
{
    this->ptr_masterCardList = masterCardList;
    this->ptr_profileDB      = profileDB;
    this->m_profileSet       = false;
    this->m_deckSet          = false;

    t_loadedProfileName = "NONE PICKED";
    t_loadedDeckName    = "NONE PICKED";
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
} //eo displayCardSet

void GameMonitor::displayDeckCreation(vector<Card> cards)
{
    vector<string> t_basicCards;
    vector<string> t_advCards;

    int t_num;
    string t_cardListHeader = "Basic ====== Adv";
    string t_basicString;

    // Build temp vectors
    for (uint8_t i = 0; i < cards.size(); i++)
    {
        t_num = stoi(cards.at(i).getID());
        if (t_num >= BASIC_CARD_ID_START && t_num <= BASIC_CARD_ID_END)
        {
            t_basicCards.push_back(cards.at(i).getCardName());
        }
        else if (t_num >= ADV_CARD_ID_START && t_num <= ADV_CARD_ID_END)
        {
            t_advCards.push_back(cards.at(i).getCardName());
        }
    } //eof
    
    // hacky way to avoid out of bounds error in printing the cards
    while (t_basicCards.size() < 10) { t_basicCards.push_back(""); }
    while (t_advCards.size() < 10)   { t_advCards.push_back(""); }

    cout << t_cardListHeader << endl;
    // 10 is both basic card and adv card limit
    for (uint8_t i = 0; i < 10; i++)
    {
        t_basicString = (i+1) + ". " + t_basicCards.at(i);
        // string padding
        while (t_basicString.length() < 13) { t_basicString += " "; }

        cout << t_basicString << (i+1) << ". " << t_advCards.at(i);
    }//eof
    
} //eo displayDeckCreation

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
    cout << "4. How to Play" << endl;
    cout << "5. Save All (Profiles and Decks)" << endl;
    cout << "6. Exit Game" << endl;
    cout << "Choice: ";
    cin >> t_inputChar;

    switch (t_inputChar)
    {
    // Play Game
    case '1':
        cout << "going to playGameMenu" << endl;
        playGameMenu();
        break;
    // Load profile
    case '2':
        cout << "going to loadProfileMenu" << endl;
        loadProfileMenu();
        break;
    // Card Information
    case '3':
        cout << "going to cardInformationMenu" << endl;
        cardInformationMenu();
        break;
    // How to play
    case '4':
        cout << "going to gameRulesMenu" << endl;
        gameRulesMenu();
        break;
    // Save All
    case '5':
        cout << endl;
        cout << "NOT IMPLEMENTED" << endl;
        sleep(1); //sleep for 2s
        mainMenu();
        break;
    // Exit
    case '6':
        cout << "Exiting" << endl;
        sleep(1); //sleep for 2s
        return;
        break;
    default:
        cout << endl;
        cout << "Invalid Input" << t_inputChar << endl;
        sleep(2); //sleep for 2s
        mainMenu();
        break;
    } //eos
} //eo mainMenu

void GameMonitor::playGameMenu() 
{
    //clear console screen
    system("cls"); 

    cout << "Play Menu" << endl;
    cout << "\t Profile Loaded: " << t_loadedProfileName << endl;
    cout << "\t Deck Loaded: " << t_loadedDeckName << endl;
    cout << endl;
    cout << "1. Start" << endl;
    cout << "2. Change Deck" << endl;
    cout << "3. Create Deck" << endl;
    cout << "4. Back" << endl;
    cout << "Choice: ";
    cin >> t_inputChar;

    switch (t_inputChar)
    {
    // Start
    case '1': 
        cout << endl;
        cout << "NOT IMPLEMENTED" << endl;
        sleep(1);
        playGameMenu();
        break;
    // Change Deck
    case '2': 
        if (this->m_profileSet == false)
        {
            cout << "No profile is selected. No decks to load from." << endl;
            sleep(2);
            playGameMenu();
        }
        else
        {
            changeDeckMenu();
            playGameMenu();
        }
        break;
    // Create Deck
    case '3': 
        createDeckMenu();
        break;
    // Back
    case '4': 
        mainMenu();
        break;   
    default:
        cout << endl;
        cout << "Invalid Input" << t_inputChar << endl;
        sleep(2); //sleep for 2s
        playGameMenu();
        break;
    } //eos
} //eo playGameMenu

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
        cout << "Invalid Input" << t_inputChar << endl;
        sleep(2); //sleep for 2s
        cardInformationMenu();
        break;
    } //eos
} //eo cardInformationMenu

void GameMonitor::gameRulesMenu() 
{
    //clear console screen
    system("cls"); 

    cout << "Game Rules" << endl << endl;

    cout << "======== OBJECTIVE ========" << endl;
    cout << "Start with 5 HP." << endl;
    cout << "Reduce Opponents health to 0." << endl << endl;

    cout << "======== YOUR HAND ========" << endl;
    cout << "Start each round with 7 cards. 3 Core Cards and 4 cards drawn from your deck." << endl;
    cout << "Unplayed cards are kept in your hand." << endl << endl;

    cout << "======== FIGHTING ========" << endl;
    cout << "Each round has 5 battles, in which only 1 card is played. However, all 3 Core cards MUST be played." << endl;
    cout << "The order in which you play your Core cards does not matter, but all must be played within the 5 battles." << endl << endl;
    
    cout << "After all 5 battles have been played, send all non Core cards to the discard pile and start a new round." << endl;
    cout << "The 3 Core cards are added back to your hand and then draw cards from your deck to have 7 cards in your hand." << endl << endl;

    cout << "======== MISC ========" << endl;
    cout << "When the deck is empty, your discard pile is added to your deck and shuffled." << endl << endl;

    cout << "Enter any key to go back" << endl;
    cin >> t_inputStr;
    mainMenu();
} //eo gameRulesMenu

void GameMonitor::loadProfileMenu() 
{
    //clear console screen
    system("cls"); 

    cout << "Load Profile" << endl;
    cout << "\t Profile Loaded: " << this->m_currProfile.getProfileName() << endl;
    cout << endl;
    cout << "1. Change Profile" << endl;
    cout << "2. New Profile" << endl;
    cout << "3. Back" << endl;
	cout << "Choice: ";
    cin >> t_inputChar;

    switch (t_inputChar)
    {
    case '1': 
        changeProfileMenu();
        loadProfileMenu();
        break;
    case '2': 
        newProfileMenu();
        loadProfileMenu();
        break;
    case '3': 
        mainMenu();
        break;
    default:
        cout << endl;
        cout << "Invalid Input" << endl;
        sleep(2); //sleep for 2s
        loadProfileMenu();
        break;
    } //eos
} //eo loadProfileMenu

void GameMonitor::changeProfileMenu()
{
    int t_num;
    //clear console screen
    system("cls"); 

    cout << "Change Profile" << endl;
    cout << "\t Profile Loaded: " << this->m_currProfile.getProfileName() << endl;
    cout << endl;

    map<string, Profile>::iterator it;
    int counter = 1;
    for (it = ptr_profileDB->begin(); it != ptr_profileDB->end(); it++, counter++)
    {
        cout << counter << ". " << it->first << endl;
    } //eof
    
    // counter should be 1 more than max due to for loop
    cout << counter << ". Back" << endl;
	cout << "Choice: ";
    cin >> t_inputStr;

    try
    {
        t_num = stoi(t_inputStr);
    }
    catch(...)
    {
        cout << "Invalid input" << endl;
        changeProfileMenu();
    }
    
    // check if choice in bounds of profile list & Back choice
    if (t_num >= 1 && t_num <= counter)
    {
        // if Back is chosen
        if (t_num == counter)
        {
            return;
        }
        else
        {
            // increment iterator to choice
            it = ptr_profileDB->begin();
            for (int i = 0; i < t_num-1; i++)
            {
                it++;
            }
            
            this->m_currProfile = it->second;
            this->m_profileSet = true;
            t_loadedProfileName = it->second.getProfileName();
            changeProfileMenu();
        }
    }
    else
    {
        cout << "Invalid input" << endl;
        sleep(1);
        changeProfileMenu();
    }

} //eo changeProfileMenu

void GameMonitor::newProfileMenu()
{
    string t_profileName = "New Profile";
    
    while (true)
    {
        //clear console screen
        system("cls"); 

        cout << "Creating New Profile" << endl;
        cout << "\t Profile Name: " << t_profileName << endl;
        cout << endl;
        cout << "1. Done   - go back" << endl;
        cout << "2. Cancel - go back" << endl;
        cout << "Name: ";
        cin >> t_inputStr;

        if (t_inputStr.compare("1") == 0)
        {
            Profile t_profile(t_profileName);

            // Add profile to database and set as current profile
            this->ptr_profileDB->insert(pair<string, Profile>(t_profile.getProfileName(),t_profile));
            this->m_currProfile = this->ptr_profileDB->at(t_profile.getProfileName());
            return;
        }
        else if (t_inputStr.compare("2") == 0)
        {
            return;
        }
        else
        {
            t_profileName = t_inputStr;
        }
    } //eow
} //eo newProfileMenu

void GameMonitor::changeDeckMenu() 
{
    //clear console screen
    system("cls"); 

    cout << "Change Deck" << endl;
    cout << "\t Deck Loaded: " << t_loadedDeckName << endl;
    cout << endl;
    cout << "Decks Available: " << endl;
    int counter;
    for (counter = 1; counter < int(this->m_currProfile.getAllDecks().size())+1; counter++)
    {
        cout << counter << ". " << this->m_currProfile.getAllDecks().at(counter-1).getDeckName() << endl;
    } //eof
    cout << counter << ". Back" << endl;
	cout << "Choice: ";
    cin >> t_inputStr;

    if (t_inputStr.compare(""+(counter-1)) == 0)
    {
        playGameMenu();
    }

    int t_num;
    // convert input to int
    try
    {
        t_num = stoi(t_inputStr);
    }
    catch(...)
    {
        cout << endl;
        cout << "Invalid Input: " << t_inputStr << endl;
        sleep(2); //sleep for 2s
        changeDeckMenu();
    }
    
    if (t_num <= int(this->m_currProfile.getAllDecks().size()))
    {
        m_currDeck = this->m_currProfile.getAllDecks().at(t_num);
        m_deckSet = true;
        t_loadedDeckName = m_currDeck.getDeckName();
    }
    else
    {
        cout << endl;
        cout << "Invalid Input: " << t_inputStr << endl;
        sleep(2); //sleep for 2s
        changeDeckMenu();
    }
} //eo changeDeckMenu

void GameMonitor::createDeckMenu()
{
    bool exitMenu = false;
    string t_deckName = "New Deck";
    string temp;
    Deck t_deck(t_deckName, DECK_SIZE_LIMIT);
    
    while (exitMenu == false)
    {
        //clear console screen
        system("cls"); 

        cout << "Creating New Deck" << endl;
        cout << "\tDeck Name: " << t_deckName << endl << endl;

        displayDeckCreation(t_deck.getOriginalDeck());

        cout << "1. Edit Deck Name" << endl;
        cout << "2. Add Basic Card" << endl;
        cout << "3. Add Advanced Card" << endl;
        cout << "4. Remove Cards" << endl;
        cout << "5. Done   - Go back" << endl;
        cout << "6. Cancel - Go back" << endl;
        cout << "Choice: ";
        cin >> t_inputChar;

        switch (t_inputChar)
        {
        case '1': 
            temp = editDeckNameMenu();
            // Update new deckName only if valid
            temp.compare("-1") == 0 ? temp = "": t_deckName = temp;
            break;
        case '2': 
            addBasicCardMenu(&t_deck);
            break;
        case '3': 
            addAdvCardMenu(&t_deck);
            break;
        case '4': 
            removeCardMenu(&t_deck);
            break; 
        case '5':
            // deck restriction validation
            exitMenu = true;
            break;
        case '6':
            exitMenu = true;
            break;
        default:
            cout << endl;
            cout << "Invalid Input" << endl;
            sleep(2); //sleep for 2s
            createDeckMenu();
            break;
        } //eos
    } //eow
    playGameMenu();
} //eo createDeckMenu

string GameMonitor::editDeckNameMenu()
{
    string t_newDeckname = "New Deck";
    
    while (true)
    {
        //clear console screen
        system("cls"); 

        cout << "Deck Name: " << t_newDeckname << endl;
        cout << endl;
        cout << "1. Done   - go back" << endl;
        cout << "2. Cancel - go back" << endl;
        cout << "Name: ";
        cin >> t_inputStr;

        if (t_inputStr.compare("1") == 0)
        {
            return t_newDeckname;
        }
        else if (t_inputStr.compare("2") == 0)
        {
             return "-1";
        }
        else
        {
            t_newDeckname = t_inputStr;
        }
    } //eow
} //eo editDeckNameMenu

void GameMonitor::addBasicCardMenu(Deck *deck)
{

}

void GameMonitor::addAdvCardMenu(Deck *deck)
{

}

void GameMonitor::removeCardMenu(Deck *deck)
{

}
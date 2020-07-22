#ifndef MENUS_H_
#define MENUS_H_

#include "commonUtils.h"
#include "commonTypes.h"
#include "gameTypes.h"

#include <string>
#include <iostream>

using namespace std;


/* TYPE DEFINITIONS */
enum MenuIndex
{
  M_MAIN_MENU = 0,
  M_NEW_PROFILE,
  M_LOAD_PROFILE,
  M_QUICK_PLAY,
  M_NEW_DECK,
  M_LOAD_DECK,
  M_VIEW_DECK,

  NUM_MENUS
};

typedef struct MenuLUT
{
  MenuIndex menuIdx;
  string menuTitle;
  void (*dispMenu);
};

/* LOCAL VARIABLES */
static const int  MENU_STRING_LEN = 30;
static const char MENU_PAD_CHAR   = '=';
GameContext * gameCntxt;

/* MENU FUNCTIONS PROTOTYPES */
void initDispMenus();
void dispMainMenu();
void dispNewProfileMenu();
void dispLoadProfileMenu();
void dispQuickPlayMenu();
void dispNewDeckMenu();
void dispLoadDeckMenu();
void dispViewDeckMenu();

MenuLUT menuList[] =
{
  /*Menu Index          Menu Title           Menu Function*/
  {M_MAIN_MENU,         " MAIN MENU ",       &dispMainMenu},
  {M_NEW_PROFILE,       " NEW PROFILE ",     &dispNewProfileMenu},
  {M_LOAD_PROFILE,      " LOAD PROFILE ",    &dispLoadProfileMenu},
  {M_QUICK_PLAY,        " QUICK PLAY ",      &dispQuickPlayMenu},
  {M_NEW_DECK,          " NEW DECK ",        &dispNewDeckMenu},
  {M_LOAD_DECK,         " LOAD DECK ",       &dispLoadDeckMenu},
  {M_VIEW_DECK,         " VIEW DECK ",       &dispViewDeckMenu},
};

void initDispMenus()
{
  if (padString(&menuList[M_MAIN_MENU].menuTitle, MENU_STRING_LEN, MENU_PAD_CHAR) == RETVAL_ERROR)
  {
    menuList[M_MAIN_MENU].menuTitle = ">> MAIN MENU <<";
  }
  if (padString(&menuList[M_NEW_PROFILE].menuTitle, MENU_STRING_LEN, MENU_PAD_CHAR) == RETVAL_ERROR)
  {
    menuList[M_NEW_PROFILE].menuTitle = ">> NEW PROFILE <<";
  }
  if (padString(&menuList[M_LOAD_PROFILE].menuTitle, MENU_STRING_LEN, MENU_PAD_CHAR) == RETVAL_ERROR)
  {
    menuList[M_LOAD_PROFILE].menuTitle = ">> LOAD PROFILE <<";
  }
  if (padString(&menuList[M_QUICK_PLAY].menuTitle, MENU_STRING_LEN, MENU_PAD_CHAR) == RETVAL_ERROR)
  {
    menuList[M_QUICK_PLAY].menuTitle = ">> QUICK PLAY <<";
  }
  if (padString(&menuList[M_LOAD_DECK].menuTitle, MENU_STRING_LEN, MENU_PAD_CHAR) == RETVAL_ERROR)
  {
    menuList[M_LOAD_DECK].menuTitle = ">> LOAD DECK <<";
  }
  if (padString(&menuList[M_VIEW_DECK].menuTitle, MENU_STRING_LEN, MENU_PAD_CHAR) == RETVAL_ERROR)
  {
    menuList[M_VIEW_DECK].menuTitle = ">> VIEW DECK <<";
  }
}

void dispMainMenu()
{

  cout << menuList[M_MAIN_MENU].menuTitle << endl;

}

void dispNewProfileMenu()
{
  cout << "Profile Menu" << endl;
}
void dispLoadProfileMenu()
{
  cout << "Load Profile Menu" << endl;
}

void dispQuickPlayMenu()
{
  cout << "Quick Play Menu" << endl;
}

void dispNewDeckMenu()
{
  cout << "New Deck Menu" << endl;
}

void dispLoadDeckMenu()
{
  cout << "Load Deck Menu" << endl;
}

void dispViewDeckMenu()
{
  cout << "View Deck Menu" << endl;
}

#endif

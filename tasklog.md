# Task Log

Updates and working tasks

## refactor-folders
- [ ] Add folders in src and include to organize files
- [ ] Update makefile to reflect changes
- [ ] Update include paths

## add-deck-profiles
- [x] Add profile folder
- [x] Add example profile json file
    1. Profiles should be json files.
        - Profile Name
        - List of decks
            - Deck Profile
                - Deck Name
                - Card IDs
- [x] Add example decks 
- [x] Add profile class
- [x] Load profiles from main
- [x] Add deck class

## add-menus-profile-and-deck-creation
- [x] Add menus
    - [x] play game
    - [x] load profile
    - [x] change profile
    - [x] new profile
    - [x] card info
    - [x] game rules
    - [x] change deck
    - [x] create deck
- [x] Add card sorting for the deck

## extern-card-and-profile-db
- [x] Move db to global vars

## implement-battle
- [x] Add battle against rng bot
- [x] Add Battle Monitor class
    - [x] display round screen, hand, hp
    - [x] input validation for picking cards to play
- [x] Fix shuffle
- [x] Add discard pile and reshuffle discard pile to playdeck
- [x] Add Player Class
    - [x] implement player hand
- [x] Implement func pointer action queue

## refactor-action-switch-with-lut
- [ ] Implment Action 1 look-up-table
- [ ] Implment Action 2 look-up-table

## implement-save
- [x] Save profiles to json
    - [x] Update loadProfileData to check for save file
- [x] Add W-L to deck - not implemented yet lul

## implement-multiple-save-files
- [ ] Add feature for multiple save files
- [ ] Add loading of different save files
- [ ] Add continue last save file

## add-edit-and-remove-deck-options
- [ ] Add edit current deck choice
- [ ] Add delete current deck choice

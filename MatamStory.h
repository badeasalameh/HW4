
#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include <fstream>
#include <sstream>
#include <deque>
#include <cctype>

#include "Players/Player.h"
#include "Players/Archer.h"
#include "Players/Character.h"
#include "Players/Job.h"
#include "Players/Magician.h"
#include "Players/Responsible.h"
#include "Players/RiskTaking.h"
#include "Players/Warrior.h"

#include "Events/Event.h"
#include "Events/Balrog.h"
#include "Events/Encounter.h"
#include "Events/Pack.h"
#include "Events/PotionsMerchant.h"
#include "Events/Slime.h"
#include "Events/Snail.h"
#include "Events/SolarEclipse.h"
#include "Events/SpecialEvent.h"

#define MAXIMAL_HP 50
#define DAMAGE_TAKEN_ON_PLAYER_WIN 10
#define MAX_LEVEL 10
#define MIN_HP 0

#define MIN_PACK_MEMBER_NUMBER 2
#define MIN_NUMBER_OF_EVENTS 2
#define MAX_NUMBER_OF_PLAYERS 6
#define MIN_NUMBER_OF_PLAYERS 2
#define MAX_NAME_LENGTH 15
#define NUMBER_OF_PLAYER_PARAMETERS 3
#define MIN_NAME_LENGTH 3

class MatamStory{
private:

    unsigned int m_turnIndex;
    class isCharacter;
    class isBehavior;
//    bool check_players_input(string& playerName,string& playerCharacter,string& playerBehavior);
    std::set<shared_ptr<Player>> leaderBoardSet;
//    int WinnerIdx() const;
    /**
     * Playes a single turn for a player
     *
     * @param player - the player to play the turn for
     *
     * @return - void
    */
    void playTurn(Player& player);

    /**
     * Plays a single round of the game
     *
     * @return - void
    */
    void playRound();

    /**
     * Checks if the game is over
     *
     * @return - true if the game is over, false otherwise
    */
        bool isGameOver() const;
//    void add_player(string& playerName,string& playerCharacter,string& playerBehavior);
    void add_card(const string& cardName);
    void put_cards(const vector<string>& cardsVector , int* start_index);
    vector<shared_ptr<Event>> pack_input( const vector<string>& cardsVector,vector<shared_ptr<Event>>& packVector,int* start_index,int packSize);
    bool isNumber(const string&);
     vector<shared_ptr<Event>> m_Cards;
//    vector<shared_ptr<Player>> m_Players;
    deque<shared_ptr<Player>> m_players;

    void updateLeaderboard();

public:
    /**
     * Constructor of MatamStory class
     *
     * @param eventsStream - events input stream (file)
     * @param playersStream - players input stream (file)
     *
     * @return - MatamStory object with the given events and players
     *
    */
    MatamStory(std::istream& eventsStream, std::istream& playersStream);
    /**
     * Plays the entire game
     *
     * @return - void
    */
    void play();
};

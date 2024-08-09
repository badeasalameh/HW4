
#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <memory>

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

class MatamStory{
private:
    unsigned int m_turnIndex;

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

    //////////////////////////////////////////////////////////////
    //ADDED PRIVATE METHODS:
    vector<shared_ptr<Player>> m_players;
    vector<shared_ptr<Event>> m_events;

    set<shared_ptr<Player>> m_leaderboard;

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

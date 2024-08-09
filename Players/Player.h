
#pragma once

#include <string>
#include <memory>
#include <iostream>

#include "Job.h"
#include "Character.h"

using namespace std;
using std::string;

class Player {
public:
    //ADDED METHODS:
    Player(const char* name , unique_ptr<Job> job ,unique_ptr<Character> character , int level = INITIAL_LEVEL ,
           int force = INITIAL_FORCE , int maxHP = INITIAL_MAX_HP , int coins = INITIAL_COINS);

    ~Player() = default;

    int getCombatPower() const;

    string getJob() const;

    string getCharacter() const;

    void alterForce(int change);

    bool pay(int amount);

    void addHealth(int healthAdded);
    void takeDamage(int damage);

    int getMaxHP() const;

    bool isWarrior() const;
    bool isArcher() const;
    bool isMagician() const;

    void takeLoot(int loot);
    ///////////////////////////////////////////////////////
    /**
     * Gets the description of the player
     *
     * @return - description of the player
    */
    string getDescription() const;

    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    string getName() const;

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    int getLevel() const;

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    int getHealthPoints() const;

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    int getCoins() const;

private:
    string m_name;
    int m_level;
    int m_force;
    int m_currHP;
    int m_maxHP;
    int m_coins;

    unique_ptr<Job> m_job;
    unique_ptr<Character> m_character;
    ////////////////////////////////////
    static const int INITIAL_LEVEL = 1;

    static const int INITIAL_FORCE = 5;

    static const int INITIAL_MAX_HP = 100;
    static const int INITIAL_WARRIOR_MAX_HP = 150;

    static const int INITIAL_COINS = 10;
    static const int INITIAL_ARCHER_COINS = 20;

    static const int MINIMAL_HP = 0;
    ////////////////////////////////////
    friend bool operator<(const Player& p1 , const Player& p2);
};
bool operator<(const shared_ptr<Player>& p1 , const shared_ptr<Player>& p2);
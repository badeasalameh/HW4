#include "Player.h"

#include <utility>

Player :: Player(string name, unique_ptr<Job> job, unique_ptr<Character> character, int level, int force, int maxHP, int coins)
        : m_name(std::move(name)),
          m_level(level),
          m_force(force),
          m_currHP(maxHP),
          m_maxHP(maxHP),
          m_coins(coins),
          m_job(std::move(job)),
          m_character(std::move(character))
{
    // LEVEL CHECK:
    if(level < 1 || level > 10) {
        throw invalid_argument("level must be a neutral number between 1 and 10");
    }

    // FORCE CHECK:
    if(m_force < 0) {
        throw invalid_argument("force should be a non-negative number");
    }

    // HP CHECK:
    if(m_maxHP <= 0) {
        throw invalid_argument("maxHP should be a positive number");
    }

    // COINS CHECK:
    if(m_coins < 0) {
        throw invalid_argument("coins should be a non-negative number");
    }

    if(m_job->getJob() == "Warrior") {
        m_maxHP = INITIAL_WARRIOR_MAX_HP;
        m_currHP = m_maxHP;
    } else if(m_job->getJob() == "Archer") {
        m_coins = INITIAL_ARCHER_COINS;
    }
}


int Player :: getCombatPower() const
{
    if(m_job -> getJob() == "Warrior")
    {
        return m_force * 2 + m_level;
    }
    return m_force + m_level;
}

string Player :: getName() const
{
    return m_name;
}

int Player :: getLevel() const
{
    return m_level;
}

int Player :: getForce() const
{
    return m_force;
}

int Player :: getHealthPoints() const
{
    return m_currHP;
}

int Player :: getCoins() const
{
    return m_coins;
}

string Player :: getDescription() const
{
    return  m_name + ", " + m_job -> getJob() + " with " + m_character -> getCharacter() +
    " character (level " + to_string(m_level) + ", " + "force " + to_string(m_force) + ')';
}

string Player :: getJob() const
{
    return m_job -> getJob();
}

string Player :: getCharacter() const
{
    return m_character -> getCharacter();
}

bool operator<(const Player& player1 , const Player& player2)
{
    if(player1.getLevel() > player2.getLevel())
    {
        return true;
    }
    else if(player1.getLevel() == player2.getLevel())
    {
        if(player1.getCoins() > player2.getCoins())
        {
            return true;
        }
        else if(player1.getCoins() == player2.getCoins())
        {
            //was > :
            if(player1.getName() < player2.getName())
            {
                return true;
            }
        }
    }
    return false;
}

bool operator<(const shared_ptr<Player>& player1 , const shared_ptr<Player>& player2)
{
    return (*player1 < *player2);
}

void Player :: alterForce(int change)
{
    if(m_force + change <= 0)
    {
        m_force = 0;
    }
    else
    {
        m_force += change;
    }
}

bool Player :: pay(int amount)
{
    if(m_coins >= amount)
    {
        m_coins -= amount;
        return true;
    }
    else
    {
        return false;
    }
}

void Player :: addHealth(int healthAdded)
{
    if(m_currHP + healthAdded <= m_maxHP)
    {
        m_currHP += healthAdded;
    }
    else
    {
        m_currHP = m_maxHP;
    }
}

void Player :: takeDamage(int damageTaken)
{
    if(m_currHP - damageTaken >= MINIMAL_HP)
    {
        m_currHP -= damageTaken;
    }
    else
    {
        m_currHP = MINIMAL_HP;
    }
}

int Player :: getMaxHP() const
{
    return m_maxHP;
}

bool Player :: isArcher() const
{
    return (getJob() == "Archer");
}

bool Player :: isWarrior() const
{
    return (getJob() == "Warrior");
}

bool Player :: isMagician() const
{
    return (getJob() == "Magician");
}

void Player :: takeLoot(int loot)
{
    m_coins += loot;
}

void Player :: addLevel()
{
    m_level += LEVEL_ADD;
}

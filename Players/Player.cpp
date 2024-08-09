#include "Player.h"

Player :: Player(const char* name , unique_ptr<Job> job ,unique_ptr<Character> character , int level , int force ,
                int maxHP , int coins) : m_name(name) , m_job(std::move(job)) , m_character(std::move(character)) ,
                m_level(level) , m_force(force) , m_maxHP(maxHP) , m_currHP(maxHP) , m_coins(coins)
{
    //NAME CHECK:
    if(m_name.size() > 15)
    {
        throw invalid_argument("Name must be 15 characters or less");
    }
    for(char letter : m_name)
    {
        if(letter == ' ')
        {
            throw invalid_argument("Name must not contain spaces");
        }
    }
    ////////////////////////////////////////////
    //LEVEL CHECK:
    if(level < 1 || level > 10)
    {
        throw invalid_argument("level must be neutral number between 1 and 10");
    }
    ///////////////////////////////////////////
    //FORCE CHECK:
    if(m_force < 0)
    {
        throw invalid_argument("force should be a non - negative number");
    }
    //////////////////////////////////////////
    //HP CHECK:
    if(m_maxHP <= 0)
    {
        throw invalid_argument("maxHP should be a positive number");
    }
    //////////////////////////////////////////
    //COINS CHECK:
    if(m_coins < 0)
    {
        throw invalid_argument("coins should be a non - negative number");
    }
    /////////////////////////////////////////
    if(m_job -> getJob() == "WARRIOR")
    {
        m_maxHP = INITIAL_WARRIOR_MAX_HP;
        m_currHP = m_maxHP;
    }

    else if(m_job -> getJob() == "ARCHER")
    {
        m_coins = INITIAL_ARCHER_COINS;
    }
}

int Player :: getCombatPower() const
{
    if(m_job -> getJob() == "WARRIOR")
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
    " (level " + to_string(m_level) + ", " + "force " + to_string(m_force) + ')';
}

string Player :: getJob() const
{
    return m_job -> getJob();
}

string Player :: getCharacter() const
{
    return m_character -> getCharacter();
}

bool operator<(const Player& p1 , const Player& p2)
{
   if(p1.getLevel() > p2.getLevel())
   {
       return true;
   }
   else if(p1.getLevel() == p2.getLevel())
   {
       if(p1.getCoins() > p2.getCoins())
       {
           return true;
       }
       else if(p1.getCoins() == p2.getCoins())
       {
           if(p1.getName() > p2.getName())
           {
               return true;
           }
       }
   }
   return false;
}

bool operator<(const shared_ptr<Player>& p1 , const shared_ptr<Player>& p2)
{
    return (*p1 < *p2);
}

void Player :: alterForce(int change)
{
    m_force += change;
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

#include "Encounter.h"
Encounter :: Encounter(const char* monster , int combatPower , int loot , int damage) : Event("Encounter") ,
                       m_monster(monster) , m_combatPower(combatPower) , m_loot(loot) , m_damage(damage)
{}

string Encounter :: getDescription() const
{
    return m_monster + " (power " + to_string(m_combatPower) + ", loot " + to_string(m_loot) + ", damage " +
           to_string(m_damage) + ')';
}

int Encounter :: getCombatPower() const
{
    return m_combatPower;
}

int Encounter :: getLoot() const
{
    return m_loot;
}

int Encounter :: getDamage() const
{
    return m_damage;
}

#include "Balrog.h"
Balrog :: Balrog() : Encounter("Balrog" , BALROG_COMBAT_POWER , BALROG_LOOT , BALROG_DAMAGE)
{}

void Balrog :: balrogCombatPowerIncrease()
{
    m_combatPower += BALROG_COMBAT_POWER_INCREASE;
}

string Balrog :: getDescription() const
{
    return "Balrog (power " + to_string(getCombatPower()) + ", loot " + to_string(getLoot()) + ", damage " + to_string(getDamage()) + ')';
}
#include "Snail.h"
Snail :: Snail() : Encounter("Snail" , SNAIL_COMBAT_POWER , SNAIL_LOOT , SNAIL_DAMAGE)
{}

string Snail :: getDescription() const
{
    return "Snail (power " + to_string(getCombatPower()) + ", loot " + to_string(getLoot()) + ", damage " + to_string(getDamage()) + ')';
}
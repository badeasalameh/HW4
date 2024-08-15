#include "Slime.h"
Slime :: Slime() : Encounter("Slime" , SLIME_COMBAT_POWER , SLIME_LOOT , SLIME_DAMAGE)
{}

string Slime :: getDescription() const
{
    return "Slime (power " + to_string(getCombatPower()) + ", loot " + to_string(getLoot()) + ", damage " + to_string(getDamage()) + ')';
}
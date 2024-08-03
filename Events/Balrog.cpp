#include "Balrog.h"
Balrog :: Balrog() : Encounter("BALROG" , BALROG_COMBAT_POWER , BALROG_LOOT , BALROG_DAMAGE)
{}

void Balrog :: balrogCombatPowerIncrease()
{
    m_CombatPower += BALROG_COMBAT_POWER_INCREASE;
}
#include "SolarEclipse.h"
SolarEclipse :: SolarEclipse() : SpecialEvent("SolarEclipse")
{}

int SolarEclipse :: getForceBuff()
{
    return FORCE_BUFF;
}

int SolarEclipse :: getForceNerf()
{
    return FORCE_NERF;
}
int SolarEclipse::getCombatPower() const {
    return 0;
}
int SolarEclipse::getDamage() const {
    return 0 ;
}
int SolarEclipse::getLoot() const{
    return 0;
}

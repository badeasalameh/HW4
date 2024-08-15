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
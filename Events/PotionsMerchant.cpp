#include "PotionsMerchant.h"
PotionsMerchant :: PotionsMerchant() : SpecialEvent("PotionsMerchant")
{}

int PotionsMerchant :: getPotionCost()
{
    return COST;
}

int PotionsMerchant :: getPotionEffect()
{
    return EFFECT;
}
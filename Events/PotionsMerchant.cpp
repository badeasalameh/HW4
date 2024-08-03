#include "PotionsMerchant.h"
PotionsMerchant :: PotionsMerchant() : SpecialEvent("POTIONSMERCHANT")
{}

int PotionsMerchant :: getPotionCost()
{
    return COST;
}

int PotionsMerchant :: getPotionEffect()
{
    return EFFECT;
}
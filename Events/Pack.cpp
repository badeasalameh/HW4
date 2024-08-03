#include "Pack.h"
Pack :: Pack() : Encounter("PACK" , EMPTY_PACK_PARAMETERS , EMPTY_PACK_PARAMETERS , EMPTY_PACK_PARAMETERS)
{}

void Pack :: insertNewMember(unique_ptr<Encounter> newMember)
{
    m_packMembers.push_back(std :: move(newMember));
    m_CombatPower += newMember -> getCombatPower();
    m_loot += newMember -> getLoot();
    m_damage += newMember -> getDamage();
}

const vector<unique_ptr<Encounter>>& Pack :: getPackMembers() const
{
     return m_packMembers;
}

int Pack :: getPackSize() const
{
    int size = 0;
    for(const unique_ptr<Encounter>& member : m_packMembers)
    {
        size++;
    }
    return size;
}

string Pack :: getDescription() const
{
    return "Pack of " + to_string(getPackSize()) + " members (power " + to_string(m_CombatPower) + ", loot " +
            to_string(m_loot) + ", damage " + to_string(m_damage) + ')';
}
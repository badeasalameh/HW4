#include "Pack.h"
Pack :: Pack() : Encounter("Pack" , EMPTY_PACK_PARAMETERS , EMPTY_PACK_PARAMETERS , EMPTY_PACK_PARAMETERS)
{}

void Pack :: insertNewMember(shared_ptr<Encounter> newMember)
{
    m_packMembers.push_back(newMember);
    m_CombatPower += newMember -> getCombatPower();
    m_loot += newMember -> getLoot();
    m_damage += newMember -> getDamage();
}

const vector<shared_ptr<Encounter>>& Pack :: getPackMembers() const
{
     return m_packMembers;
}

int Pack :: getPackSize() const
{

    return static_cast<int>(m_packMembers.size());
}

string Pack :: getDescription() const
{
    return "Pack of " + to_string(getPackSize()) + " members (power " + to_string(m_CombatPower) + ", loot " +
            to_string(m_loot) + ", damage " + to_string(m_damage) + ')';
}

void Pack :: insertNewMembers(vector<shared_ptr<Encounter>> newMembers)
{
    for(const shared_ptr<Encounter>& member : newMembers)
    {
        insertNewMember(member);
    }
}

void Pack :: addCombatPower()
{
    m_CombatPower += POWER_ADD;
}
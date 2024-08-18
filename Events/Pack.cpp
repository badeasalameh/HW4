#include "Pack.h"
Pack :: Pack() : Encounter("Pack" , EMPTY_PACK_PARAMETERS , EMPTY_PACK_PARAMETERS , EMPTY_PACK_PARAMETERS) ,
m_size(0), m_combatPower(0)
{}

Pack::Pack(const vector<shared_ptr<Event>> &vec) :  m_size(0),m_combatPower(0),packVector(vec){
    int sum_of_combat_power = 0;
    int sum_of_damage = 0;
    int sum_of_loot = 0;
    m_size = static_cast<int>(vec.size());
    for (const auto& it : vec) {
        sum_of_combat_power += it->getCombatPower();
        sum_of_damage += it->getDamage();
        sum_of_loot += it->getLoot();
    }
    m_combatPower = sum_of_combat_power;
    m_loot = sum_of_loot;
    m_damage = sum_of_damage;
    m_name = "Pack";
}


const vector<shared_ptr<Event>>& Pack :: getPackMembers() const
{
     return packVector;
}

int Pack :: getPackSize() const
{

    return static_cast<int>(packVector.size());
}

string Pack :: getDescription() const
{
    return "Pack of " + to_string(getPackSize()) + " members (power " + to_string(m_combatPower) + ", loot " +
            to_string(m_loot) + ", damage " + to_string(m_damage) + ')';
}

//void Pack :: insertNewMembers(vector<shared_ptr<Encounter>> newMembers)
//{
//    for(const shared_ptr<Encounter>& member : newMembers)
//    {
//        insertNewMember(member);
//    }
//}

void Pack :: addCombatPower()
{
    m_combatPower += POWER_ADD;
}

int Pack::getCombatPower() const {
    int sum_of_combat_power = 0;
    for(const auto& it : packVector){
        sum_of_combat_power += it->getCombatPower();
    }
    return sum_of_combat_power;
}

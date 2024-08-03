#ifndef HW4_ENCOUNTER_H
#define HW4_ENCOUNTER_H

#define UNINITIALIZED (-1)

#include "Event.h"

class Encounter : public Event{
public:
    explicit Encounter(const char* monster , int combatPower = UNINITIALIZED_COMBAT_POWER , int loot = UNINITIALIZED_LOOT
            , int damage = UNINITIALIZED_DAMAGE);

    string getDescription() const override;

    int getCombatPower() const;
    int getLoot() const;
    int getDamage() const;

protected:
    string m_monster;
    int m_CombatPower;
    int m_loot;
    int m_damage;

private:
    static const int UNINITIALIZED_COMBAT_POWER = UNINITIALIZED;
    static const int UNINITIALIZED_LOOT = UNINITIALIZED;
    static const int UNINITIALIZED_DAMAGE = UNINITIALIZED;
};


#endif //HW4_ENCOUNTER_H

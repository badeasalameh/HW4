#ifndef HW4_ENCOUNTER_H
#define HW4_ENCOUNTER_H

#include "Event.h"

class Encounter : public Event{
public:
    Encounter() = default;
    explicit Encounter(const char* monster , int combatPower = UNINITIALIZED_COMBAT_POWER , int loot = UNINITIALIZED_LOOT
            , int damage = UNINITIALIZED_DAMAGE);

    string getDescription() const override;

    virtual int getCombatPower() const;
    int getLoot() const;
    int getDamage() const;

protected:
    string m_monster;
    int m_combatPower;
    int m_loot;
    int m_damage;

private:
    static const int UNINITIALIZED_COMBAT_POWER = 0;
    static const int UNINITIALIZED_LOOT = 0;
    static const int UNINITIALIZED_DAMAGE = 0;
};


#endif //HW4_ENCOUNTER_H

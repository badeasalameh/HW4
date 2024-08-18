#ifndef HW4_PACK_H
#define HW4_PACK_H

#include "Encounter.h"
#include <vector>

class Pack : public Encounter{
private:
    unsigned int m_size;
    int m_combatPower ;
    vector<shared_ptr<Event>> packVector;
    string m_name;
    static const int EMPTY_PACK_PARAMETERS = 0;
    static const int POWER_ADD = 2;

public:
    Pack();
    explicit Pack(const vector<shared_ptr<Event>>&vec);
    int getPackSize() const;
    void addCombatPower();
     int getCombatPower()const override;
    string getDescription() const override;
    const vector<shared_ptr<Event>>&  getPackMembers() const;


};


#endif //HW4_PACK_H

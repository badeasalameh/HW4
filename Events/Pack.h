#ifndef HW4_PACK_H
#define HW4_PACK_H

#include "Encounter.h"
#include <vector>

class Pack : public Encounter{
public:
    Pack();
    void insertNewMember(shared_ptr<Encounter> newMember);
    void insertNewMembers(vector<shared_ptr<Encounter>> newMembers);
    const vector<shared_ptr<Encounter>>& getPackMembers() const;
    int getPackSize() const;
    void addCombatPower();
    string getDescription() const override;

private:
    static const int EMPTY_PACK_PARAMETERS = 0;
    static const int POWER_ADD = 2;

    vector<shared_ptr<Encounter>> m_packMembers;
};


#endif //HW4_PACK_H

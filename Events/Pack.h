#ifndef HW4_PACK_H
#define HW4_PACK_H

#include "Encounter.h"
#include <vector>

class Pack : public Encounter{
public:
    Pack();
    void insertNewMember(unique_ptr<Encounter> newMember);
    const vector<unique_ptr<Encounter>>& getPackMembers() const;
    int getPackSize() const;
    string getDescription() const override;

private:
    static const int EMPTY_PACK_PARAMETERS = 0;

    vector<unique_ptr<Encounter>> m_packMembers;
};


#endif //HW4_PACK_H

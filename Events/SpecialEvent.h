#ifndef HW4_SPECIALEVENT_H
#define HW4_SPECIALEVENT_H

#include "Event.h"

class SpecialEvent : public Event{
public:
    explicit SpecialEvent(const char* specialEventType);
    string getSpecialEventType() const;
    virtual string getDescription() const override;

private:
    string m_specialEventType;
};


#endif //HW4_SPECIALEVENT_H

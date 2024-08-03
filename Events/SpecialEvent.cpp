#include "SpecialEvent.h"
SpecialEvent ::SpecialEvent(const char* specialEventType) : Event("SPECIALEVENT") , m_specialEventType(specialEventType)
{}

string SpecialEvent :: getSpecialEventType() const
{
    return m_specialEventType;
}
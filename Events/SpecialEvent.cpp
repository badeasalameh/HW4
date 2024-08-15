#include "SpecialEvent.h"
SpecialEvent :: SpecialEvent(const char* specialEventType) : Event("SpecialEvent") , m_specialEventType(specialEventType)
{}

string SpecialEvent :: getSpecialEventType() const
{
    return m_specialEventType;
}

string SpecialEvent :: getDescription() const
{
    return m_specialEventType;
}
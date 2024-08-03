#include "Event.h"
Event :: Event(const char* eventType) : m_eventType(eventType)
{}

string Event :: getDescription() const
{
    return m_eventType;
}
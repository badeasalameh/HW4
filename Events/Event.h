
#pragma once

#include "../Players/Player.h"

class Event {
public:
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    //CHECK IF ADDING VIRTUAL IS OK:
    virtual string getDescription() const;
    virtual ~Event() = default;
    explicit Event(const char* eventType);

protected:
    string m_eventType;
};


#pragma once

#include "../Players/Player.h"

class Event {
public:
    Event() = default;
    virtual int getCombatPower() const = 0;
    virtual int getDamage() const = 0;
    virtual int getLoot() const = 0;
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    //CHECK IF ADDING VIRTUAL IS OK:
    virtual string getDescription() const = 0;
    virtual ~Event() = default;
    explicit Event(const char* eventType);

protected:
    string m_eventType;
};

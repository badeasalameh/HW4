cmake_minimum_required(VERSION 3.27)
project(HW4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Events)
include_directories(Players)

add_executable(HW4
        Events/Event.h
        Players/Player.h
        main.cpp
        MatamStory.cpp
        MatamStory.h
        Utilities.cpp
        Utilities.h
        Players/Player.cpp
        Players/Job.cpp
        Players/Job.h
        Players/Character.cpp
        Players/Character.h
        Players/Warrior.cpp
        Players/Warrior.h
        Players/Archer.cpp
        Players/Archer.h
        Players/Magician.cpp
        Players/Magician.h
        Players/Responsible.h
        Players/RiskTaking.cpp
        Players/RiskTaking.h
        Players/Responsible.cpp
        Events/Event.cpp
        Events/Encounter.cpp
        Events/Encounter.h
        Events/Snail.cpp
        Events/Snail.h
        Events/Slime.cpp
        Events/Slime.h
        Events/Pack.cpp
        Events/Pack.h
        Events/Balrog.cpp
        Events/Balrog.h
        Events/SpecialEvent.cpp
        Events/SpecialEvent.h
        Events/SolarEclipse.cpp
        Events/SolarEclipse.h
        Events/PotionsMerchant.cpp
        Events/PotionsMerchant.h
)

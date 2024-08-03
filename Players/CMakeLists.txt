cmake_minimum_required(VERSION 3.27)
project(Players)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Players
        Archer.cpp
        Archer.h
        Character.cpp
        Character.h
        Job.cpp
        Job.h
        Magician.cpp
        Magician.h
        Player.cpp
        Player.h
        Responsible.cpp
        Responsible.h
        RiskTaking.cpp
        RiskTaking.h
        Warrior.cpp
        Warrior.h)

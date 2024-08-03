#include "Character.h"

Character :: Character(const char* character) : m_character(character)
{}

string Character :: getCharacter() const
{
    return m_character;
}
#ifndef HW4_CHARACTER_H
#define HW4_CHARACTER_H

#include <string>

using namespace std;

class Character {
public:
    explicit Character(const char* character);
    virtual ~Character() = default;
    string getCharacter() const;

private:
    string m_character;
};


#endif //HW4_CHARACTER_H

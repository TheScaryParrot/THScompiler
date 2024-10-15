#pragma once

#include <vector>

#include "TwoChar.cpp"
class CharacterGroup
{
   public:
    CharacterGroup() { twoChars = std::vector<TwoChar>(); }
    CharacterGroup(std::vector<TwoChar> twoChars) { this->twoChars = twoChars; }
    CharacterGroup(std::vector<CharacterGroup> characterGroups)
    {
        for (CharacterGroup group : characterGroups)
        {
            for (TwoChar twoChar : group.twoChars)
            {
                this->twoChars.push_back(twoChar);
            }
        }
    }
    CharacterGroup(std::vector<TwoChar> twoChars, std::vector<CharacterGroup> characterGroups)
    {
        this->twoChars = twoChars;

        for (CharacterGroup group : characterGroups)
        {
            for (TwoChar twoChar : group.twoChars)
            {
                this->twoChars.push_back(twoChar);
            }
        }
    }

    enum EMatchResults : unsigned int
    {
        NO_MATCH = 0,
        FIRST_MATCH = 1,
        BOTH_MATCH = 2
    };

    EMatchResults Match(char first, char second)
    {
        unsigned int match = 0;

        for (TwoChar twoChar : twoChars)
        {
            match = twoChar.Match(first, second);

            if (match > 0) return (EMatchResults)match;
        }

        return NO_MATCH;
    }

    static CharacterGroup Empty() { return CharacterGroup(); }

   private:
    std::vector<TwoChar> twoChars;
};
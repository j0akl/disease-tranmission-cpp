#ifndef PERSON_H
#define PERSON_H

#include <vector>


class Person { 
    public:

        Person(int infectionChance, int globalInfectionDuration, int m_groupId, int m_groupIndex);
        Person(); // this is an overload for array creation

        void changeState(std::vector<std::vector<Person> > population);

        // getters
        bool getInfected();
        bool getImmune();
        bool getUntouched();
        bool getDead();
        int  getInfectDuration();
        int  getInfectCounter();

        // setters
        void setInfected(bool x);
        void setImmune(bool x);
        void setUntouched(bool x);
        void setDead(bool x);
        void setInfectionDuration(int x);
        void incrementCounter();
        void clearCounter();
        void setGroupId(int x);
        void setGroupIndex(int x);
        void setInfectionChance(int x);
        void infect();
    private:
        bool infected;
        bool immune;
        bool untouched;
        bool dead;
        int  infectionDuration;
        int  infectCounter;
        int  groupId;
        int  groupIndex;
        int  infectionChance;
};

#endif

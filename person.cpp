#include <iostream>
#include <string>
#include <vector>
#include "person.h"
using namespace std;

// initialize with default values
Person::Person(int infectionChance, int globalInfectionDuration, int m_groupId, int m_groupIndex) {
    setInfected(false);
    setImmune(false);
    setUntouched(true);
    setDead(false);
    setInfectionChance(infectionChance);
    clearCounter();


    // give local access to infectionDuration
    setInfectionDuration(globalInfectionDuration);
    setGroupId(m_groupId);
    setGroupIndex(m_groupIndex);

}

Person::Person() {}

void Person::changeState(vector<vector<Person> > population) {

    
    if(infected) {
        incrementCounter();
    }

    if (infectCounter >= infectionDuration) {
        // person has recovered
        // TODO - add death
        setInfected(false);
        setImmune(true);
    }

    for (int i = 0; i < population[groupId].size(); i++) {
        // if there are infected people in the persons group, there is a chance
        // they will be infected
        // this will be fast for small group sizes, if larger sizes are used
        // switch to a better sorting algorithm
        // these next 3 if statements check for infection in the group as well
        // as the two nearest groups. Infections within the group have a higher
        // chance to transmit
        if (population[groupId][i].getInfected() == true) {
            int random = rand() % 100 + 1; // replace with better rand
            if (random <= infectionChance * 2 && !getImmune()) {
                infect();
            }
        }
        if (groupId != population.size() - 1 && population[groupId + 1][i].getInfected() == true) {
            int random = rand() % 100 + 1; // replace with better rand
            if (random <= infectionChance && !getImmune()) {
                infect();
            }
        }
        if (groupId != 0 && population[groupId - 1][i].getInfected() == true) {
            int random = rand() % 100 + 1; // replace with better rand
            if (random <= infectionChance && !getImmune()) {
                infect();
            }
        }
    }

}

// getter methods
bool Person::getInfected()        { return infected; }
bool Person::getImmune()          { return immune; }
bool Person::getUntouched()       { return untouched; }
bool Person::getDead()            { return dead; }
int  Person::getInfectCounter()   { return infected; }

// setter methods
void Person::setInfected(bool x)         { infected = x; }
void Person::setImmune(bool x)           { immune = x; }
void Person::setUntouched(bool x)        { untouched = x; }
void Person::setDead(bool x)             { dead = x; }
void Person::incrementCounter()          { infectCounter += 1; }
void Person::clearCounter()              { infectCounter = 0; }
void Person::setInfectionDuration(int x) { infectionDuration = x; }
void Person::setGroupId(int x)           { groupId = x; }
void Person::setGroupIndex(int x)        { groupIndex = x; }
void Person::setInfectionChance(int x)   { infectionChance = x; }
void Person::infect() {
    infected = true;
    untouched = false;
}

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "person.h"
using namespace std;

// initialize population 
vector<vector<Person> > population;

void showPopulation() {
    // draw infect status of entire population
    for (int i = 0; i < population.size(); i++) {
        for (int j = 0; j < population[0].size(); j++) {
            if (population[i][j].getImmune()) {
                cout << 2;
            } else {
                cout << population[i][j].getInfected();
            }
        }
        cout << " " << endl;
    }
}

void runIteration() {
    // run a single iteration
    // run this periodically in the full sim
    for (int i = 0; i < population.size(); i++) {
        for (int j = 0; j < population[0].size(); j++) {
            population[i][j].changeState(population);
        }
    }
}

void runAnimation() {
    bool eradicated = false;

    while (!eradicated) {
        cout << "-----" << endl;
        runIteration();
        showPopulation();
        eradicated = true;
        for (int i = 0; i < population.size(); i++) {
            for (int j = 0; j < population[0].size(); j++) {
                if (population[i][j].getInfected()) {
                    eradicated = false;
                }
            }
        }
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    int untouchedCounter = 0;
    int immuneCounter = 0;
    int deadCounter = 0;
    for (int i = 0; i < population.size(); i++) {
        for (int j = 0; j < population[0].size(); j++) {
            if (population[i][j].getUntouched()) {
                untouchedCounter++;
            }
            if (population[i][j].getImmune()) {
                immuneCounter++;
            }
            if (population[i][j].getDead()) {
                deadCounter++;
            }
        }
    }
    cout << "People Killed:           " << deadCounter << endl;
    cout << "People with immunity:    " << immuneCounter << endl;
    cout << "People without immunity: " << untouchedCounter << endl;
}

int main() {

    // upper limit on the number of days the simulation will run
    int maxDuration = 1000; 

    // this is left as 50 and 50 for now for drawing purposes in the console,
    // when this gets animated make smaller groups so they act like households
    int groups;
    int groupSize;
    cout << "Enter the number of groups: " << endl;
    cin >> groups;
    cout << "Enter the size of each group: " << endl;
    cin >> groupSize;

    // TODO - make the animation end when there are no more infected people

    // % chance someone will be infected at a given interaction
    int infectionChance;
    cout << "Enter the chance of infection (%): " << endl;
    cin >> infectionChance;

    // number of days a person is sick
    // TODO - add variance
    int globalInfectionDuration;
    cout << "Enter the infection duration: " << endl;
    cin >> globalInfectionDuration;


    // fill population
    for (int i = 0; i < groups; i++) {
        vector<Person> tempGroup;
        for (int j = 0; j < groupSize; j++) {
            tempGroup.push_back(Person(infectionChance,
                                       globalInfectionDuration, 
                                       i, 
                                       j));
        }
        population.push_back(tempGroup);
    }

    // create patient zero
    population[5][3].infect();


    runAnimation();




    return 0;
}

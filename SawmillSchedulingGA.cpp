#include <vector>
#include <iostream>

#include "GeneticAlgorithm.hpp"

struct Shift {
    int extraWorkers;
    double productionVolume;
};

struct Solution {
    std::vector<Shift> shifts;
};

class SawmillSchedulingGA : public GeneticAlgorithm {
public:
    SawmillSchedulingGA(int populationSize, int generations, int elitSize, double mutationRate, double crossoverRate)
        : GeneticAlgorithm(populationSize, generations, elitSize, mutationRate, crossoverRate) {}

    Solution getBestSolution() {}

private:
    void initializePopulation() override {}

    void calculateFitness() override {}

    void selection() override {}

    void crossover() override {}

    void mutation() override {}

    void sort() override {}
};


int main() {
    SawmillSchedulingGA SawmillSchedulingGA(100, 200, 70, 0.5, 0.5);

    std::cout <<"Hello Universe, I give a solution for the sawmill scheduling problem!";
    
    return 0;
}

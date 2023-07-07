#include <vector>
#include <iostream>

#include "GeneticAlgorithm.hpp"

struct Solution {
    std::vector<bool> genome;
    double fitness;
};

class KnapsackGA : public GeneticAlgorithm {
public:
    KnapsackGA(int populationSize, int generations, const std::vector<int>& values, const std::vector<int>& weights, int knapsackCapacity)
        : GeneticAlgorithm(populationSize, generations), values(values), weights(weights), knapsackCapacity(knapsackCapacity) {
        solutions.resize(populationSize);
    }

    Solution getBestSolution() {}

private:
    void initializePopulation() override {}

    void calculateFitness() override {}

    void selection() override {}

    void crossover() override {}

    void mutation() override {}

    std::vector<int> values;
    std::vector<int> weights;
    int knapsackCapacity;
    std::vector<Solution> solutions;
};


int main() {
    std::vector<int> values {10, 40, 50, 70};
    std::vector<int> weights {1, 3, 4, 5};
    int knapsackCapacity = 10;

    KnapsackGA knapsackGA(100, 200, values, weights, knapsackCapacity);

    std::cout <<"Hello Universe, I give a solution for the knapsack problem!";
    
    return 0;
}

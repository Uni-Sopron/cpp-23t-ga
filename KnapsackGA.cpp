#include <vector>
#include <iostream>
#include <random>

#include "GeneticAlgorithm.hpp"

struct Solution {
    std::vector<bool> itemSelection;
    double fitness;
};

class KnapsackGA : public GeneticAlgorithm {
public:
    KnapsackGA(int populationSize, int generations, const std::vector<int>& values, const std::vector<int>& weights, int knapsackCapacity)
        : GeneticAlgorithm(populationSize, generations), values(values), weights(weights), knapsackCapacity(knapsackCapacity) {
        solutions.resize(populationSize);
        initializePopulation();
    }

    Solution getBestSolution() {
        return solutions[0];
    }

private:
    void initializePopulation() override {
        for (int i = 0; i < solutions.size(); ++i) {
            solutions[i] = generateSolution();
        }
    }

    void calculateFitness() override {}

    void selection() override {}

    void crossover() override {}

    void mutation() override {}

    void sort() {}

    Solution generateSolution() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, 1);

        Solution solution;
        solution.itemSelection.resize(values.size());

        for (size_t i = 0; i < values.size(); ++i) {
            solution.itemSelection[i] = distr(gen);
        }

        solution.fitness = fitness(solution);
        return solution;
    }

    double fitness(Solution& solution) {
        int totalValue = 0;
        int totalWeight = 0;

        for (size_t i = 0; i < solution.itemSelection.size(); ++i) {
            if (solution.itemSelection[i]) {
                totalValue += values[i];
                totalWeight += weights[i];
            }
        }

        if (totalWeight <= knapsackCapacity) {
            return totalValue;
        } 
        return 0;
    }

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

    std::cout <<"\n\nBest solution: ";
    Solution bestSolution = knapsackGA.getBestSolution();
    for (size_t i = 0; i < bestSolution.itemSelection.size(); ++i) {
        std::cout << bestSolution.itemSelection[i] << " ";
    }
    std::cout <<"\nFitness: " << bestSolution.fitness <<"\n";
    
    return 0;
}

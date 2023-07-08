#include <vector>
#include <iostream>
#include <random>
#include <algorithm>

#include "GeneticAlgorithm.hpp"

struct Solution
{
    std::vector<bool> itemSelection;
    double fitness;
};

class KnapsackGA : public GeneticAlgorithm
{
public:
    KnapsackGA(int populationSize, int generations, int elitSize, double mutationRate, double crossoverRate, const std::vector<int> &values, const std::vector<int> &weights, int knapsackCapacity)
        : GeneticAlgorithm(populationSize, generations, elitSize, mutationRate, crossoverRate), values(values), weights(weights), knapsackCapacity(knapsackCapacity), distr(0, 1), distrInt(0, values.size() - 1)
    {
        solutions.resize(populationSize);
    }

    Solution getBestSolution() const
    {
        return solutions[0];
    }

private:
    void initializePopulation() override
    {
        for (int i = 0; i < solutions.size(); ++i)
        {
            solutions[i] = generateSolution();
        }
    }

    void calculateFitness() override
    {
        for (Solution &solution : solutions)
        {
            solution.fitness = fitness(solution);
        }
    }

    void selection() override
    {
        sort();
        solutions.resize(elitSize);
    }

    void crossover() override
    {
        for (size_t i = 0; i < elitSize; i += 2)
        {
            if (distr(gen) < crossoverRate)
            {
                int crossoverPoint = distrInt(gen);

                Solution child1;
                Solution child2;

                child1.itemSelection.insert(child1.itemSelection.end(), solutions[i].itemSelection.begin(), solutions[i].itemSelection.begin() + crossoverPoint);
                child1.itemSelection.insert(child1.itemSelection.end(), solutions[i + 1].itemSelection.begin() + crossoverPoint, solutions[i + 1].itemSelection.end());

                child2.itemSelection.insert(child2.itemSelection.end(), solutions[i + 1].itemSelection.begin(), solutions[i + 1].itemSelection.begin() + crossoverPoint);
                child2.itemSelection.insert(child2.itemSelection.end(), solutions[i].itemSelection.begin() + crossoverPoint, solutions[i].itemSelection.end());

                solutions.push_back(child1);
                solutions.push_back(child2);
            }
        }
    }

    void mutation() override
    {
        for (size_t i = elitSize; i < solutions.size(); ++i)
        {
            if (distr(gen) < mutationRate)
            {
                int mutationPoint = distrInt(gen);
                solutions[i].itemSelection[mutationPoint] = !solutions[i].itemSelection[mutationPoint];
            }
        }
    }

    void sort() override
    {
        std::sort(solutions.begin(), solutions.end(), [](const Solution &a, const Solution &b)
                  { return a.fitness > b.fitness; });
    }

    Solution generateSolution()
    {
        Solution solution;
        solution.itemSelection = std::vector<bool>(values.size(), false);

        for (size_t i = 0; i < values.size(); ++i)
        {
            solution.itemSelection[i] = distr(gen);
        }

        return solution;
    }

    double fitness(Solution &solution)
    {
        int totalValue = 0;
        int totalWeight = 0;

        for (size_t i = 0; i < solution.itemSelection.size(); ++i)
        {
            if (solution.itemSelection[i])
            {
                totalValue += values[i];
                totalWeight += weights[i];

                if (totalWeight > knapsackCapacity)
                {
                    return 0;
                }
            }
        }

        return totalValue;
    }

    std::vector<int> values;
    std::vector<int> weights;
    int knapsackCapacity;
    std::vector<Solution> solutions;

    std::random_device rd;
    std::mt19937 gen = std::mt19937(rd());
    std::uniform_int_distribution<> distr;
    std::uniform_int_distribution<> distrInt;
};

int main()
{
    std::vector<int> values{10, 40, 50, 70};
    std::vector<int> weights{1, 3, 4, 5};
    int knapsackCapacity = 10;

    KnapsackGA knapsackGA(100, 200, 20, 0.05, 0.7, values, weights, knapsackCapacity);

    knapsackGA.execute();

    std::cout << "Hello Universe, I give a solution for the knapsack problem!";

    std::cout << "\n\nBest solution: ";
    Solution bestSolution = knapsackGA.getBestSolution();
    for (size_t i = 0; i < bestSolution.itemSelection.size(); ++i)
    {
        std::cout << bestSolution.itemSelection[i] << " ";
    }
    std::cout << "\nFitness: " << bestSolution.fitness << "\n";

    return 0;
}

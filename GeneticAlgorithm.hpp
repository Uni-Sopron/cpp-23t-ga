#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int populationSize, int generations)
        : populationSize(populationSize), generations(generations) { }

    virtual ~GeneticAlgorithm() { }

    virtual void initializePopulation() = 0;

    virtual void calculateFitness() = 0;

    virtual void selection() = 0;

    virtual void crossover() = 0;

    virtual void mutation() = 0;

    virtual void* getBestSolution() = 0;

    void execute() {
        initializePopulation();
        for(int i = 0; i < generations; i++) {
            calculateFitness();
            selection();
            crossover();
            mutation();
        }
    }

protected:
    int populationSize;
    int generations;
};

#endif

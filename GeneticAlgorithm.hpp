#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int populationSize, int generations, int elitSize, double mutationRate, double crossoverRate)
        : populationSize(populationSize), generations(generations), elitSize(elitSize), mutationRate(mutationRate), crossoverRate(crossoverRate) { }

    virtual ~GeneticAlgorithm() { }

    virtual void initializePopulation() = 0;

    virtual void calculateFitness() = 0;

    virtual void selection() = 0;

    virtual void crossover() = 0;

    virtual void mutation() = 0;

    void execute() {
        initializePopulation();
        for(int i = 0; i < generations; i++) {
            calculateFitness();
            selection();
            crossover();
            mutation();
            calculateFitness();
            sort();
        }
    }

    virtual void sort() = 0;

protected:
    int populationSize;
    int generations;
    int elitSize;
    double mutationRate;
    double crossoverRate;
};

#endif

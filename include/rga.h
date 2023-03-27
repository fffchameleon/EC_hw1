#ifndef RGA_H 
#define RGA_H 
#include <bits/stdc++.h>
using namespace std;

class R_GA
{
private:
    int POPULATION_SIZE = 100;
    int MAX_ITERATIONS = 100;
    double MUTATION_RATE = 0.01;

    struct Individual {
        vector<double> genes;
        double fitness;
    };
public:
    R_GA();
    vector<Individual> initialize_population(int gene_length);
    double evaluate_fitness(Individual& individual);
    int roulette_wheel_selection(vector<Individual>& population);
    void crossover(vector<Individual>& population, int parent1_index);
    ~R_GA();
};


#endif 
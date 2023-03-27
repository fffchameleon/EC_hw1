#ifndef GA_H
#define GA_H
#include <bits/stdc++.h>
using namespace std;

static const int POPULATION_SIZE = 100;

template <typename T>
class GA {
private:
    int crossover_n_point;
    int population_size, times;
    double crossover_prob, mutation_rate;
    static constexpr int dim_n = 10;

    struct Individual {
        vector<T> genes;
        double fitness;
        Individual() : genes(dim_n) {}
    };

public:
    GA(int crossover = 2, int pop_size = 100, int t = 500,
        double cross_prob = 0.9, double mut_rate = 0.1) {
        crossover_n_point = crossover;
        population_size = pop_size, times = t;
        crossover_prob = cross_prob, mutation_rate = mut_rate;
    }

    vector<Individual> initialize_population(int dim);
    // Modify the following methods to handle real values
    // double get_xi(T& gene);
    // int bit2int(T& gene);
    void evaluate_fitness(Individual& individual);

    pair<int, int> generate_range(int range);
    vector<Individual> crossover_2point(vector<Individual>& population);

    void mutate(vector<Individual>& individual);

    vector<Individual> survivor_selection(vector<Individual>& population, vector<Individual>& next_gen);

    double get_best_individual(vector<Individual>& population, int id);

    void print_population(vector<Individual>& population);

    void evolution();

    GA();
};

#endif

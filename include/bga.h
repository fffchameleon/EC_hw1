#ifndef BGA_H 
#define BGA_H 
#include <bits/stdc++.h>
using namespace std;

class B_GA
{
private:
    int crossover_n_point;
    int population_size, times;
    double crossover_prob, mutation_rate;
    static constexpr int dim_n = 10;
    static constexpr int gene_length = 10;
    
    struct Individual {
        vector<bitset<gene_length>> genes;
        double fitness;
        Individual() : genes(dim_n) {}
    };
public:
    B_GA(int crossover = 2, int pop_size = 100, int t = 500,
        double cross_prob = 0.9, double mut_rate = 0.1) {
        crossover_n_point = crossover;
        population_size = pop_size, times = t;
        crossover_prob = cross_prob, mutation_rate = mut_rate;
        
        // if(dim < 1)  throw invalid_argument("Schwefel Function must have minimum 1 dimension, " + to_string(dim) + " requested");
    }

    vector<Individual> initialize_population(int dim);
    double get_xi(bitset<gene_length>& gene);
    int bit2int(bitset<gene_length>& gene);
    void evaluate_fitness(Individual& individual);
    
    vector<Individual> crossover(vector<Individual>& population, bool is_uniform);
    
    void mutate(vector<Individual>& individual);
    
    vector<Individual> survivor_selection(vector<Individual>& population, vector<Individual>& next_gen);

    double get_best_individual(vector<Individual>& population, int id);
    
    void print_population(vector<Individual>& population);

    void evolution();

    ~B_GA();
};


#endif 

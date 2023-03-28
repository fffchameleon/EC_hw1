#ifndef BGA_H 
#define BGA_H 

#include <vector>
#include <bitset>
#include <tuple>
#include <iostream>

class B_GA
{
private:
    int crossover_n_point;
    int population_size, times;
    double crossover_prob, mutation_rate;
    static constexpr int dim_n = 10;
    static constexpr int gene_length = 10;
    
    struct Individual {
        std::vector<std::bitset<gene_length>> genes;
        double fitness;
        Individual() : genes(dim_n) {}
    };
public:
    B_GA(int crossover = 2, int pop_size = 100, int t = 500,
        double cross_prob = 0.9, double mut_rate = 0.1) {
        crossover_n_point = crossover;
        population_size = pop_size, times = t;
        crossover_prob = cross_prob, mutation_rate = mut_rate;
    }

    std::vector<Individual> initialize_population(int dim);
    double get_xi(std::bitset<gene_length>& gene);
    int bit2int(std::bitset<gene_length>& gene);
    void evaluate_fitness(Individual& individual);
    
    std::vector<Individual> crossover(std::vector<Individual>& population, bool is_uniform);
    
    void mutate(std::vector<Individual>& individual);
    
    std::vector<Individual> survivor_selection(std::vector<Individual>& population, std::vector<Individual>& next_gen);

    double get_best_individual(std::vector<Individual>& population, int id);
    
    void print_population(std::vector<Individual>& population);

    void evolution();

    ~B_GA();
};


#endif 

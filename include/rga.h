#ifndef RGA_H 
#define RGA_H 
#include <vector>
#include <tuple>
class R_GA
{
private:
    int crossover_n_point;
    int population_size, times;
    double crossover_prob, mutation_rate;
    static constexpr int dim_n = 10;
    static constexpr int gene_length = 10;
    
    struct Individual {
        std::vector<double> genes;
        double fitness;
        Individual() : genes(dim_n) {}
    };
public:
    R_GA(int crossover = 2, int pop_size = 100, int t = 500,
        double cross_prob = 0.9, double mut_rate = 0.1) {
        crossover_n_point = crossover;
        population_size = pop_size, times = t;
        crossover_prob = cross_prob, mutation_rate = mut_rate;
    }

    std::vector<Individual> initialize_population(int dim);
    void evaluate_fitness(Individual& individual);
    
    std::vector<Individual> crossover(std::vector<Individual>& population, bool is_uniform);
    
    void mutate(std::vector<Individual>& individual);
    
    std::vector<Individual> survivor_selection(std::vector<Individual>& population, std::vector<Individual>& next_gen);

    double get_best_individual(std::vector<Individual>& population, int id);
    
    void print_population(std::vector<Individual>& population);

    void evolution();

    ~R_GA();
};


#endif 

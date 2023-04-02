#ifndef RGA_H 
#define RGA_H 

#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

/**
 * @brief Real-valued Genetic Algorithm (R_GA) class
 */
class R_GA
{
private:
    /**
     * @brief The Individual struct represents an individual in the population, which means a solution xi for SCH function.
     */
    static constexpr int dim_n = 10;
    struct Individual {
        vector<double> genes;
        double fitness;
        Individual() : genes(dim_n) {}
    };
public:
    /**
     * @brief R_GA constructor
     */
    R_GA() {}

    /**
     * @brief Initialize the population with random individuals.
     * @param dim The dimension of the SCH problem.
     * @return A vector containing the initialized population.
     */
    vector<Individual> initialize_population(int dim);

    /**
     * @brief Evaluate the fitness of an individual.
     * @param individual The individual to evaluate.
     */
    void evaluate_fitness(Individual& individual);
    
    /**
     * @brief Selects a pair of parents from the given population.
     * @param selected A vector of bool values indicating if an individual is already selected as a parent.
     * @param population The population from this generation.
     * @return A pair of selected parent individuals.
     */
    pair<Individual, Individual> parent_selection(vector<bool>& selected, vector<Individual>& population);

    /**
     * @brief Perform crossover operation on the given population.
     * @param population The population to perform crossover on.
     * @param is_uniform A flag to determine if uniform crossover is used.
     * @return A vector containing the offspring generated through crossover.
     */
    vector<Individual> crossover(vector<Individual>& population, bool is_uniform);
    
    /**
     * @brief Perform mutation operation on the given population.
     * @param population The population to perform mutation on.
     */
    void mutate(vector<Individual>& population);
    
    /**
     * @brief Perform survivor selection on the given population and offspring.
     * @param population The population to select survivors from.
     * @param offspring The offspring to select survivors from.
     * @return A vector containing the selected survivors.
     */
    vector<Individual> survivor_selection(vector<Individual>& population, vector<Individual>& offspring);

    /**
     * @brief Get the best fitness value from the given population.
     * @param population The population to get the best fitness value from.
     * @param id The generation id (for detail output).
     * @return The best fitness value.
     */
    double get_best_fitness(vector<Individual>& population, int id);
    
    /**
     * @brief Perform the genetic algorithm evolution.
     */
    void evolution();

    /**
     * @brief Print the population for debugging purposes.
     * @param population The population to print.
     */
    void print_population(vector<Individual>& population) {
        for(auto i : population) {
            for(auto j : i.genes) 
                cout << j << " ";
            cout << "\n";
        }
    }

    /**
     * @brief R_GA destructor
     */
    ~R_GA() {}
};


#endif 
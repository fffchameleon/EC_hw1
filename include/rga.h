#ifndef RGA_H 
#define RGA_H 

#include <iostream>
#include <vector>
#include <bitset>

using namespace std;
class R_GA
{
private:
    static constexpr int dim_n = 100;
    struct Individual {
        vector<double> genes;
        double fitness;
        Individual() : genes(dim_n) {}
    };
public:
    R_GA() {}

    vector<Individual> initialize_population(int dim);
    void evaluate_fitness(Individual& individual);
    
    pair<Individual, Individual> parent_selection(vector<bool>& selected, vector<Individual>& population);
    vector<Individual> crossover(vector<Individual>& population, bool is_uniform);
    
    void mutate(vector<Individual>& population);
    
    vector<Individual> survivor_selection(vector<Individual>& population, vector<Individual>& offspring);

    double get_best_fitness(vector<Individual>& population, int id);
    
    void evolution();

    // debug using
    void print_population(vector<Individual>& population) {
        for(auto i : population) {
            for(auto j : i.genes) 
                cout << j << " ";
            cout << "\n";
        }
    }
    ~R_GA() {}
};


#endif 
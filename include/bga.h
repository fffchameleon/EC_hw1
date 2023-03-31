#ifndef BGA_H 
#define BGA_H 

#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

class B_GA
{
private:
    int n_point;
    static constexpr int gene_length = 10;
    static constexpr int dim_n = 100;
    
    struct Individual {
        vector<bitset<gene_length>> genes;
        double fitness;
        Individual() : genes(dim_n) {}
    };
public:
    B_GA(int n = 2){
        n_point = n;
    }

    vector<Individual> initialize_population(int dim);
    double get_xi(bitset<gene_length>& gene);
    int bit2int(bitset<gene_length>& gene);
    void evaluate_fitness(Individual& individual);
    
    pair<Individual, Individual> parent_selection(vector<bool>& selected, vector<Individual>& population);
    vector<Individual> crossover(vector<Individual>& population, bool is_uniform);
    
    void mutate(vector<Individual>& population);
    
    vector<Individual> survivor_selection(vector<Individual>& population, vector<Individual>& offspring);

    double get_best_fitness(vector<Individual>& population, int id);
    
    // debug using
    void print_population(vector<Individual>& population) {
        for(auto i : population) {
            for(auto j : i.genes) 
                cout << get_xi(j) << " ";
            cout << "\n";
        }
    }
    
    void evolution();

    ~B_GA() {}
};


#endif 
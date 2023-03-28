#include "include/bga.h"
#include "include/global.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

vector<B_GA::Individual> B_GA::initialize_population(int dim) {
    int p_size = population_size;
    vector<Individual> ret(p_size);
    for (int i = 0; i < p_size; i++) {
        Individual tmp;
        for(int j = 0; j < dim; j++) {
            for(int k = 0; k < gene_length; k++) {
                if(rand_int(0, 1))    tmp.genes[j].set(k);
            }
        }
        evaluate_fitness(tmp);
        ret[i] = tmp;
    }
    return ret;
}

double B_GA::get_xi(bitset<gene_length>& gene) {
    int val = bit2int(gene);
    return val * sin(sqrt(abs(val)));
}

int B_GA::bit2int(bitset<gene_length>& gene) {
    bool sign = gene.test(gene_length - 1);
    
    bitset<gene_length> tmp = gene;
    
    if(!sign) return tmp.to_ulong();
    else return (-1)* (tmp.flip().to_ulong() + 1);
}


void B_GA::evaluate_fitness(Individual& individual) {
    double fit = 418.98291 * dim_n;
    for(int i = 0; i < dim_n; i++) {
        fit -= get_xi(individual.genes[i]);
    }
    individual.fitness = fit;
}

vector<B_GA::Individual> B_GA::crossover(vector<Individual>& population, bool is_uniform) {
    vector<bool> selected(population_size, false);
    vector<Individual> ret;
    double tmp = rand_real(0, 1);
    if(tmp > crossover_prob) 
        return population;
    // parent selection
    int t = population_size / crossover_n_point;
    Individual parent1, parent2, offspring1, offspring2;
    while(t) {
        int parent1_idx, parent2_idx;
        while(1) {
            tie(parent1_idx, parent2_idx) = generate_range(population_size-1);
            if(!selected[parent1_idx] && !selected[parent2_idx]) {
                t--;
                selected[parent1_idx] = true;
                selected[parent2_idx] = true;
                break;
            }
        }
        
        parent1 = population[parent1_idx], parent2 = population[parent2_idx];
        // flag true when 2-point crossover, false when uniform crossover
        if(!is_uniform) {
            auto [l, r] = generate_range(gene_length - 1);
            offspring1 = parent1, offspring2 = parent2;

            for(int i = l; i < r; i++) {
                bitset<gene_length> tmp;
                tmp = offspring1.genes[i];
                offspring1.genes[i] = offspring2.genes[i];
                offspring2.genes[i] = tmp;
            }
        } else {    // better (compare to each bit uniform)
            offspring1 = parent1, offspring2 = parent2;
            for(int i = 0; i < dim_n; i++) {
                if(rand_int(0, 1) > 0.5) {
                    offspring1.genes[i] = parent2.genes[i];
                    offspring2.genes[i] = parent1.genes[i];
                }
            }

            // for(int i = 0; i < dim_n; i++) {
            //     bitset<gene_length> mask1, mask2;
            //     for(int j = 0; j < gene_length; j++) {
            //         if(rand_real(0, 1) > 0.5)   mask1.set(j);
            //         else                        mask1.reset(j);
            //     }
            //     mask2 = mask1;  mask2.flip();
            //     offspring1.genes[i] = (mask1 & parent1.genes[i]) | (mask2 & parent2.genes[i]);
            //     offspring2.genes[i] = (mask2 & parent1.genes[i]) | (mask1 & parent2.genes[i]);
            // }
        }
        ret.emplace_back(offspring1);
        ret.emplace_back(offspring2);
    }
    for(auto &i : ret)
        evaluate_fitness(i);
    return ret;

}

void B_GA::mutate(vector<Individual>& population) {
    for(auto& i : population) {
        for(auto& j : i.genes) {
            for(int k = 0; k < gene_length; k++) {
                double tmp = rand_real(0, 1);
                if(tmp < mutation_rate) {
                    j.flip(k);
                }
            }
        }
        evaluate_fitness(i);
    }
}

vector<B_GA::Individual> B_GA::survivor_selection(vector<Individual>& population, vector<Individual>& next_generation) {
    population.insert(population.end(), next_generation.begin(), next_generation.end());
    sort(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
        return a.fitness < b.fitness;}
    ); // increasing
    vector<Individual> ret;
    for(int i = 0; i < POPULATION_SIZE; i++) 
        ret.emplace_back(population[i]);

    population_size = ret.size();
    return ret;
}

double B_GA::get_best_individual(vector<Individual>& population, int id) {
    auto it = min_element(population.begin(), population.end(),
                          [](const Individual& a, const Individual& b) {
                              return a.fitness < b.fitness;
                          });
    if((*it).fitness < 1 || id == times - 1) {
        for(auto j : (*it).genes) 
            cout << bit2int(j) << " ";
        cout << "\n";
    }
    return (*it).fitness;
}

void B_GA::print_population(vector<Individual>& population) {
    for(auto i : population) {
        for(auto j : i.genes) 
            cout << get_xi(j) << " ";
        cout << "\n";
    }
}

void B_GA::evolution() {
    vector<Individual> offspring, population;
    
    for(int i = 0; i < times; i++) {
        if(i == 0)
            population = initialize_population(dim_n);
        offspring = crossover(population, true);
        mutate(population);
        population = survivor_selection(population, offspring);

        double best = get_best_individual(population, i);
        bga_fit.push_back(best);
        if((i % 50) == 0) cout << "In " << i+1 << "th generation, the best fitness is: " << best << "\n";  
        else if (best < 0.1) {
            cout << "In " << i+1 << "th generation, the fitness " << best << "lower than 0.1\n";
            break;
        }
    }
    
    return;
}
#include "../include/bga.h"
#include "../include/global.h"

#include <cstdlib>
#include <cmath>
#include <algorithm>

std::vector<B_GA::Individual> B_GA::initialize_population(int dim) {
    int p_size = population_size;
    std::vector<Individual> ret(p_size);
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

double B_GA::get_xi(std::bitset<gene_length>& gene) {
    int val = bit2int(gene);
    return val * sin(sqrt(abs(val)));
}

int B_GA::bit2int(std::bitset<gene_length>& gene) {
    bool sign = gene.test(gene_length - 1);
    
    std::bitset<gene_length> tmp = gene;
    
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

std::vector<B_GA::Individual> B_GA::crossover(std::vector<Individual>& population, bool is_uniform) {
    std::vector<bool> selected(population_size, false);
    std::vector<Individual> ret;
    double tmp = rand_real(0, 1);
    if(tmp > crossover_prob) 
        return population;
    // parent selection
    int t = population_size / crossover_n_point;
    Individual parent1, parent2, offspring1, offspring2;
    while(t) {
        int parent1_idx, parent2_idx;
        while(1) {
            std::tie(parent1_idx, parent2_idx) = generate_range(population_size-1);
            if(!selected[parent1_idx] && !selected[parent2_idx]) {
                t--;
                selected[parent1_idx] = true;
                selected[parent2_idx] = true;
                break;
            }
        }
        
        // crossover, flag true when 2-point crossover, false when uniform crossover
        parent1 = population[parent1_idx], parent2 = population[parent2_idx];

        if(!is_uniform) {
            auto [l, r] = generate_range(gene_length - 1);
            offspring1 = parent1, offspring2 = parent2;

            for(int i = l; i < r; i++) {
                std::bitset<gene_length> tmp;
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

void B_GA::mutate(std::vector<Individual>& population) {
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

std::vector<B_GA::Individual> B_GA::survivor_selection(std::vector<Individual>& population, std::vector<Individual>& next_generation) {
    population.insert(population.end(), next_generation.begin(), next_generation.end());
    sort(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
        return a.fitness < b.fitness;}
    ); // increasing
    std::vector<Individual> ret;
    for(int i = 0; i < POPULATION_SIZE; i++) 
        ret.emplace_back(population[i]);

    population_size = ret.size();
    return ret;
}

double B_GA::get_best_individual(std::vector<Individual>& population, int id) {
    auto it = std::min_element(population.begin(), population.end(),
                          [](const Individual& a, const Individual& b) {
                              return a.fitness < b.fitness;
                          });
    if((*it).fitness < 1 || id == times - 1) {
        for(auto j : (*it).genes) 
            std::cout << bit2int(j) << " ";
        std::cout << "\n";
    }
    return (*it).fitness;
}

// debug using
void B_GA::print_population(std::vector<Individual>& population) {
    for(auto i : population) {
        for(auto j : i.genes) 
            std::cout << get_xi(j) << " ";
        std::cout << "\n";
    }
}

void B_GA::evolution() {
    std::vector<Individual> offspring, population;
    
    for(int i = 0; i < times; i++) {
        if(i == 0)
            population = initialize_population(dim_n);
        offspring = crossover(population, true);
        mutate(population);
        population = survivor_selection(population, offspring);

        double best = get_best_individual(population, i);
        bga_fit.push_back(best);
        if((i % 50) == 0) std::cout << "In " << i+1 << "th generation, the best fitness is: " << best << "\n";  
        else if (best < 0.1) {
            std::cout << "In " << i+1 << "th generation, the fitness " << best << "lower than 0.1\n";
            break;
        }
    }
    
    return;
}
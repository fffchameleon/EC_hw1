#include "../include/rga.h"
#include "../include/global.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>

std::vector<R_GA::Individual> R_GA::initialize_population(int dim) {
    int p_size = population_size;
    std::vector<Individual> ret(p_size);
    for (int i = 0; i < p_size; i++) {
        Individual tmp;
        for(int j = 0; j < dim; j++) {
            tmp.genes[j] = rand_real(lower, upper);
        }
        evaluate_fitness(tmp);
        ret[i] = tmp;
    }
    return ret;
}

void R_GA::evaluate_fitness(Individual& individual) {
    double fit = 418.98291 * dim_n;
    for(int i = 0; i < dim_n; i++) {
        double val = individual.genes[i];
        fit -= ( val * sin(sqrt(abs(val))) );
    }
    individual.fitness = fit;
}

std::vector<R_GA::Individual> R_GA::crossover(std::vector<Individual>& population, bool is_uniform) {
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
        
        // crossover, flag true when whole arithmetic crossover, false when uniform crossover
        parent1 = population[parent1_idx], parent2 = population[parent2_idx];
        
        if(!is_uniform) {
            auto [l, r] = generate_range(gene_length - 1);
            offspring1 = parent1, offspring2 = parent2;
            double alpha = generate_alpha(1);
            for(int i = 0; i < dim_n; i++) {
                offspring1.genes[i] = (parent1.genes[i] * alpha) + (parent2.genes[i] * (1-alpha));
                offspring2.genes[i] = (parent2.genes[i] * alpha) + (parent1.genes[i] * (1-alpha));
            }
            
        } else {
            offspring1 = parent1, offspring2 = parent2;
            for(int i = 0; i < dim_n; i++) {
                if(rand_real(0, 1) > 0.5) {
                    offspring1.genes[i] = parent2.genes[i];
                    offspring2.genes[i] = parent1.genes[i];
                }
            }
        }
        ret.emplace_back(offspring1);
        ret.emplace_back(offspring2);
    }
    for(auto &i : ret)
        evaluate_fitness(i);
    return ret;

}

void R_GA::mutate(std::vector<Individual>& population) {
    for(auto& i : population) {
        for(auto& j : i.genes) {
            double tmp = rand_real(0, 1);
            if(tmp < mutation_rate) {
                j = rand_real(lower, upper);
            }
        }
        evaluate_fitness(i);
    }
}

std::vector<R_GA::Individual> R_GA::survivor_selection(std::vector<Individual>& population, std::vector<Individual>& next_generation) {
    population.insert(population.end(), next_generation.begin(), next_generation.end());
    std::sort(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
        return a.fitness < b.fitness;}
    ); // increasing
    std::vector<Individual> ret;
    for(int i = 0; i < POPULATION_SIZE; i++) 
        ret.emplace_back(population[i]);

    population_size = ret.size();
    return ret;
}

double R_GA::get_best_individual(std::vector<Individual>& population, int id) {
    auto it = std::min_element(population.begin(), population.end(),
                          [](const Individual& a, const Individual& b) {
                              return a.fitness < b.fitness;
                          });
    if((*it).fitness == 0 || id == times - 1) {
        for(auto j : (*it).genes) 
            std::cout << j << " ";
        std::cout << "\n";
    }
    return (*it).fitness;
}

// debug using
void R_GA::print_population(std::vector<Individual>& population) {
    for(auto i : population) {
        for(auto j : i.genes) 
            std::cout << j << " ";
        std::cout << "\n";
    }
}
void R_GA::evolution() {
    std::vector<Individual> offspring, population;
    
    for(int i = 0; i < times; i++) {
        if(i == 0)
            population = initialize_population(dim_n);
        offspring = crossover(population, true);
        mutate(population);
        population = survivor_selection(population, offspring);

        double best = get_best_individual(population, i);
        rga_fit.push_back(best);
        if((i % 50) == 0) std::cout << "In " << i+1 << "th generation, the best fitness is: " << best << "\n";  
        else if (best == 0) {
            std::cout << "In " << i+1 << "th generation, the fitness " << best << "lower than 0.1\n";
            break;
        }
    }

    return;
}
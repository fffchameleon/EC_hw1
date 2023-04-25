#include "../include/rga.h"
#include "../include/global.h"

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <ctime>
using namespace std;

vector<R_GA::Individual> R_GA::initialize_population(int dim) {
    vector<Individual> ret(POPULATION_SIZE);
    for (int i = 0; i < POPULATION_SIZE; i++) {
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

// pair<R_GA::Individual, R_GA::Individual> R_GA::parent_selection(vector<bool>& selected, vector<Individual>& population) {
pair<R_GA::Individual, R_GA::Individual> R_GA::parent_selection(vector<Individual>& population) {
    vector<int> parent_candidate;
    int p = p_select;
    vector<bool> candidate(POPULATION_SIZE, false);
    while(p) {
        int candidate_i = rand_int(0, POPULATION_SIZE-1);
        if(!candidate[candidate_i]) {
            p--;
            candidate[candidate_i] = true;
            parent_candidate.emplace_back(candidate_i);
        }
    }

    auto first_min_it = std::min_element(parent_candidate.begin(), parent_candidate.end(),
        [&](int a, int b) { return population[a].fitness < population[b].fitness; });
    int first_min_id = *first_min_it;
    parent_candidate.erase(first_min_it);
    

    auto second_min_it = std::min_element(parent_candidate.begin(), parent_candidate.end(),
        [&](int a, int b) { return population[a].fitness < population[b].fitness; });
    int second_min_id = *second_min_it;
    return {population[first_min_id], population[second_min_id]};
}

vector<R_GA::Individual> R_GA::crossover(vector<Individual>& population, bool is_uniform) {
    if(rand_real(0, 1) > pc) 
        return population;

    vector<Individual> offspring;
    
    // parent selection
    int t = POPULATION_SIZE;
    Individual parent1, parent2, offspring1, offspring2;
    while(t--) {
        auto [parent1, parent2] = parent_selection(population);

        if(!is_uniform) {  // whole arithmetic
            offspring1 = parent1, offspring2 = parent2;
            double alpha = generate_alpha(1);
            for(int i = 0; i < dim_n; i++) {
                offspring1.genes[i] = (parent1.genes[i] * alpha) + (parent2.genes[i] * (1.0 - alpha));
                offspring2.genes[i] = (parent2.genes[i] * alpha) + (parent1.genes[i] * (1.0 - alpha));
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
        offspring.emplace_back(offspring1);
        offspring.emplace_back(offspring2);
    }
    for(auto &i : offspring)
        evaluate_fitness(i);
    return offspring;

}

void R_GA::mutate(vector<Individual>& population) {
    bool has_mutate = false;
    for(auto& i : population) {
        for(auto& j : i.genes) {
            if(rand_real(0, 1) < pm) {
                has_mutate = true;
                j = rand_real(lower, upper);
            }
        }
        if(has_mutate)  evaluate_fitness(i);
        has_mutate = false;
    }
}

vector<R_GA::Individual> R_GA::survivor_selection(vector<Individual>& population, vector<Individual>& offspring) {
    population.insert(population.end(), offspring.begin(), offspring.end());
    sort(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
        return a.fitness < b.fitness;}
    ); // increasing
    vector<Individual> survivor(population.begin(), population.begin() + POPULATION_SIZE);

    return survivor;
}

double R_GA::get_best_fitness(vector<Individual>& population, int id) {
    
    auto it = min_element(population.begin(), population.end(),
                          [](const Individual& a, const Individual& b) {
                              return a.fitness < b.fitness;
                          });

    if(detail && id == term - 1) {
        cout << "In " << id+1 << "th generation, the best fitness is: " << (*it).fitness << "\nWhen xi are, \n";  
        for(auto j : (*it).genes) 
            cout << j << " ";
        cout << "\n";
    }
    return (*it).fitness;
}

void R_GA::evolution() {
    vector<Individual> offspring, population;

    for(int i = 0; i < term; i++) {
        if(i == 0)
            population = initialize_population(dim_n);
        offspring = crossover(population, is_uniform);
        mutate(offspring);
        population = survivor_selection(population, offspring);
        double best = get_best_fitness(population, i);
        rga_fit[i] += best;

        if(detail && (i % 100 == 0)) cout << "In " << i+1 << "th generation, the best fitness is: " << best << "\n";  
    }

    return;
}
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

pair<R_GA::Individual, R_GA::Individual> R_GA::parent_selection(vector<bool>& selected, vector<Individual>& population) {
    vector<int> parent_candidate;
    int p = p_select;
    while(p) {
        vector<bool> candidate(POPULATION_SIZE, false);

        int candidate_i = rand_int(0, POPULATION_SIZE-1);
        if(!candidate[candidate_i] && !selected[candidate_i]) {
            p--;
            candidate[candidate_i] = true;
            parent_candidate.emplace_back(candidate_i);
        }
    }

    int first_min_id = -1;
    int second_min_id = -1;
    double first_min_fitness = std::numeric_limits<double>::max();
    double second_min_fitness = std::numeric_limits<double>::max();

    for (int id : parent_candidate) {
        if (population[id].fitness < first_min_fitness) {
            second_min_fitness = first_min_fitness;
            second_min_id = first_min_id;
            first_min_fitness = population[id].fitness;
            first_min_id = id;
        } else if (population[id].fitness < second_min_fitness) {
            second_min_fitness = population[id].fitness;
            second_min_id = id;
        }
    }
    selected[first_min_id] = true;
    selected[second_min_id] = true;
    return {population[first_min_id], population[second_min_id]};
}

vector<R_GA::Individual> R_GA::crossover(vector<Individual>& population, bool is_uniform) {
    if(rand_real(0, 1) > cross_prob) 
        return population;

    vector<bool> selected(POPULATION_SIZE, false);
    vector<Individual> offspring;
    
    // parent selection
    int t = POPULATION_SIZE / 2;
    Individual parent1, parent2, offspring1, offspring2;
    while(t--) {
        tie(parent1, parent2) = parent_selection(selected, population);

        if(!is_uniform) {  // whole arithmetic
            offspring1 = parent1, offspring2 = parent2;
            // double alpha = generate_alpha(1);
            double alpha = rand_real(0, 1);
            for(int i = 0; i < dim_n; i++) {
                offspring1.genes[i] = (parent1.genes[i] * alpha) + (parent2.genes[i] * (1-alpha));
                offspring2.genes[i] = (parent2.genes[i] * alpha) + (parent1.genes[i] * (1-alpha));
                offspring1.genes[i] = max(min(offspring1.genes[i], double(upper)), double(lower));
                offspring2.genes[i] = max(min(offspring2.genes[i], double(upper)), double(lower));
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
            if(rand_real(0, 1) < mut_prob) {
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

    vector<Individual> survivor;
    for(int i = 0; i < POPULATION_SIZE; i++) 
        survivor.emplace_back(population[i]);

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
        mutate(population);
        population = survivor_selection(population, offspring);

        double best = get_best_fitness(population, i);
        rga_fit[i] += best;

        if(detail && (i % 100 == 0)) cout << "In " << i+1 << "th generation, the best fitness is: " << best << "\n";  
    }

    return;
}
#include "../include/bga.h"
#include "../include/global.h"

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <queue>

vector<B_GA::Individual> B_GA::initialize_population(int dim) {
    vector<Individual> ret(POPULATION_SIZE);
    for (int i = 0; i < POPULATION_SIZE; i++) {
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

// pair<B_GA::Individual, B_GA::Individual> B_GA::parent_selection(vector<bool>& selected, vector<Individual>& population) {
pair<B_GA::Individual, B_GA::Individual> B_GA::parent_selection(vector<Individual>& population) {
    vector<int> parent_candidate;
    int p = p_select;
    while(p) {
        vector<bool> candidate(POPULATION_SIZE, false);

        int candidate_i = rand_int(0, POPULATION_SIZE-1);
        // if(!candidate[candidate_i] && !selected[candidate_i]) {
        if(!candidate[candidate_i]) {
            p--;
            candidate[candidate_i] = true;
            parent_candidate.emplace_back(candidate_i);
        }
    }

    auto first_min_it = std::min_element(parent_candidate.begin(), parent_candidate.end(),
        [&](int a, int b) { return population[a].fitness < population[b].fitness; });
    int first_min_id = *first_min_it;
    // selected[first_min_id] = true;
    parent_candidate.erase(first_min_it);
    

    auto second_min_it = std::min_element(parent_candidate.begin(), parent_candidate.end(),
        [&](int a, int b) { return population[a].fitness < population[b].fitness; });
    int second_min_id = *second_min_it;
    // selected[second_min_id] = true;
    return {population[first_min_id], population[second_min_id]};
}

vector<B_GA::Individual> B_GA::crossover(vector<Individual>& population, bool is_uniform) {
    if(rand_real(0, 1) > cross_prob) 
        return population;

    // vector<bool> selected(POPULATION_SIZE, false);
    vector<Individual> offspring;

    // parent selection
    // int t = POPULATION_SIZE / 2;
    int t = POPULATION_SIZE;
    Individual parent1, parent2, offspring1, offspring2;
    while(t--) {
        // auto [parent1, parent2] = parent_selection(selected, population);
        auto [parent1, parent2] = parent_selection(population);
        if(!is_uniform) {  // n-point crossover
            vector<int> crossover_points = generate_crossover_points(n_point, 1, gene_length - 1);
            offspring1 = parent1, offspring2 = parent2;

            bool swap_flag = false;
            int point_idx = 0;
            for(int i = 0; i < gene_length; i++) {
                if(point_idx < n_point && i == crossover_points[point_idx]) {
                    swap_flag = !swap_flag;
                    point_idx++;
                }
                if(swap_flag) {
                    bitset<gene_length> tmp;
                    tmp = offspring1.genes[i];
                    offspring1.genes[i] = offspring2.genes[i];
                    offspring2.genes[i] = tmp;
                }
            }
        } else {    // better (compare to each bit uniform)
            offspring1 = parent1, offspring2 = parent2;
            for(int i = 0; i < dim_n; i++) {
                if(rand_int(0, 1) > 0.5) {
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

void B_GA::mutate(vector<Individual>& population) {
    bool has_mutate = false;
    for(auto& i : population) {
        for(auto& j : i.genes) {
            for(int k = 0; k < gene_length; k++) {
                if(rand_real(0, 1) < mut_prob) {
                    has_mutate = true;
                    j.flip(k);
                }
            }
        }
        if(has_mutate)  evaluate_fitness(i);
        has_mutate = false;
    }
}

vector<B_GA::Individual> B_GA::survivor_selection(vector<Individual>& population, vector<Individual>& offspring) {
    population.insert(population.end(), offspring.begin(), offspring.end());
    sort(population.begin(), population.end(), [](const Individual& a, const Individual& b) {
        return a.fitness < b.fitness;}
    ); // increasing

    vector<Individual> survivor;
    for(int i = 0; i < POPULATION_SIZE; i++) 
        survivor.emplace_back(population[i]);

    return survivor;
}

double B_GA::get_best_fitness(vector<Individual>& population, int id) {
    auto it = min_element(population.begin(), population.end(),
                          [](const Individual& a, const Individual& b) {
                              return a.fitness < b.fitness;
                          });

    if(detail && (id == term - 1)) {
        cout << "In " << id+1 << "th generation, the best fitness is: " << (*it).fitness << "\nWhen xi are, \n"; 
        for(auto j : (*it).genes) 
            cout << bit2int(j) << " ";
        cout << "\n";
    }
    return (*it).fitness;
}


void B_GA::evolution() {
    vector<Individual> offspring, population;
    
    for(int i = 0; i < term; i++) {
        if(i == 0)
            population = initialize_population(dim_n);
        offspring = crossover(population, is_uniform);
        mutate(population);
        population = survivor_selection(population, offspring);

        double best = get_best_fitness(population, i);
        bga_fit[i] += best;
        if(detail) if((i % 100 == 0) && i != term-1)  cout << "In " << i+1 << "th generation, the best fitness is: " << best << "\n";  
    }
    
    return;
}

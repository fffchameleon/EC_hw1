#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include <map>

extern std::map<std::string, std::string> values;
extern int p_select;
extern int POPULATION_SIZE;
extern double cross_prob;
extern double mut_prob;
extern int trial;
extern int term;
extern bool is_uniform;
extern bool binary;
extern bool real;

extern const int lower;
extern const int upper;
extern std::vector<double> bga_fit;
extern std::vector<double> rga_fit;

void initialize(int argc, char* argv[]);
std::vector<int> generate_crossover_points(int n, int min_val, int max_val);
int rand_int(int min, int max);
double rand_real(double min, double max);
double generate_alpha(int up);
void write_to_file(const std::vector<double>& binary_data, const std::vector<double>& real_data, const std::string& filename);
void write_to_file(const std::vector<double>& binary_data, const std::vector<double>& real_data, const std::string& filename);
#endif 

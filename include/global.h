#ifndef GLOBAL_H
#define GLOBAL_H

#include <random>
#include <utility>
#include <vector>

extern const int POPULATION_SIZE;
extern const int lower;
extern const int upper;
extern std::vector<double> bga_fit;
extern std::vector<double> rga_fit;

int rand_int(int min, int max);
double rand_real(double min, double max);
double generate_alpha(int up);
std::pair<int, int> generate_range(int range);
void write_to_file(const std::vector<double>& binary_data, const std::vector<double>& real_data, const std::string& filename);
#endif 

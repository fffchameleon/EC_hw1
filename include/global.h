#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include <map>

extern std::map<std::string, std::string> values;
extern int p_select;                                ///< number of parent select
extern int POPULATION_SIZE;
extern double cross_prob;
extern double mut_prob;
extern int trial;
extern int term;                                    ///< Number of generations
extern bool is_uniform;
extern bool binary;
extern bool real;
extern bool detail;

extern const int lower;
extern const int upper;
extern std::vector<double> bga_fit;                 ///< Vector to store binary GA avg fitness values (for plotting)
extern std::vector<double> rga_fit;                 ///< Vector to store real-valued GA avg fitness values (for plotting)

/**
 * @brief Initializes global variables and command-line arguments.
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 */
void initialize(int argc, char* argv[]);

/**
 * @brief Generates crossover points.
 * @param n Number of crossover points.
 * @param min_val Minimum value of crossover points.
 * @param max_val Maximum value of crossover points.
 * @return A vector of crossover points.
 */
std::vector<int> generate_crossover_points(int n, int min_val, int max_val);

/**
 * @brief Generates a random integer between min and max.
 * @param min Minimum value.
 * @param max Maximum value.
 * @return A random integer between min and max.
 */
int rand_int(int min, int max);

/**
 * @brief Generates a random real number between min and max.
 * @param min Minimum value.
 * @param max Maximum value.
 * @return A random real number between min and max.
 */
double rand_real(double min, double max);

/**
 * @brief Generates an alpha value within the upper bound.
 * @param up Upper bound for alpha.
 * @return A random alpha value.
 */
double generate_alpha(int up);

/**
 * @brief Writes fitness data to a file.
 * @param binary_data Fitness data of binary GA.
 * @param real_data Fitness data of real-valued GA.
 * @param filename The name of the file to write the data to.
 */
void write_to_file(const std::vector<double>& binary_data, const std::vector<double>& real_data, const std::string& filename);
#endif 

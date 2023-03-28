#include "include/global.h"
#include <random>
#include <utility>
#include <fstream>
#include <vector>

const int POPULATION_SIZE = 100;
const int lower = -512;
const int upper = 511;

std::vector<double> bga_fit;
std::vector<double> rga_fit;

std::random_device rd;
std::mt19937 gen(rd());

int rand_int(int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

double rand_real(double min, double max) {
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

double generate_alpha(int up) {
    double a = 0.5;
    while(a == 0.5) {
        a = rand_real(0, up);
    }
    return a;
}

std::pair<int, int> generate_range(int range) {
    int a = 0, b = 0;
    while(a == b) {
        a = rand_int(0, range);
        b = rand_int(0, range);
    }
    if(a > b) std::swap(a, b);
    std::pair<int, int> pi(a, b);
    return pi;
}

void write_to_file(const std::vector<double>& binary_data, const std::vector<double>& real_data, const std::string& filename) {
    std::ofstream file(filename);

    file << "Binary,Real" << std::endl;

    for (size_t i = 0; i < binary_data.size(); ++i) {
        file << binary_data[i] << "," << real_data[i] << std::endl;
    }

    file.close();
}
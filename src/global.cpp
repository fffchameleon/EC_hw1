#include "../include/global.h"

#include <fstream>
#include <iomanip>
#include <chrono>
#include <set>
bool real = true;
bool binary = true;
int p_select = 2;
int POPULATION_SIZE = 100;
double cross_prob = 0.9;
double mut_prob = 0.1;
int trial = 30;
int term = 500;
bool is_uniform = true;
bool detail = false;
std::map<std::string, std::string> values = {   {"algorithm", "both"},
                                                {"detail", "0"},
                                                {"p_select", "2"},
                                                {"p_size", "100"},
                                                {"cross_prob", "0.9"},
                                                {"mut_prob", "0.1"},
                                                {"trial", "30"},
                                                {"term", "500"},
                                                {"uniform", "1"},
                                                {"n_point", "2"}};
void initialize(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.substr(0, 2) == "--") {
            std::string key = arg.substr(2);
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                values[key] = argv[++i];
            } else {
                values[key] = "";
            }
        }
    }

    p_select = std::stoi(values["p_select"]);
    POPULATION_SIZE = std::stoi(values["p_size"]);
    cross_prob = std::stod(values["cross_prob"]);
    mut_prob = std::stod(values["mut_prob"]);
    trial = std::stoi(values["trial"]);
    term = std::stoi(values["term"]);
    bga_fit.resize(term, 0);
    rga_fit.resize(term, 0);
    is_uniform = (std::stoi(values["uniform"]) != 0);
    
    real = (values["algorithm"] == "both" || values["algorithm"] == "real")? true : false;
    binary = (values["algorithm"] == "both" || values["algorithm"] == "binary")? true : false;

    detail = (std::stoi(values["detail"]) != 0);

    const int num_columns = 2;
    const int column_width = 15;
    const int frame_width = num_columns * column_width + 3;
    std::cout << std::string(frame_width, '-') << "\n";
    std::cout << '|' << std::left << std::setw(column_width) << "Parameter"
              << '|' << std::left << std::setw(column_width) << "Value" << '|' << "\n";
    std::cout << std::string(frame_width, '-') << "\n";
    for(auto i : values) {
         std::cout << '|' << std::left << std::setw(column_width) << i.first
              << '|' << std::left << std::setw(column_width) << i.second << '|' << "\n";
    }
    std::cout << std::string(frame_width, '-') << "\n";
}
const int lower = -512;
const int upper = 511;

// avg_fitness
std::vector<double> bga_fit;
std::vector<double> rga_fit;

// best_fitness
// std::vector<double> bga_fit(term, __DBL_MAX__);
// std::vector<double> rga_fit(term, __DBL_MAX__);

std::random_device rd;
std::mt19937 gen(rd());

std::vector<int> generate_crossover_points(int n, int min_val, int max_val) {
    std::set<int> points;
    while (points.size() < static_cast<std::set<int>::size_type>(n)) {
        points.insert(rand_int(min_val, max_val - 1));
    }
    return std::vector<int>(points.begin(), points.end());
}

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

void write_to_file(const std::vector<double>& binary_data, const std::vector<double>& real_data, const std::string& filename) {
    std::ofstream file(filename);

    if(binary && real) {
        file << "Binary,Real\n";
        for (size_t i = 0; i < binary_data.size(); ++i) 
            file << binary_data[i] << "," << real_data[i] << "\n";
    }
    else if(binary) {
        file << "Binary\n";
        for (size_t i = 0; i < binary_data.size(); ++i) 
            file << binary_data[i] << "\n";
    
    }      
    else if(real)   {
        file << "Real\n";
        for (size_t i = 0; i < binary_data.size(); ++i) 
            file << real_data[i] << "\n";
    
    }
    

    file.close();
}


#include "../include/bga.h"
#include "../include/rga.h"
#include "../include/global.h"

int main(int argc, char* argv[]) {    
    initialize(argc, argv);
    if (values.find("help") != values.end()) {
        std::cout << "Usage: ./main [options]\n\n";
        std::cout << "Options:\n";
        std::cout << "  --p_select <value>   Set the number of tournament selection when parent selection period (default: 2)\n";
        std::cout << "  --p_size <value>     Set the population size (default: 100)\n";
        std::cout << "  --cross_prob <value> Set the crossover probability (default: 0.9)\n";
        std::cout << "  --mut_prob <value>   Set the mutation probability (default: 0.1)\n";
        std::cout << "  --trial <value>      Set the number of trials (default: 30)\n";
        std::cout << "  --term <value>       Set the termination criterion (default: 500)\n";
        std::cout << "  --uniform <value>    Use uniform crossover (1)\n                       or 2-point for binary GA, whole arithmetic for real-valued GA (0) (default: 1)\n";
        std::cout << "  --n_point <value>    Set the number of crossover points (only for binary GA) (default: 2)\n\n";
        return 0;
    } 
    string test;
    if(argc > 1) {
        test = argv[1];
        test = test.substr(2);
    } else 
        test = "default";
    for(int i = 0; i < 90; i++) std::cout << "=" << "\n"[i!=89];

    for(int t = 0; t < trial; t++) {
        // if(t == 0 || t == trial-1) {
        //     std::cout << "The " << t+1 <<  "th trial:\n";
        //     std::cout << "Binary GA:\n";
        // }
        B_GA* bga = new B_GA(std::stoi(values["n_point"]));
        bga->evolution();
        delete bga;

        // for(int i = 0; i < 90 && (t == 0 || t == trial-1); i++) std::cout << "=" << "\n"[i!=89];
        
        // if(t == 0 || t == trial-1) {
        //     std::cout << "Real-valued GA:\n";
        // }
        R_GA* rga = new R_GA;
        rga->evolution();
        delete rga;

        // for(int i = 0; i < 90 && (t == 0 || t == trial-1); i++) std::cout << "=" << "\n"[i!=89];
    }
    for(int i = 0; i < term; i++) {
        bga_fit[i] /= double(trial);
        rga_fit[i] /= double(trial);
    }
    string fileName = "./data/avgfitness_" + test + "_" + values[test] + ".csv";
    write_to_file(bga_fit, rga_fit, fileName);
    return 0;
}
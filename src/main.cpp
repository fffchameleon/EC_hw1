#include "../include/bga.h"
#include "../include/rga.h"
#include "../include/global.h"

int main(int argc, char* argv[]) {    
    initialize(argc, argv);
    if (values.find("help") != values.end()) {
        cout << "Usage: ./main [options]\n\n";
        cout << "Options:\n";
        cout << "  --algorithm <value>  Set the algorithm to use. Only binary, only real or both (default: both)\n";
        cout << "  --detail <value>     Set the number of printing detail or not (default: 0)\n";
        cout << "  --pc <value> Set the crossover probability (default: 0.9)\n";
        cout << "  --pm <value>   Set the mutation probability (default: 0.1)\n";
        cout << "  --n_point <value>    Set the number of crossover points (only for binary GA, and need to set uniform to 0) (default: 2)\n";
        cout << "  --p_select <value>   Set the number of tournament selection when parent selection period (default: 2)\n";
        cout << "  --p_size <value>     Set the population size (default: 100)\n";
        cout << "  --term <value>       Set the termination criterion (default: 500)\n";
        cout << "  --trial <value>      Set the number of trials (default: 30)\n";
        cout << "  --uniform <value>    Use uniform crossover (1)\n                       or 2-point for binary GA, whole arithmetic for real-valued GA (0) (default: 1)\n";
        return 0;
    } 
    string test;
    if(argc > 1) {
        test = argv[1];
        test = test.substr(2);
    } else 
        test = "default";
    for(int i = 0; i < 90; i++) cout << "=" << "\n"[i!=89];

    for(int t = 0; t < trial; t++) {
        if(detail) {
            std::cout << "The " << t+1 <<  "th trial:\n";
            std::cout << "Binary GA:\n";
        }
        if(binary) {
            B_GA* bga = new B_GA(stoi(values["n_point"]));
            bga->evolution();
            delete bga;
        }
        if(detail) {
            for(int i = 0; i < 90 && (t == 0 || t == trial-1); i++) std::cout << "=" << "\n"[i!=89];
            std::cout << "Real-valued GA:\n";
            
        }
        if(real) {
            R_GA* rga = new R_GA;
            rga->evolution();
            delete rga;
        }
        if(detail)  for(int i = 0; i < 90 && (t == 0 || t == trial-1); i++) std::cout << "=" << "\n"[i!=89];
    }
    for(int i = 0; i < term; i++) {
        if(binary)  bga_fit[i] /= double(trial);
        if(real)    rga_fit[i] /= double(trial);
    }
    cout << "BGA in the final generation fitness: " << bga_fit[term-1] << ", RGA in the final generation fitness: " << rga_fit[term-1] << "\n";

    string fileName = "";
    if(binary) {
        fileName += "./data/binary_";
        if(is_uniform) 
            fileName += "uniform_";
        else
            fileName += "2p_";
        fileName += (test + " " + values[test] + ".csv");
    } else {
        fileName += "./data/real_";
        if(is_uniform) 
            fileName += "uniform_";
        else
            fileName += "arith_";
        fileName += (test + " " + values[test] + ".csv");
    }
    write_to_file(bga_fit, rga_fit, fileName);
    return 0;
}
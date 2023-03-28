#include "../include/bga.h"
#include "../include/rga.h"
#include "../include/global.h"

int main() {
    // cin.tie(0);
    // ios_base::sync_with_stdio(false);
    std::cout << "Binary GA:\n";
    B_GA* bga = new B_GA;
    bga->evolution();
    for(int i = 0; i < 100; i++) std::cout << "=";
    std::cout << "\nReal-valued GA:\n";
    R_GA* rga = new R_GA;
    rga->evolution();

    write_to_file(bga_fit, rga_fit, "fitness.csv");
    return 0;
}
#include <bits/stdc++.h>

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
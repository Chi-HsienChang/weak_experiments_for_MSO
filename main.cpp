#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <set>
#include <random>
#include "eg.h"  // 技術上合法
#include "chromosome.h"  // 技術上合法
#include "problem.h"  // 技術上合法

using namespace std;
#define DEBUG 1 // Uncomment this line if DEBUG is meant to be a macro

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <Problem Length L> <Fitness Method>" << endl;
        return 1;
    }

    int L = stoi(argv[1]);
    string method = argv[2];

    int n = pow(2, L);

    // Generate all possible chromosomes:
    // Generates all 2^L possible binary strings of length L, each unique.
    // Each chromosome is paired with its fitness score.
    // So all_chromosomes contains only distinct chromosomes.
    auto all_chromosomes = generate_chromosomes(L, method);

    // Sample n distinct chromosomes randomly
    auto chromosomes = sample_chromosomes(all_chromosomes, n);

    for (int target_index = 0; target_index < L; target_index++) {
        cout << "S -> " << target_index << endl;

        std::vector<int> weak_epi_count_results = epistasis(L, target_index, chromosomes);
        cout << "--- Epistasis ---" << endl;
        for (int i = 1; i < weak_epi_count_results.size(); i++) {
            cout << "#order_" << i << ": " << weak_epi_count_results[i] << endl;
        }
        cout << "-----------------" << endl;
        cout << endl;
    }
    cout << endl;
    cout << endl;

    // 排序根據 chom.second 的值由高到低
    sort(chromosomes.begin(), chromosomes.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // 由高到低排序
    });

    cout << "chromosomes & fitness" << endl;
    for (const auto& chom : chromosomes) {
        cout << chom.first << " " << chom.second << endl;
    }
    cout << endl;
    return 0;
}

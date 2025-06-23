#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <set>
#include <random>
#include "weak.cpp"  // 技術上合法
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

    // Generate all possible chromosomes
    auto all_chromosomes = generate_chromosomes(L, method);

    // Sample n chromosomes randomly
    auto chromosomes = sample_chromosomes(all_chromosomes, n);

    for (int target_index = 0; target_index < L; target_index++) {
        cout << "S -> " << target_index << endl;
        
        std::vector<int> weak_epi_count_results = count_weak(L, target_index, chromosomes, method);
        // cout << "order_0  order_1 order_2 ... order_(ell-1): "<< endl;
        cout << "-----------------" << endl;
        for (int i = 1; i < weak_epi_count_results.size(); i++) {
            cout << "#order_" << i << ": " << weak_epi_count_results[i] << endl;
        }
        cout << "-----------------" << endl;

        // for (int count : weak_epi_count_results) {
        //     cout << count << " ";
        // }
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

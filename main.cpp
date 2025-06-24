#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <set>
#include <random>

#include "chromosome.h"
#include "problem.h"
#include "eg.h"
#include "weak.h"

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

    int run_count = 0;
    bool found_no_weak = false;
    vector<pair<string,double>> chromosomes;

    // 重複執行，直到找到一次「No weak」
    while (!found_no_weak) {
        ++run_count;
        cout << "===== Run #" << run_count << " =====" << endl;

        // 1. 生成所有 2^L 染色體並抽樣 n 條
        auto all_chromosomes = generate_chromosomes(L, method);
        chromosomes = sample_chromosomes(all_chromosomes, n);

        // 2. 檢查 weak
        cout << "====================\nWeak counts\n====================\n";
        bool isWeakProblem = false;
        for (int target_index = 0; target_index < L; ++target_index) {
            cout << "S -> " << target_index << endl;
            auto weak_count_results = weak(L, target_index, chromosomes);

            bool isWeak = false;
            for (int i = 2; i < (int)weak_count_results.size(); ++i) {
                if (weak_count_results[i] > 0) {
                    isWeak = true;
                    isWeakProblem = true;
                    break;
                }
            }

            if (!isWeak) {
                cout << "--- No weak ---\n";
            } else {
                cout << "--- Weak ---\n";
                for (int i = 2; i < (int)weak_count_results.size(); ++i) {
                    cout << "#order_" << i << ": " << weak_count_results[i] << endl;
                }
                cout << "-----------------\n\n";
            }
        }

        if (!isWeakProblem) {
            cout << "##### No weak found! Stopping after run #" 
                 << run_count << " #####\n\n";
            found_no_weak = true;
        } else {
            cout << "##### Weak detected. Retrying... #####\n\n";
            // found_no_weak = true;
        }
    }

    // 3. 找到「No weak」後，再做一次 epistasis 計算（或直接用最後一次的 chromosomes）
    cout << "====================\nEpistasis counts\n====================\n";
    for (int target_index = 0; target_index < L; ++target_index) {
        cout << "S -> " << target_index << endl;
        auto epi_count_results = epistasis(L, target_index, chromosomes);
        cout << "--- Epistasis ---\n";
        for (int i = 1; i < (int)epi_count_results.size(); ++i) {
            cout << "#order_" << i << ": " << epi_count_results[i] << endl;
        }
        cout << "-----------------\n\n";
    }

    // 4. 最後把那組 chromosomes 依 fitness 排序並列印
    sort(chromosomes.begin(), chromosomes.end(),
         [](auto const& a, auto const& b) {
             return a.second > b.second;
         });

    cout << "chromosomes & fitness\n";
    for (auto const& chom : chromosomes) {
        cout << chom.first << " " << chom.second << "\n";
    }
    cout << endl;

    return 0;
}

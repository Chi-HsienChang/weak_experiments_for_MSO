#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <vector>
#include <string>
#include <utility>

// Generate all possible chromosomes (binary strings of length L) with fitness
std::vector<std::pair<std::string, double>> generate_chromosomes(int L, const std::string& method);

// Generate all binary sequences of length n
std::vector<std::vector<int>> generateBinarySequences(int n);

// Generate all combinations of k elements from [0..n], excluding target_index
std::vector<std::vector<int>> generateCombinations(int n, int k, int target_index);

// Sample n chromosomes randomly without replacement
std::vector<std::pair<std::string, double>> sample_chromosomes(
    const std::vector<std::pair<std::string, double>>& all_chromosomes,
    int n
);

#endif // CHROMOSOME_H

#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>
#include <set>
#include <utility>

// 檢查 subset 是否為 set 的子集
bool isSubset(
    const std::vector<int>& subset,
    const std::vector<int>& set);

// 檢查在指定 combination 和 enumeration 條件下，fitness 最大的 allele 值與對應染色體模式
std::pair<std::set<char>, std::vector<std::string>> check_constraint(
    int target_index,
    const std::vector<int>& combination,
    const std::vector<int>& enumeration,
    const std::vector<std::pair<std::string, double>>& chromosomes);

// 比較原始與去除指定 locus 的 constrained optima 是否不同，返回 true/false
bool check_constrained_optima(
    int target_index,
    const std::vector<int>& combination,
    const std::vector<int>& enumeration_original,
    const std::vector<int>& combination_wo,
    const std::vector<int>& enumeration_wo,
    const std::vector<std::pair<std::string, double>>& chromosomes);

#endif // UTIL_H

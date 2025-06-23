#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <set>
#include <random>
#include "chromosome.h"   // 這裡面有 generateCombinations 和 generateBinarySequences 的宣告
#include "problem.h"      // （如有需要，也加上）
#include "weak.h"           // epistasis、check_constraint… 等宣告
#include "utils.h"          // 這裡面有 generate_chromosomes 和 sample_chromosomes 的宣告


// main.cpp
// #include "problem.cpp"  // 技術上合法
// #include "chromosome.cpp"  // 技術上合法

using namespace std;
#define DEBUG 1 // Uncomment this line if DEBUG is meant to be a macro

// Generate all possible chromosomes based on the problem length L

bool isSubset(const std::vector<int>& subset, const std::vector<int>& set) {
    for (const auto& elem : subset) {
        if (std::find(set.begin(), set.end(), elem) == set.end()) {
            // 如果找不到元素，則返回 false
            return false;
        }
    }
    // 所有元素都被找到，返回 true
    return true;
}


std::pair<std::set<char>, std::vector<std::string>> check_constraint(int target_index, const vector<int>& combination, const vector<int>& enumeration, const vector<pair<string, double>>& chromosomes){
    std::set<char> values_at_v;
    std::vector<std::string> highest_fitness_chromosomes;

    // if (DEBUG){
    //     cout << endl;
    //     cout << "++++++++++++ in check_constraint ++++++++++++" << endl;
    // }

    // if (DEBUG)
    // {
    //     cout << "locus =  ";
    //     for (const auto& elem : combination) {
    //         cout << elem << " ";
    //     }
    //     cout << endl;
    // }

    // if (DEBUG)
    // {
    //     cout << "allele =  ";
    //     for (const auto& elem : enumeration) {
    //         cout << elem << " ";
    //     }
    //     cout << endl;
    // }   
    


    double max_fitness = -1;
    for (const auto& chromosome : chromosomes) 
    {
        bool fit_constraint = true;
        int enumeration_index = 0;
        for (int i : combination)
        {
            // cout << "note chromosome.first[i]: " << chromosome.first[i] << endl;
            // cout << "enumeration[i]: " << enumeration[enumeration_index] << endl;

            if (chromosome.first[i] - '0' != enumeration[enumeration_index]){
                fit_constraint = false;
                // cout << "不一樣" << chromosome.first[i] << endl;
                break;
            }
            // else{
            //     cout << "!一樣!" << chromosome.first[i] << endl;
            // }

            enumeration_index++;
        }


        if (fit_constraint) 
        {
            double fitness = chromosome.second;
            if (fitness > max_fitness) {
                max_fitness = fitness;
                values_at_v.clear();
                highest_fitness_chromosomes.clear();
                values_at_v.insert(chromosome.first[target_index]);
                highest_fitness_chromosomes.push_back(chromosome.first);
            } else if (fitness == max_fitness) {
                values_at_v.insert(chromosome.first[target_index]);
                highest_fitness_chromosomes.push_back(chromosome.first);
            } 

            // if (DEBUG){
            //     cout << "constraint = ";
            //     int _index = 0;
            //     for (int i : combination)
            //     {
            //         cout << "(" << i << ", " << enumeration[_index] << ") ";
            //         _index++;
            //     cout << endl;
            //     }
            //     cout << chromosome.first << endl;
            // }
        }         
    
    }



    // if (DEBUG)
    // {
    //     cout << "highest_fitness_chromosomes: ";
    //     for (const auto& elem : highest_fitness_chromosomes) {
    //         cout << elem << " ";
    //     }
    //     cout << endl;
    // }

    // if (DEBUG)
    // {
    //     cout<<"max_fitness = " << max_fitness << endl;
    // }

    // if (DEBUG)
    // {
    //     cout << "values_at_v: ";
    //     for (const auto& elem : values_at_v) {
    //         cout << elem << " ";
    //     }
    //     cout << endl;
    // }

    // if (DEBUG){
    //     cout << "++++++++++++ out check_constraint ++++++++++++" << endl;
    // }

    return {values_at_v, highest_fitness_chromosomes};

}


bool check_constrained_optima(int target_index, const vector<int>& combination, const vector<int>& enumeration_original, const vector<int>& combination_wo, const vector<int>& enumeration_wo, const vector<pair<string, double>>& chromosomes){

        // if (DEBUG)
        // {
        //     cout << "A =  ";
        //     for (const auto& elem : enumeration_original) {
        //         cout << elem << " ";
        //     }
        //     cout << endl;
        // }

        // if (DEBUG)
        // {
        //     cout << "B =  ";
        //     for (const auto& elem : enumeration) {
        //         cout << elem << " ";
        //     }
        //     cout << endl;
        // }


    auto constrained_optima_original = check_constraint(target_index, combination, enumeration_original, chromosomes);

    auto constrained_optima_flip = check_constraint(target_index, combination_wo, enumeration_wo, chromosomes);




    if (constrained_optima_original.first != constrained_optima_flip.first) {

        if (!constrained_optima_original.first.empty() && !constrained_optima_flip.first.empty()){

            // if (DEBUG)
            // {
            //     cout << "constrained_optima_original.first: ";
            //     for (const auto& elem : constrained_optima_original.first) {
            //         cout << elem << " ";
            //     }
            //     cout << endl;
            // }

            // if (DEBUG)
            // {
            //     cout << "constrained_optima_flip.first: ";
            //     for (const auto& elem : constrained_optima_flip.first) {
            //         cout << elem << " ";
            //     }
            //     cout << endl;
            // }


            //////
            // cout << "{";
            // for (const auto& elem : combination) {
            //     cout << elem << " ";
            // }
            // cout << "} -> "<< target_index << endl;

            // cout << "omega_A_pattern: ";
            // for (const auto& elem : constrained_optima_original.second) {
            //     cout << elem << endl;
            // }

            // cout << "omega_B_pattern: ";
            // for (const auto& elem : constrained_optima_flip.second) {
            //     cout << elem << endl;
            // }

            // cout << "omega_A_[target_index] = ";
            // for (const auto& elem : constrained_optima_original.first) {
            //     cout << elem << " ";
            // }
            // cout << endl;   

            // cout << "omega_B_[target_index] = ";
            // for (const auto& elem : constrained_optima_flip.first) {
            //     cout << elem << " ";
            // }
            // cout << endl;    
            // cout << endl;  
            return true;
        }
        else{
            return false;
        }
    }else{
        // cout << "{";
        // for (const auto& elem : combination) {
        //     cout << elem << " ";
        // }
        // cout << "} !-> "<< target_index << endl;

        // cout << "omega_A_pattern: ";
        // for (const auto& elem : constrained_optima_original.second) {
        //     cout << elem << endl;
        // }

        // cout << "omega_B_pattern: ";
        // for (const auto& elem : constrained_optima_flip.second) {
        //     cout << elem << endl;
        // }

        // cout << "omega_A_[target_index] = ";
        // for (const auto& elem : constrained_optima_original.first) {
        //     cout << elem << " ";
        // }
        // cout << endl;   

        // cout << "omega_B_[target_index] = ";
        // for (const auto& elem : constrained_optima_flip.first) {
        //     cout << elem << " ";
        // }
        // cout << endl;    
        // cout << endl;        
        return false;
    }
}


// Print the matrix
void print_matrix(const vector<vector<string>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}




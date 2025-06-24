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
#include "eg.h"           // epistasis、check_constraint… 等宣告
#include "utils.h"         // weak 函數的宣告

using namespace std;
#define DEBUG 1 // Uncomment this line if DEBUG is meant to be a macro

// Generate all possible chromosomes based on the problem length L

// bool isSubset(const std::vector<int>& subset, const std::vector<int>& set) {
//     for (const auto& elem : subset) {
//         if (std::find(set.begin(), set.end(), elem) == set.end()) {
//             // 如果找不到元素，則返回 false
//             return false;
//         }
//     }
//     // 所有元素都被找到，返回 true
//     return true;
// }


// std::pair<std::set<char>, std::vector<std::string>> check_constraint(int target_index, const vector<int>& combination, const vector<int>& enumeration, const vector<pair<string, double>>& chromosomes){
//     std::set<char> values_at_v;
//     std::vector<std::string> highest_fitness_chromosomes;

//     // if (DEBUG){
//     //     cout << endl;
//     //     cout << "++++++++++++ in check_constraint ++++++++++++" << endl;
//     // }

//     // if (DEBUG)
//     // {
//     //     cout << "locus =  ";
//     //     for (const auto& elem : combination) {
//     //         cout << elem << " ";
//     //     }
//     //     cout << endl;
//     // }

//     // if (DEBUG)
//     // {
//     //     cout << "allele =  ";
//     //     for (const auto& elem : enumeration) {
//     //         cout << elem << " ";
//     //     }
//     //     cout << endl;
//     // }   
    


//     double max_fitness = -1;
//     for (const auto& chromosome : chromosomes) 
//     {
//         bool fit_constraint = true;
//         int enumeration_index = 0;
//         for (int i : combination)
//         {
//             // cout << "note chromosome.first[i]: " << chromosome.first[i] << endl;
//             // cout << "enumeration[i]: " << enumeration[enumeration_index] << endl;

//             if (chromosome.first[i] - '0' != enumeration[enumeration_index]){
//                 fit_constraint = false;
//                 // cout << "不一樣" << chromosome.first[i] << endl;
//                 break;
//             }
//             // else{
//             //     cout << "!一樣!" << chromosome.first[i] << endl;
//             // }

//             enumeration_index++;
//         }


//         if (fit_constraint) 
//         {
//             double fitness = chromosome.second;
//             if (fitness > max_fitness) {
//                 max_fitness = fitness;
//                 values_at_v.clear();
//                 highest_fitness_chromosomes.clear();
//                 values_at_v.insert(chromosome.first[target_index]);
//                 highest_fitness_chromosomes.push_back(chromosome.first);
//             } else if (fitness == max_fitness) {
//                 values_at_v.insert(chromosome.first[target_index]);
//                 highest_fitness_chromosomes.push_back(chromosome.first);
//             } 

//             // if (DEBUG){
//             //     cout << "constraint = ";
//             //     int _index = 0;
//             //     for (int i : combination)
//             //     {
//             //         cout << "(" << i << ", " << enumeration[_index] << ") ";
//             //         _index++;
//             //     cout << endl;
//             //     }
//             //     cout << chromosome.first << endl;
//             // }
//         }         
    
//     }



//     // if (DEBUG)
//     // {
//     //     cout << "highest_fitness_chromosomes: ";
//     //     for (const auto& elem : highest_fitness_chromosomes) {
//     //         cout << elem << " ";
//     //     }
//     //     cout << endl;
//     // }

//     // if (DEBUG)
//     // {
//     //     cout<<"max_fitness = " << max_fitness << endl;
//     // }

//     // if (DEBUG)
//     // {
//     //     cout << "values_at_v: ";
//     //     for (const auto& elem : values_at_v) {
//     //         cout << elem << " ";
//     //     }
//     //     cout << endl;
//     // }

//     // if (DEBUG){
//     //     cout << "++++++++++++ out check_constraint ++++++++++++" << endl;
//     // }

//     return {values_at_v, highest_fitness_chromosomes};

// }


// bool check_constrained_optima(int target_index, const vector<int>& combination, const vector<int>& enumeration_original, const vector<int>& combination_wo, const vector<int>& enumeration_wo, const vector<pair<string, double>>& chromosomes){

//         // if (DEBUG)
//         // {
//         //     cout << "A =  ";
//         //     for (const auto& elem : enumeration_original) {
//         //         cout << elem << " ";
//         //     }
//         //     cout << endl;
//         // }

//         // if (DEBUG)
//         // {
//         //     cout << "B =  ";
//         //     for (const auto& elem : enumeration) {
//         //         cout << elem << " ";
//         //     }
//         //     cout << endl;
//         // }


//     auto constrained_optima_original = check_constraint(target_index, combination, enumeration_original, chromosomes);

//     auto constrained_optima_flip = check_constraint(target_index, combination_wo, enumeration_wo, chromosomes);




//     if (constrained_optima_original.first != constrained_optima_flip.first) {

//         if (!constrained_optima_original.first.empty() && !constrained_optima_flip.first.empty()){

//             // if (DEBUG)
//             // {
//             //     cout << "constrained_optima_original.first: ";
//             //     for (const auto& elem : constrained_optima_original.first) {
//             //         cout << elem << " ";
//             //     }
//             //     cout << endl;
//             // }

//             // if (DEBUG)
//             // {
//             //     cout << "constrained_optima_flip.first: ";
//             //     for (const auto& elem : constrained_optima_flip.first) {
//             //         cout << elem << " ";
//             //     }
//             //     cout << endl;
//             // }


//             //////
//             // cout << "{";
//             // for (const auto& elem : combination) {
//             //     cout << elem << " ";
//             // }
//             // cout << "} -> "<< target_index << endl;

//             // cout << "omega_A_pattern: ";
//             // for (const auto& elem : constrained_optima_original.second) {
//             //     cout << elem << endl;
//             // }

//             // cout << "omega_B_pattern: ";
//             // for (const auto& elem : constrained_optima_flip.second) {
//             //     cout << elem << endl;
//             // }

//             // cout << "omega_A_[target_index] = ";
//             // for (const auto& elem : constrained_optima_original.first) {
//             //     cout << elem << " ";
//             // }
//             // cout << endl;   

//             // cout << "omega_B_[target_index] = ";
//             // for (const auto& elem : constrained_optima_flip.first) {
//             //     cout << elem << " ";
//             // }
//             // cout << endl;    
//             // cout << endl;  
//             return true;
//         }
//         else{
//             return false;
//         }
//     }else{
//         // cout << "{";
//         // for (const auto& elem : combination) {
//         //     cout << elem << " ";
//         // }
//         // cout << "} !-> "<< target_index << endl;

//         // cout << "omega_A_pattern: ";
//         // for (const auto& elem : constrained_optima_original.second) {
//         //     cout << elem << endl;
//         // }

//         // cout << "omega_B_pattern: ";
//         // for (const auto& elem : constrained_optima_flip.second) {
//         //     cout << elem << endl;
//         // }

//         // cout << "omega_A_[target_index] = ";
//         // for (const auto& elem : constrained_optima_original.first) {
//         //     cout << elem << " ";
//         // }
//         // cout << endl;   

//         // cout << "omega_B_[target_index] = ";
//         // for (const auto& elem : constrained_optima_flip.first) {
//         //     cout << elem << " ";
//         // }
//         // cout << endl;    
//         // cout << endl;        
//         return false;
//     }
// }


int check_epistasis(int target_index, const vector<int>& combination, const vector<vector<int>>& enumerations, const vector<pair<string, double>>& chromosomes) {

    // cout << "==================" << endl;
    // cout << "combination: ";
    // for (const auto& elem : combination) {
    //     cout << elem << " ";
    // }
    // cout << endl;
    

    // auto enumeration_original = enumeration;
    int condition_holds = 0;
    for (int condition_index = 0; condition_index < combination.size(); condition_index++)
    {
        for (auto& enumeration : enumerations) // combination = [1, 2] and enumerations = { [0, 0], [0, 1], [1, 0], [1, 1]}
        { 
            auto enumeration_original = enumeration;
            // enumeration[condition_index] = 1 - enumeration[condition_index]; // flip bit  

            auto combination_wo = combination;
            auto enumeration_wo = enumeration;
            combination_wo.erase(combination_wo.begin() + condition_index);
            enumeration_wo.erase(enumeration_wo.begin() + condition_index);

            // cout << "combination: ";
            // for (const auto& elem : combination) {
            //     cout << elem << " ";
            // }   
            // cout<<endl;

            // cout << "combination_wo: ";
            // for (const auto& elem : combination_wo) {
            //     cout << elem << " ";
            // }
            // cout<<endl;

            // cout << "enumeration: ";
            // for (const auto& elem : enumeration) {
            //     cout << elem << " ";
            // }
            // cout<<endl;

            // cout << "enumeration_wo: ";
            // for (const auto& elem : enumeration_wo) {
            //     cout << elem << " ";
            // }
            // cout<<endl;
            
            bool not_equal;
            not_equal = check_constrained_optima(target_index, combination, enumeration_original, combination_wo, enumeration_wo, chromosomes);

            if (not_equal)
            {
                condition_holds++;
                break;
            }       
        }

    }

    if (condition_holds == combination.size())
        {
            if (combination.size() == 1){

                

            }else{  
                cout << "{";
                for (const auto& elem : combination) {
                    cout << elem << " ";
                }
                cout << "} -> "<< target_index << endl;           
            }

            // if (DEBUG){
            //     cout << "--------------------------------------" << endl;
            //     cout << "enumeration_original" << endl;
            //     for (const auto& elem : enumeration_original) {
            //         cout << elem << " ";
            //     }
            //     cout << endl;          
            // }
            return 1;
        }


    // if (DEBUG){
    //     cout << endl;
    //     cout << "---------- in check_weak --------------" << endl;
    // }


    // if (DEBUG)
    // {
    //     cout << "current combination index is ";
    //     for (const auto& elem : combination) {
    //         cout << elem << " ";
    //     }
    //     cout << endl;
    // }
    
    
    
    // if (DEBUG)
    // {
    //     cout << "current enumeration is ";
    //     for (const auto& elem : enumeration) {
    //         cout << elem << " ";
    //     }
    //     cout << endl;
    // }

    // cout << "current combination index is ";
    // for (const auto& elem : combination) {
    //     cout << elem << " ";
    // }
    // cout << endl;

    // cout << "current enumeration is ";
    // for (const auto& elem : enumeration) {
    //     cout << elem << " ";
    // }
    // cout << "target_index = "<< target_index <<endl;


    // auto enumeration_original = enumeration;
    // int condition_holds = 0;
    // for (int condition_index = 0; condition_index < enumeration.size(); condition_index++)
    // {
    //     // cout << "--------------------------------------" << endl;
    //     // cout << "enumeration_original" << endl;
    //     // for (const auto& elem : enumeration_original) {
    //     //     cout << elem << " ";
    //     // }
    //     // cout << endl;

    //     enumeration = enumeration_original;
    //     enumeration[condition_index] = 1 - enumeration[condition_index]; // flip bit 

    //     // if (DEBUG)
    //     // {
    //     //     cout << "A =  ";
    //     //     for (const auto& elem : enumeration_original) {
    //     //         cout << elem << " ";
    //     //     }
    //     //     cout << endl;
    //     // }

    //     // if (DEBUG)
    //     // {
    //     //     cout << "B =  ";
    //     //     for (const auto& elem : enumeration) {
    //     //         cout << elem << " ";
    //     //     }
    //     //     cout << endl;
    //     // }
        
    //     bool not_equal;
    //     not_equal = check_constrained_optima(target_index, combination, enumeration_original, enumeration, chromosomes);
    //     // cout << "not_equal: " << not_equal << endl;
    //     // cout << "######################################" << endl;

    //     if (not_equal)
    //     {
    //         condition_holds++;
    //     }else{
    //         return 0;
    //     }
    // }

    // if (condition_holds == enumeration.size())
    // {
    //     if (DEBUG){  
    //         cout << "{";
    //         for (const auto& elem : combination) {
    //             cout << elem << " ";
    //         }
    //         cout << "} -> "<< target_index << endl;           
    //     }

        // if (DEBUG){
        //     cout << "--------------------------------------" << endl;
        //     cout << "enumeration_original" << endl;
        //     for (const auto& elem : enumeration_original) {
        //         cout << elem << " ";
        //     }
        //     cout << endl;          
        // }
    //     return 1;
    // }

    // if (DEBUG){
    //     cout << "---------- out check_weak --------------" << endl;
    // }

    return 0;
}


std::vector<int> epistasis(int L, int target_index, const vector<pair<string, double>>& chromosomes)
{
    std::vector<std::vector<std::vector<int>>> epi_set(L);
    std::vector<int> epi_count(L, 0); 
    
    for (int epi_size = 1; epi_size < L; epi_size++)
    {  
        auto combinations = generateCombinations(L-1, epi_size, target_index); // combinations = { [1, 2], [1, 3], [2, 3] }

        for (auto& combination : combinations) // combination = [1, 2]
        { 

            bool not_find_smaller_epi;

            if (epi_size == 1)
            {
                not_find_smaller_epi = true;           
            }else{
                not_find_smaller_epi = true;  
                int smaller_epi_size = epi_size;
                bool is_subset;
                while(not_find_smaller_epi && smaller_epi_size>=1)
                {   
                    for (auto& previous : epi_set[smaller_epi_size-1]) 
                    {
                        is_subset = isSubset(previous, combination);
                        not_find_smaller_epi = !is_subset;
                        if(is_subset) break;
                    }
                    smaller_epi_size--;
                }
            }

            if(not_find_smaller_epi)
            {
                auto enumerations = generateBinarySequences(epi_size); // enumerations = { [0, 0], [0, 1], [1, 0], [1, 1] }    

                int result = check_epistasis(target_index, combination, enumerations, chromosomes);
                epi_count[epi_size] += result;
                if (result)
                {
                    // weak_epi_set[epi_size].push_back(combination);
                    // break;
                }
            
            
            }
        }
    }

    return epi_count;
}




#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <set>
#include <random>
// main.cpp
#include "problem.cpp"  // 技術上合法

using namespace std;
#define DEBUG 1 // Uncomment this line if DEBUG is meant to be a macro

// Generate all possible chromosomes based on the problem length L
vector<pair<string, double>> generate_chromosomes(int L, const string& method) {
    vector<pair<string, double>> chromosomes;
    int num_combinations = pow(2, L);

    for (int i = 0; i < num_combinations; ++i) {
        // Generate chromosome using bitset and convert it to a string
        string chromosome = bitset<32>(i).to_string().substr(32 - L);
        
        // Calculate fitness for the chromosome
        double fitness = calculate_fitness(chromosome, method);
        
        // Store the chromosome and its fitness as a pair
        chromosomes.push_back({chromosome, fitness});
    }

    return chromosomes;
}

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

std::vector<std::vector<int>> generateBinarySequences(int n) {
    int totalSequences = 1 << n;  // 2^n
    std::vector<std::vector<int>> allSequences;

    for (int i = 0; i < totalSequences; ++i) {
        std::vector<int> sequence(n);

        for (int j = 0; j < n; ++j) {
            // 檢查第j位是否為1
            sequence[n - 1 - j] = (i >> j) & 1;
        }

        // 將序列添加到所有序列的vector中
        allSequences.push_back(sequence);
    }

    return allSequences;
}

std::vector<std::vector<int>> generateCombinations(int n, int k, int target_index) {
    std::vector<int> elements;

    // 建立不包含 target_index 的元素清單
    for (int i = 0; i <= n; ++i) { // n 表示實際範圍
        if (i != target_index) {
            elements.push_back(i);
        }
    }

    std::vector<int> bitmask(k, 1);            // 創建 k 個 1
    bitmask.resize(elements.size(), 0);       // 後面填充其餘為 0

    std::vector<std::vector<int>> combinations;

    do {
        std::vector<int> currentCombination;
        for (size_t i = 0; i < elements.size(); ++i) {
            if (bitmask[i]) {
                currentCombination.push_back(elements[i]);
            }
        }
        combinations.push_back(currentCombination);
    } while (std::prev_permutation(bitmask.begin(), bitmask.end())); // 生成下一個排列

    return combinations;
}

std::pair<std::set<char>, std::vector<std::string>> check_constraint(int target_index, auto combination, auto enumeration, auto chromosomes){
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


bool check_constrained_optima(int target_index, auto combination, auto enumeration_original, auto combination_wo, auto enumeration_wo, auto chromosomes){

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




int check_weak(int target_index, auto combination, auto enumerations, auto chromosomes) {

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
            if (DEBUG){  
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

std::vector<int> weak(int L, int target_index, auto chromosomes, const string& method)
{
    std::vector<std::vector<std::vector<int>>> weak_epi_set(L);
    std::vector<int> weak_epi_count(L, 0); 
    

    for (int epi_size = 1; epi_size < L; epi_size++)
    {  
        auto combinations = generateCombinations(L-1, epi_size, target_index); // combinations = { [1, 2], [1, 3], [2, 3] }

        for (auto& combination : combinations) // combination = [1, 2]
        { 
            // cout << "combination!!!!! ";
            // for (const auto& elem : combination) {
            //     cout << elem << " ";
            // }
            // cout << endl;

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
                    // cout << "previous:" << endl;
                    for (auto& previous : weak_epi_set[smaller_epi_size-1]) 
                    {
                        // cout << "previous" << endl;

                        // for (const auto& elem : previous) {
                        //     cout << elem << " ";
                        // }
                        // cout<<endl;

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

                int result = check_weak(target_index, combination, enumerations, chromosomes);
                weak_epi_count[epi_size] += result;
                if (result)
                {
                    // weak_epi_set[epi_size].push_back(combination);
                    // break;
                }
            
            
            }
        }
    }

    return weak_epi_count;
}



std::vector<int> epistasis(int L, int target_index, auto chromosomes)
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

                int result = check_weak(target_index, combination, enumerations, chromosomes);
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



// Print the matrix
void print_matrix(const vector<vector<string>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

// Sample n chromosomes randomly from all_chromosomes
vector<pair<string, double>> sample_chromosomes(const vector<pair<string, double>>& all_chromosomes, int n) {
    // Create a mutable copy of all_chromosomes
    vector<pair<string, double>> sampled_chromosomes = all_chromosomes;

    // Shuffle the vector
    random_device rd;
    mt19937 gen(rd());
    shuffle(sampled_chromosomes.begin(), sampled_chromosomes.end(), gen);

    // Resize to keep only n elements
    if (n < sampled_chromosomes.size()) {
        sampled_chromosomes.resize(n);
    }

    return sampled_chromosomes;
}

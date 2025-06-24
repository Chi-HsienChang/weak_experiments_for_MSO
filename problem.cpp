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


double calculate_segment_onemax_weak(const string& segment, const string& method) {
        double weak_fiteness = 0;
        if (count(segment.begin(), segment.end(), '1') == 0)
            weak_fiteness = 1.5;
        else
            weak_fiteness = count(segment.begin(), segment.end(), '1');

        return weak_fiteness;
}

// Helper function for segment-based functions
double calculate_segment_fitness(const string& segment, const string& method) {
    double result = 0.0;
    if (method == "trap") {
        int ones = count(segment.begin(), segment.end(), '1');
        if (ones == segment.length()) {
            return 4.0;
        } else if (ones == 0) {
            return 3.0;
        } else {
            result = 3.0 - (ones * 3.0 / (segment.length() - 1));
            if (result < 0)
            {
                return 0.0;
            }

            return result;
        }
    } else if (method == "niah") {
        return all_of(segment.begin(), segment.end(), [](char bit) { return bit == '1'; }) ? 1.0 : 0.0;
    }
    return 0.0;
}

double calculate_segment_fitness_test(const string& segment) {
    // double result = 0.0;
  
    int ones = count(segment.begin(), segment.end(), '1');
    if (ones == segment.length()) {
        return 4.0;
    } else if (ones == 3) {
        return 3.0;
    } else if (ones == 2) {
        return 0.0;
    } else if (ones == 1) {
        return 1.0;
    } else {
        return 2.0;
    }
    // return 0.0;
}


// Helper function for segment-based functions
double calculate_onemax_weak2(const string& segment, const string& method) {
    double weak_fiteness = 0;
    if (count(segment.begin(), segment.end(), '1') == 0)
        weak_fiteness = 1.5;
    else
        weak_fiteness = count(segment.begin(), segment.end(), '1');

    return weak_fiteness;
}

double calculate_onemax_weak3(const string& segment, const string& method) {
    double weak_fiteness = 0;
    if (count(segment.begin(), segment.end(), '1') == 0)
        weak_fiteness = 1.5;
    else
        weak_fiteness = count(segment.begin(), segment.end(), '1');

    return weak_fiteness;
}

// Calculate the fitness of a chromosome based on the selected method
double calculate_fitness(const string& chromosome, const string& method) {
    if (method == "onemax") {
        // if (DEBUG)
        // {
        //     cout << chromosome << endl;
        //     cout << count(chromosome.begin(), chromosome.end(), '1') << endl;
        // }
        return count(chromosome.begin(), chromosome.end(), '1');
    } else if (method == "trap") {
        // if (DEBUG)
        // {
        //     cout << chromosome << endl;
        //     cout << calculate_segment_fitness(chromosome, "trap") << endl;
        // }
        return calculate_segment_fitness(chromosome, "trap");
    } else if (method == "niah") {
        // if (DEBUG)
        // {
        //     cout << chromosome << endl;
        //     cout << calculate_segment_fitness(chromosome, "niah") << endl;
        // }
        return calculate_segment_fitness(chromosome, "niah");
    } else if (method == "ctrap" || method == "cniah") {
        int segment_length = 4;
        double total_fitness = 0.0;
        for (size_t i = 0; i < chromosome.length(); i += segment_length) {
            string segment = chromosome.substr(i, min(segment_length, static_cast<int>(chromosome.length() - i)));
            total_fitness += calculate_segment_fitness(segment, method.substr(1));
        }

        return total_fitness;
    } else if (method == "cyctrap") {
        int segment_length = 4;
        int overlap = 1;
        double total_fitness = 0.0;
        for (size_t i = 0; i < chromosome.length(); i += segment_length - overlap) {
            string segment;
            if (i + segment_length <= chromosome.length()) {
                segment = chromosome.substr(i, segment_length);
            } else {
                segment = chromosome.substr(i) + chromosome.substr(0, segment_length - (chromosome.length() - i));
            }

            total_fitness += calculate_segment_fitness(segment, "trap");

            if (i + segment_length >= chromosome.length() + overlap) {
                break;
            }
        }

        return total_fitness;
    } else if (method == "leadingones") {
        // cout << method << "!!" << endl;
        double leading_ones = 0;
        for (char bit : chromosome) {
            if (bit == '1') {
                leading_ones++;
            } else {
                break;
            }
        }

        return leading_ones;
    } else if (method == "leadingtraps") {
        int segment_length = 4;

        std::vector<int> L(chromosome.length(), 0); 
        L[0] = 1;
        std::vector<double> segment_fitness_record(chromosome.length(), 0); 

        double segment_fitness = 0.0;
        for (size_t i = 0; i < chromosome.length(); i += segment_length) {
            string segment = chromosome.substr(i, min(segment_length, static_cast<int>(chromosome.length() - i)));
            segment_fitness = calculate_segment_fitness(segment, "trap");
            segment_fitness_record[i] += segment_fitness;

            if (i == 0)
            {
                continue;
            }
           
            if (segment_fitness_record[i-4] == 4 && L[i-4] == 1) {
                L[i] = 1;
            }
            
        }

        double total_fitness = 0.0;
        for (size_t i = 0; i < chromosome.length(); i += segment_length) {
            total_fitness += L[i] * segment_fitness_record[i]; 
        }

        return total_fitness;
    
    } else if (method == "test") {
        // cout << method << "!!" << endl;
        
        double weak_fiteness = calculate_segment_fitness_test(chromosome);

        return weak_fiteness;
    } else if (method == "test_equal_fitness") {
        // cout << method << "!!" << endl;
        
        double weak_fiteness = 0;
        if (chromosome == "111")
            weak_fiteness = 3;
        else if (chromosome == "100")
            weak_fiteness = 2;
        else if (chromosome == "001")
            weak_fiteness = 1;
        else
            weak_fiteness = 0;
        return weak_fiteness;

    } else if (method == "onemax_weak") {
        // cout << method << "!!" << endl;
        
        double weak_fiteness = 0;
        // if (count(chromosome.begin(), chromosome.end(), '1') == 0)
        //     weak_fiteness = 1.5;
        if ((chromosome == "1111"))
            weak_fiteness = 16;
        else if((chromosome == "0111"))
            weak_fiteness = 15;
        // else if((chromosome == "1011"))
        //     weak_fiteness = 14;
        else if((chromosome == "1101"))
            weak_fiteness = 13;
        else if((chromosome == "1110"))
            weak_fiteness = 12;
        else if((chromosome == "0011") or (chromosome == "1011"))
            weak_fiteness = 11;
        else if((chromosome == "0101"))
            weak_fiteness = 10;
        else if((chromosome == "0110"))
            weak_fiteness = 9;
        else if((chromosome == "1001") or (chromosome == "0001"))
            weak_fiteness = 15.6;
        // else if((chromosome == "1010"))
        //     weak_fiteness = 7;
        else if((chromosome == "1100"))
            weak_fiteness = 6;
        else if((chromosome == "0001"))
            weak_fiteness = 5;
        else if((chromosome == "0010"))
            weak_fiteness = 4;
        else if((chromosome == "0100"))
            weak_fiteness = 3;
        else if((chromosome == "1001"))
            weak_fiteness = 15.6;
        else if((chromosome == "0000"))
            weak_fiteness = 1;
        else if((chromosome == "1101") or (chromosome == "0101"))
            weak_fiteness = 0;
        else
            weak_fiteness = 0;
        



        return weak_fiteness;
    } else if (method == "multi_weak") {
        double weak_fiteness = 0;

        std::string segment_weak2;
        segment_weak2 += chromosome[0];
        segment_weak2 += chromosome[1];
        segment_weak2 += chromosome[2]; 

        weak_fiteness += calculate_segment_onemax_weak(segment_weak2, method);

        std::string segment_weak3;
        segment_weak3 += chromosome[3];
        segment_weak3 += chromosome[4];
        segment_weak3 += chromosome[5];   
        segment_weak3 += chromosome[6];    
        weak_fiteness += calculate_segment_onemax_weak(segment_weak3, method);  

        std::string segment_weak4;
        segment_weak4 += chromosome[7];
        segment_weak4 += chromosome[8];
        segment_weak4 += chromosome[9];   
        segment_weak4 += chromosome[10];    
        segment_weak4 += chromosome[11]; 
        weak_fiteness += calculate_segment_onemax_weak(segment_weak4, method); 
      
        return weak_fiteness;
    }else if (method == "max3sat") {
    int n = chromosome.size();
    if (n < 2) {
        cerr << "Error: max3sat_chainxor requires chromosome size >= 2\n";
        exit(1);
    }

    // 每個子句最多 3 個 literal，用 pair<idx, positive> 表示
    vector<array<pair<int,bool>,3>> clauses;
    // 1) 鎖定 x0 = true，唯一最佳解才能啟動整條鏈
    clauses.push_back({ make_pair(0,true), make_pair(0,true), make_pair(0,true) });

    // 2) 對每個相鄰 (i, i+1)，加入 XOR 約束：
    //    (xi ∨ xi+1) ∧ (¬xi ∨ ¬xi+1)，並各自用重複 literal 填滿到 3 長度
    for (int i = 0; i < n - 1; ++i) {
        // (xi ∨ xi+1 ∨ xi+1)
        clauses.push_back({ make_pair(i,  true),
                            make_pair(i+1,true),
                            make_pair(i+1,true) });
        // (¬xi ∨ ¬xi+1 ∨ ¬xi+1)
        clauses.push_back({ make_pair(i,  false),
                            make_pair(i+1,false),
                            make_pair(i+1,false) });
    }

        // 2) 輸出成 DIMACS CNF
    //    p cnf <變數數量> <子句數量>
    cout << "p cnf " << n << " " << clauses.size() << "\n";
    for (auto& cl : clauses) {
        for (auto& lit : cl) {
            int var = lit.first + 1;                    // DIMACS 變數從 1 開始
            cout << (lit.second ?  var : -var) << " ";  // 正 lit.second=true，負 lit.second=false
        }
        cout << "0\n";  // 每行子句以 0 結尾
    }

    // 評估滿足子句數
    int sat = 0;
    for (auto& cl : clauses) {
        bool clause_sat = false;
        for (auto& lit : cl) {
            bool val = (chromosome[ lit.first ] == '1');
            if ((lit.second && val) || (!lit.second && !val)) {
                clause_sat = true;
                break;
            }
        }
        if (clause_sat) ++sat;
    }

    return static_cast<double>(sat);
    }else if (method == "max3sat_cnf") {
    int n = chromosome.size();
    if (n < 2) {
        cerr << "Error: max3sat_chainxor requires chromosome size >= 2\n";
        exit(1);
    }

    // 1) 產生所有 clauses
    vector<array<pair<int,bool>,3>> clauses;
    clauses.push_back({ make_pair(0,true), make_pair(0,true), make_pair(0,true) });
    for (int i = 0; i < n - 1; ++i) {
        clauses.push_back({ make_pair(i,  true),
                            make_pair(i+1,true),
                            make_pair(i+1,true) });
        clauses.push_back({ make_pair(i,  false),
                            make_pair(i+1,false),
                            make_pair(i+1,false) });
    }

    // 2) 印出 human‐readable 的 clauses
    cout << "===  clauses ===\n";
    for (auto& cl : clauses) {
        cout << "(";
        for (int i = 0; i < 3; ++i) {
            int idx = cl[i].first;
            bool pos = cl[i].second;
            if (!pos) cout << "¬";
            cout << "x" << idx;
            if (i < 2) cout << " ∨ ";
        }
        cout << ")\n";
    }
    // 如果只想印出 clauses 就停在這裡：
    // exit(0);

    // —— 以下原本的 fitness 計算保持不變 —— 
    int sat = 0;
    for (auto& cl : clauses) {
        bool clause_sat = false;
        for (auto& lit : cl) {
            bool val = (chromosome[lit.first] == '1');
            if ((lit.second && val) || (!lit.second && !val)) {
                clause_sat = true;
                break;
            }
        }
        if (clause_sat) ++sat;
    }
    return static_cast<double>(sat);
}else if (method == "max3sat_v2") {

        int n = chromosome.length();

        // 只在第一次呼叫時計算並儲存子句集合
        static bool initialized = false;
        static vector<array<pair<int,bool>,3>> clauses;
        if (!initialized) {
            initialized = true;
            // 1) 隨機產生目標解
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> coin(0,1);
            vector<bool> target(n);
            for (int i = 0; i < n; ++i)
                target[i] = coin(gen) == 1;

            // 2) unit‐clause 鎖定目標解，保證唯一最優
            for (int i = 0; i < n; ++i) {
                bool pos = target[i];
                clauses.push_back({
                    make_pair(i, pos),
                    make_pair(i, pos),
                    make_pair(i, pos)
                });
            }

            // 3) 加入 m_random 條隨機 3-literal clause（此處取 4n 條，可自行調整）
            int m_random = 4 * n;
            uniform_int_distribution<> var_dist(0, n - 1);
            for (int k = 0; k < m_random; ++k) {
                int a, b, c;
                do {
                    a = var_dist(gen);
                    b = var_dist(gen);
                    c = var_dist(gen);
                } while (a == b || a == c || b == c);

                // 保證至少一個 literal 在目標解下為 true
                int guarantee = coin(gen) * 3;  // 0,1,2 任一
                array<pair<int,bool>,3> cl;
                int idxs[3] = {a, b, c};
                for (int t = 0; t < 3; ++t) {
                    int v = idxs[t];
                    bool sign;
                    if (t == guarantee) {
                        sign = target[v];
                    } else {
                        // 其它兩個隨機正負，但可讓目標解「不一定破壞」滿足
                        sign = (coin(gen) == 1) ? target[v] : !target[v];
                    }
                    cl[t] = make_pair(v, sign);
                }
                clauses.push_back(cl);
            }
        }

        // 4) 計算滿足子句數
        int sat = 0;
        for (auto& cl : clauses) {
            bool clause_sat = false;
            for (auto& lit : cl) {
                bool val = (chromosome[lit.first] == '1');
                if ((lit.second && val) || (!lit.second && !val)) {
                    clause_sat = true;
                    break;
                }
            }
            if (clause_sat) ++sat;
        }
        return static_cast<double>(sat);  

    } else if (method == "max3sat_v3") {
        int n = chromosome.length();

        // 只在第一次呼叫時計算並儲存子句集合
        static bool initialized = false;
        static vector<array<pair<int,bool>,3>> clauses;
        if (!initialized) {
            initialized = true;

            // 隨機數
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> coin(0,1);
            uniform_int_distribution<> var_dist(0, n - 1);

            // 1) 隨機產生唯一最佳解
            vector<bool> target(n);
            cout << "=== max3SAT_v2 target (length=" << n << ") ===\n";
            cout << "target = ";
            for (int i = 0; i < n; ++i) {
                target[i] = coin(gen);
                cout << (target[i] ? '1' : '0');
            }
            cout << "\n\n";

            // 印出並加入 unit‐clauses
            cout << "--- Unit clauses (" << n << ") ---\n";
            for (int i = 0; i < n; ++i) {
                bool pos = target[i];
                clauses.push_back({
                    make_pair(i, pos),
                    make_pair(i, pos),
                    make_pair(i, pos)
                });
                cout << "Clause " << i << ": "
                    << (pos ? "" : "¬") << "x" << i
                    << " ∨ " << (pos ? "" : "¬") << "x" << i
                    << " ∨ " << (pos ? "" : "¬") << "x" << i
                    << "\n";
            }
            cout << "\n";

            // 2) 加入 m_random 條隨機 3-literal clause（此處取 4n 條，可自行調整）
            int m_random = 4 * n;
            cout << "--- Random clauses (" << m_random << ") ---\n";
            for (int k = 0; k < m_random; ++k) {
                int a, b, c;
                do {
                    a = var_dist(gen);
                    b = var_dist(gen);
                    c = var_dist(gen);
                } while (a == b || a == c || b == c);

                // 保證至少一個 literal 在目標解下為 true
                int guarantee = coin(gen) % 3;
                array<pair<int,bool>,3> cl;
                int idxs[3] = {a, b, c};
                for (int t = 0; t < 3; ++t) {
                    int v = idxs[t];
                    bool sign;
                    if (t == guarantee) {
                        sign = target[v];
                    } else {
                        sign = (coin(gen) == 1) ? target[v] : !target[v];
                    }
                    cl[t] = make_pair(v, sign);
                }
                clauses.push_back(cl);

                // 印出這條 clause
                cout << "Clause " << n + k << ": ";
                for (int t = 0; t < 3; ++t) {
                    auto [idx, pos] = cl[t];
                    if (!pos) cout << "¬";
                    cout << "x" << idx;
                    if (t < 2) cout << " ∨ ";
                }
                cout << "\n";
            }
            cout << "========================================\n\n";
        }

        // 3) 計算滿足子句數
        int sat = 0;
        for (auto& cl : clauses) {
            bool clause_sat = false;
            for (auto& lit : cl) {
                bool val = (chromosome[lit.first] == '1');
                if ((lit.second && val) || (!lit.second && !val)) {
                    clause_sat = true;
                    break;
                }
            }
            if (clause_sat) ++sat;
        }
        return static_cast<double>(sat);
    }else if (method == "max3sat_random") {
        int n = chromosome.length();
        int m = 10 * n;  // 產生子句數，可依需求調整

        // 靜態變數：只在第一次呼叫時填充
        static bool generated = false;
        static vector<array<pair<int,bool>,3>> clauses;
        if (!generated) {
            generated = true;
            clauses.reserve(m);

            // 隨機數
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> var_dist(0, n - 1);
            uniform_int_distribution<> coin(0, 1);

            cout << "=== Generated max3SAT clauses (" << m << ") ===\n";
            for (int k = 0; k < m; ++k) {
                array<pair<int,bool>,3> cl;
                for (int t = 0; t < 3; ++t) {
                    int v = var_dist(gen);
                    bool sign = (coin(gen) == 1);
                    cl[t] = make_pair(v, sign);
                }
                clauses.push_back(cl);

                // 印出這條 clause
                cout << "Clause " << k << ": ";
                for (int t = 0; t < 3; ++t) {
                    auto [idx, pos] = cl[t];
                    if (!pos) cout << "¬";
                    cout << "x" << idx;
                    if (t < 2) cout << " ∨ ";
                }
                cout << "\n";
            }
            cout << "========================================\n";
        }

        // 評估 fitness = 滿足的子句數
        int sat = 0;
        for (auto& cl : clauses) {
            bool clause_sat = false;
            for (auto& lit : cl) {
                bool val = (chromosome[lit.first] == '1');
                if ((lit.second && val) || (!lit.second && !val)) {
                    clause_sat = true;
                    break;
                }
            }
            if (clause_sat) ++sat;
        }
        return static_cast<double>(sat);
    }else if (method == "max3sat_random2") {
        int n = chromosome.length();
        int m_random = 100 * n;  // 額外產生的隨機 clause 數

        // 靜態變數：只在第一次呼叫時初始化 target & clauses
        static bool generated = false;
        static vector<bool> target;
        static vector<array<pair<int,bool>,3>> clauses;

        if (!generated) {
            generated = true;
            target.assign(n, false);
            clauses.clear();
            clauses.reserve(n + m_random);

            // 1) 隨機產生唯一最佳解
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> coin(0, 1);
            cout << "=== max3SAT unique-optimum target (length=" << n << ") ===\n";
            cout << "target = ";
            for (int i = 0; i < n; ++i) {
                target[i] = (coin(gen) == 1);
                cout << (target[i] ? '1' : '0');
            }
            cout << "\n";

            // 2) 用 unit-clause 鎖定 target
            cout << "=== Unit clauses (" << n << ") ===\n";
            for (int i = 0; i < n; ++i) {
                bool pos = target[i];
                clauses.push_back({
                    make_pair(i, pos),
                    make_pair(i, pos),
                    make_pair(i, pos)
                });
                cout << "Unit " << i << ": "
                    << (pos ? "" : "¬") << "x" << i << "\n";
            }

            // 3) 加入 m_random 條隨機 3-literal clause，但保證在 target 下成立
            uniform_int_distribution<> var_dist(0, n - 1);
            cout << "=== Random clauses (" << m_random << ") ===\n";
            for (int k = 0; k < m_random; ++k) {
                // 選三個不同變數
                int a, b, c;
                do {
                    a = var_dist(gen);
                    b = var_dist(gen);
                    c = var_dist(gen);
                } while (a == b || a == c || b == c);
                int idxs[3] = {a, b, c};

                // 確保至少一個 literal 與 target 相同
                int guarantee = coin(gen) % 3;
                array<pair<int,bool>,3> cl;
                for (int t = 0; t < 3; ++t) {
                    int v = idxs[t];
                    bool sign = (t == guarantee)
                                    ? target[v]
                                    : (coin(gen) ? target[v] : !target[v]);
                    cl[t] = make_pair(v, sign);
                }
                clauses.push_back(cl);

                // 印出 Clause k
                cout << "Clause " << k << ": ";
                for (int t = 0; t < 3; ++t) {
                    auto [idx, pos] = cl[t];
                    if (!pos) cout << "¬";
                    cout << "x" << idx;
                    if (t < 2) cout << " ∨ ";
                }
                cout << "\n";
            }
            cout << "========================================\n";
        }

        // 4) 計算 fitness = 滿足的子句數
        int sat = 0;
        for (auto& cl : clauses) {
            bool clause_sat = false;
            for (auto& lit : cl) {
                bool val = (chromosome[lit.first] == '1');
                if ((lit.second && val) || (!lit.second && !val)) {
                    clause_sat = true;
                    break;
                }
            }
            if (clause_sat) ++sat;
        }
        return static_cast<double>(sat);
    } else if (method == "max3sat_random3") {
        int n = chromosome.length();
        int m_random = 4 * n;  // 隨機 clause 數

        // 靜態：第一次呼叫時初始化 target & clauses
        static bool generated = false;
        static vector<bool> target;
        static vector<array<pair<int,bool>,3>> clauses;

        if (!generated) {
            generated = true;
            target.assign(n, false);
            clauses.clear();

            // 隨機目標解
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> coin(0,1);
            uniform_int_distribution<> var_dist(0,n-1);

            cout << "=== Unique optimum target ===\n target = ";
            for (int i = 0; i < n; ++i) {
                target[i] = coin(gen);
                cout << (target[i]?'1':'0');
            }
            cout << "\n";

            // 1) pairwise clauses for every (i,j), i<j
            cout << "=== Pairwise lock-in clauses ===\n";
            for (int i = 0; i < n; ++i) {
                for (int j = i+1; j < n; ++j) {
                    // clause: (l_i ∨ l_j ∨ l_i)
                    bool l_i = target[i], l_j = target[j];
                    clauses.push_back({
                        make_pair(i, l_i),
                        make_pair(j, l_j),
                        make_pair(i, l_i)
                    });
                    // 印出
                    cout << "("
                        << (l_i?"":"¬") << "x" << i << " ∨ "
                        << (l_j?"":"¬") << "x" << j << " ∨ "
                        << (l_i?"":"¬") << "x" << i << ")\n";
                }
            }

            // 2) 再加入 m_random 條隨機但目標解可滿足的 3‐literal clause
            cout << "=== Random clauses ===\n";
            for (int k = 0; k < m_random; ++k) {
                int a,b,c;
                do {
                    a = var_dist(gen);
                    b = var_dist(gen);
                    c = var_dist(gen);
                } while (a==b||a==c||b==c);
                int idxs[3] = {a,b,c};
                int guarantee = coin(gen)%3;

                array<pair<int,bool>,3> cl;
                for (int t = 0; t < 3; ++t) {
                    int v = idxs[t];
                    bool sign = (t==guarantee)
                                    ? target[v]
                                    : (coin(gen)? target[v] : !target[v]);
                    cl[t] = make_pair(v, sign);
                }
                clauses.push_back(cl);

                // 印出
                cout << "(";
                for (int t=0;t<3;++t) {
                    auto [idx,pos] = cl[t];
                    cout << (pos?"":"¬") << "x" << idx
                        << (t<2?" ∨ ":"");
                }
                cout << ")\n";
            }
            cout << "================================\n";
        }

        // fitness = 滿足的 clause 數
        int sat=0;
        for (auto& cl: clauses) {
            bool ok=false;
            for (auto& lit: cl) {
                bool val = chromosome[lit.first]=='1';
                if ((lit.second&&val) || (!lit.second&&!val)) {
                    ok=true; break;
                }
            }
            if (ok) ++sat;
        }
        return (double)sat;
    } else if (method == "max3sat_random4") {
        int n = chromosome.length();
        int m_random = 10 * n;  // 初始隨機子句數，可依需求調整

        static bool generated = false;
        static vector<bool> target;
        static vector<array<pair<int,bool>,3>> clauses;

        if (!generated) {
            generated = true;
            target.assign(n, false);
            clauses.clear();
            clauses.reserve(m_random + (1<<n));

            // 隨機數生成器
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> coin(0,1);
            uniform_int_distribution<> var_dist(0,n-1);

            // 1) 隨機產生唯一目標解
            cout << "=== Unique-optimum target ===\n target = ";
            for (int i = 0; i < n; ++i) {
                target[i] = coin(gen);
                cout << (target[i] ? '1' : '0');
            }
            cout << "\n";

            // 2) 初始 m_random 條隨機子句（在 target 下都成立）
            cout << "=== Initial random clauses (" << m_random << ") ===\n";
            for (int k = 0; k < m_random; ++k) {
                array<pair<int,bool>,3> cl;
                for (int t = 0; t < 3; ++t) {
                    int v = var_dist(gen);
                    // 確保 literal 在 target 下成立
                    bool sign = coin(gen) ? target[v] : !target[v];
                    cl[t] = make_pair(v, sign);
                }
                clauses.push_back(cl);

                // 印出 clause
                cout << "Clause " << k << ": ";
                for (int t = 0; t < 3; ++t) {
                    auto [idx,pos] = cl[t];
                    if (!pos) cout << "¬";
                    cout << "x" << idx << (t<2?" ∨ ":"");
                }
                cout << "\n";
            }

            // 3) 阻擋所有非目標解
            cout << "=== Blocking non-target assignments ===\n";
            int clause_id = m_random;
            int total_assignments = 1 << n;
            // 檢查每一個可能的 assignment
            for (int mask = 0; mask < total_assignments; ++mask) {
                // 跳過 target
                bool is_target = true;
                for (int i = 0; i < n; ++i) {
                    if (target[i] != bool((mask>>i)&1)) {
                        is_target = false;
                        break;
                    }
                }
                if (is_target) continue;

                // 檢查此 assignment 是否滿足現有所有 clauses
                bool still_sat = true;
                for (auto& cl : clauses) {
                    bool sat_clause = false;
                    for (auto& lit : cl) {
                        bool val = bool((mask >> lit.first) & 1);
                        if ((lit.second && val) || (!lit.second && !val)) {
                            sat_clause = true;
                            break;
                        }
                    }
                    if (!sat_clause) {
                        still_sat = false;
                        break;
                    }
                }
                // 若仍然滿足，則加入一條 blocking clause
                if (still_sat) {
                    // 找出與 target 不同的位置 D
                    vector<int> D;
                    for (int i = 0; i < n; ++i) {
                        bool bval = bool((mask >> i) & 1);
                        if (bval != target[i]) D.push_back(i);
                    }
                    // 從 D 隨機選 3 個（或全部，如果 <3）
                    array<int,3> pick = {-1,-1,-1};
                    int dsize = D.size();
                    shuffle(D.begin(), D.end(), gen);
                    for (int t = 0; t < 3 && t < dsize; ++t) {
                        pick[t] = D[t];
                    }

                    array<pair<int,bool>,3> block_cl;
                    for (int t = 0; t < 3; ++t) {
                        int v = (pick[t] < 0 ? D[0] : pick[t]);
                        // 用 target[v] 作為 literal 方向
                        block_cl[t] = make_pair(v, target[v]);
                    }
                    clauses.push_back(block_cl);

                    // 印出 blocking clause
                    cout << "Clause " << clause_id++ << ": ";
                    for (int t = 0; t < 3; ++t) {
                        auto [idx,pos] = block_cl[t];
                        if (!pos) cout << "¬";
                        cout << "x" << idx << (t<2?" ∨ ":"");
                    }
                    cout << "\n";
                }
            }
            cout << "========================================\n";
        }

        // 4) 計算 fitness = 滿足的 clause 數
        int sat = 0;
        for (auto& cl : clauses) {
            bool clause_sat = false;
            for (auto& lit : cl) {
                bool val = (chromosome[lit.first] == '1');
                if ((lit.second && val) || (!lit.second && !val)) {
                    clause_sat = true;
                    break;
                }
            }
            if (clause_sat) ++sat;
        }
        return static_cast<double>(sat);
    }else if (method == "max3sat_random5") {
        int n = chromosome.length();

        // 靜態：只第一次呼叫時計算並印出 clauses
        static bool generated = false;
        static vector<array<pair<int,bool>,3>> clauses;
        if (!generated) {
            generated = true;
            clauses.clear();

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> coin(0,1);

            cout << "=== Generated sliding-window clauses for n=" << n << " ===\n";
            // 對所有 i=0..n-3 生成 (xi ∨ xi+1 ∨ xi+2)，加隨機 ¬
            for (int i = 0; i <= n - 3; ++i) {
                array<pair<int,bool>,3> cl;
                cout << "Clause " << i << ": ";
                for (int t = 0; t < 3; ++t) {
                    int idx = i + t;
                    bool positive = (coin(gen) == 1);
                    cl[t] = make_pair(idx, positive);
                    if (!positive) cout << "¬";
                    cout << "x" << idx;
                    if (t < 2) cout << " ∨ ";
                }
                cout << "\n";
                clauses.push_back(cl);
            }
            cout << "========================================\n";
        }

        // 計算 fitness = 滿足的子句數
        int sat = 0;
        for (auto& cl : clauses) {
            bool clause_sat = false;
            for (auto& lit : cl) {
                bool val = (chromosome[lit.first] == '1');
                if ((lit.second && val) || (!lit.second && !val)) {
                    clause_sat = true;
                    break;
                }
            }
            if (clause_sat) ++sat;
        }
        return static_cast<double>(sat);
    }







    std::cerr << "Error: the problem does not exist!" << std::endl;
    exit(1);
    return 0.0;
}



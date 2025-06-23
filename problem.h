#ifndef PROBLEM_H
#define PROBLEM_H

#include <string>

// Calculate weak onemax fitness for a segment
// method parameter is currently unused in this variant
double calculate_segment_onemax_weak(const std::string& segment, const std::string& method);

// Calculate segment fitness depending on method ("trap", "niah")
double calculate_segment_fitness(const std::string& segment, const std::string& method);

// Test-specific segment fitness function
double calculate_segment_fitness_test(const std::string& segment);

// Alternative weak onemax variants
double calculate_onemax_weak2(const std::string& segment, const std::string& method);
double calculate_onemax_weak3(const std::string& segment, const std::string& method);

// General fitness calculation dispatch based on method
// Supports methods: onemax, trap, niah, ctrap, cniah, cyctrap,
// leadingones, leadingtraps, test, test_equal_fitness,
// onemax_weak, multi_weak

double calculate_fitness(const std::string& chromosome, const std::string& method);

#endif // PROBLEM_H

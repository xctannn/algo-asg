#include <iostream>
#include <random>
#include <tuple>
#include <vector>

// Function to generate random outputs
std::vector<int> generateRandomOutputs(unsigned int seed, int count) {
    // Set the seed for the random number generator
    std::mt19937 rng(seed);

    // Generate random outputs
    std::vector<int> outputs;
    outputs.reserve(count);

    for (int i = 0; i < count; ++i) {
        outputs.push_back(rng());
    }

    return outputs;
}

int main() {
    // Set the seed for the random number generator
    unsigned int seed = 1191103296;

    // Number of random outputs to generate
    int count = 10;

    // Generate random outputs using the function
    std::vector<int> randomOutputs = generateRandomOutputs(seed, count);

    // Print the generated outputs
    for (int i = 0; i < count; ++i) {
        std::cout << "Output " << i + 1 << ": " << randomOutputs[i] << std::endl;
    }

    return 0;
}


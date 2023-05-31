#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <set>

std::string generateRandomWord(std::mt19937& rng, int wordLength) {
    static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    static const int alphabetSize = sizeof(alphabet) - 1;

    std::uniform_int_distribution<int> dist(0, alphabetSize - 1);

    std::string word;
    for (int i = 0; i < wordLength; ++i) {
        word += alphabet[dist(rng)];
    }

    return word;
}

void generateRandomWords(int numWords, int wordLength, const std::string& filename) {
    std::ofstream outputFile(filename);
    if (!outputFile) {
        std::cerr << "Error opening output file." << std::endl;
        return;
    }

    std::random_device rd;
    std::mt19937 rng(rd());

    std::set<char> uniqueChars;

    for (int i = 0; i < numWords; ++i) {
        std::string word = generateRandomWord(rng, wordLength);

        // Collect unique characters
        for (char c : word) {
            uniqueChars.insert(c);
        }
    }

    // Write unique characters count
    outputFile << uniqueChars.size() << std::endl;

    // Write unique characters to the file
    for (char c : uniqueChars) {
        outputFile << c << std::endl;
    }

    // Write generated words in one line separated by spaces
    outputFile << std::endl;
    for (int i = 0; i < numWords; ++i) {
        outputFile << generateRandomWord(rng, wordLength) << " ";
    }

    outputFile.close();
    std::cout << "Random words generated successfully and saved to " << filename << std::endl;
}

int main() {
    int numWords;
    int wordLength;

    // Get input from the user
    std::cout << "Enter the number of words: ";
    std::cin >> numWords;

    std::cout << "Enter the length of each word: ";
    std::cin >> wordLength;

    // Generate random words and save to a file
    std::string filename = "huffmancoding_";
    std::string paddedNumWords = std::to_string(numWords);
    paddedNumWords = std::string(8 - paddedNumWords.length(), '0') + paddedNumWords;
    filename += paddedNumWords + "_input.txt";

    generateRandomWords(numWords, wordLength, filename);

    return 0;
}

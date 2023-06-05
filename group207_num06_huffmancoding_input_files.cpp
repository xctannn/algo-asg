// *************************************************************************
// Program: group207_num06_huffmancoding_input_files.cpp
// Course: TCP2101 ALGORITHM DESIGN & ANALYSIS
// Class: TC2L
// Trimester: 2220
// Member_1: IVEN LOW ZI YIN | 1191202539@student.mmu.edu.my | 0124426389
// Member_2: RYAN THEN YE TONG | 1191302688@student.mmu.edu.my | 01113296711
// Member_3: TAN XIAO CHIN | 1191103157@student.mmu.edu.my | 0127490019
// Member_4: YAW BOON ZHE | 1191103296@student.mmu.edu.my | 01110807448
// *************************************************************************
// Task Distribution
// Member_1: Huffman Coding
// Member_2: Random input file generations
// Member_3: Kruskal with priority queue
// Member_4: Kruskal without priority queue
// *************************************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <set>

std::string generateRandomWord(std::mt19937& rng, int wordLength, const std::string& alphabet) {
    std::uniform_int_distribution<int> dist(0, alphabet.length() - 1);

    std::string word;
    for (int i = 0; i < wordLength; ++i) {
        word += alphabet[dist(rng)];
    }

    return word;
}

void generateRandomWords(int numWords, int wordLength, const std::string& alphabet, const std::string& filename) {
    std::ofstream outputFile(filename);
    if (!outputFile) {
        std::cerr << "Error opening output file." << std::endl;
        return;
    }

    std::mt19937 rng(1191103296);

    std::string outputString;
    std::set<char> uniqueChars;

    for (int i = 0; i < numWords; ++i) {
        std::string word = generateRandomWord(rng, wordLength, alphabet);

        // Collect unique characters
        for (char c : word) {
            if (uniqueChars.find(c) == uniqueChars.end()) {
                uniqueChars.insert(c);
            }
        }

        // Write generated word to file
        outputString += word + " ";
    }

    // Write unique characters count
    outputFile << uniqueChars.size() << std::endl;

    // Write unique characters to the file
    for (char c : uniqueChars) {
        outputFile << c << std::endl;
    }

    // Write generated words in one line separated by spaces
    outputFile << outputString << std::endl;

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

    // Get random set of characters from the user
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


    // Generate random words and save to a file with dynamic filename
    std::string filename = "huffmancoding_";
    std::string paddedNumWords = std::to_string(numWords);
    paddedNumWords = std::string(8 - paddedNumWords.length(), '0') + paddedNumWords;
    filename += paddedNumWords + "_input.txt";

    generateRandomWords(numWords, wordLength, alphabet, filename);

    return 0;
}


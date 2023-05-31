// *************************************************************************
// Program: group207_num02_kruskalwithoutpq_kruskalwithpq_am_input_files.cpp
// Course: TCP2101 ALGORITHM DESIGN & ANALYSIS
// Class: TC2L
// Trimester: 2220
// Member_1: YAW BOON ZHE | 1191103296@student.mmu.edu.my | 01110807448
// Member_2: TAN XIAO CHIN | 1191103157@student.mmu.edu.my | 0127490019
// Member_3: IVEN LOW ZI YIN | 1191202539@student.mmu.edu.my | 0124426389
// Member_4: RYAN THEN YE TONG | 1191302688@student.mmu.edu.my | 01113296711
// *************************************************************************
// Task Distribution
// Member_1: Kruskal with priority queue
// Member_2: Kruskal without priority queue
// Member_3: Huffman Coding
// Member_4: Random input file generations
// *************************************************************************

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
#include <set>

// Function to generate random weights between vertices
std::vector<std::vector<int>> generateAdjacencyMatrixGraph(int numVertices, std::vector<std::string>& vertexNames) {
    std::vector<std::vector<int>> graph(numVertices, std::vector<int>(numVertices, 0));

    // Set up the random number generator with the seed
    std::mt19937 rng(1191103296);
    std::uniform_int_distribution<int> weightDist(1, 9); // Adjust the range as needed

    // Generate vertex names
    const std::string nameLetter = "A";
    for (int i = 0; i < numVertices; ++i) {
        std::string vertexName = nameLetter + std::to_string(i);
        vertexNames[i] = vertexName;
    }

    // Control the number of connections between vertices
    int maxConnections = (numVertices / 5)  + 2; // Adjust the value as needed
    std::uniform_int_distribution<int> connectionsDist(0, maxConnections);

    // Populate the graph with random weights and connections
    for (int i = 0; i < numVertices; ++i) {
        int numConnections = connectionsDist(rng);

        // Generate a set of unique connection indices
        std::set<int> connectionIndices;
        while (connectionIndices.size() < numConnections) {
            int connectionIndex = std::uniform_int_distribution<int>(0, numVertices - 1)(rng);
            if (connectionIndex != i) {
                connectionIndices.insert(connectionIndex);
            }
        }

        // Connect the vertex to the selected connections
        for (int connectionIndex : connectionIndices) {
            int weight = weightDist(rng);
            graph[i][connectionIndex] = weight;
            graph[connectionIndex][i] = weight;
        }
    }

    return graph;
}

// Function to save the adjacency matrix graph to a text file
void saveAdjacencyMatrixGraphToFile(const std::vector<std::vector<int>>& graph, const std::vector<std::string>& vertexNames, int numVertices) {
    std::string filename = "kruskalwithoutpq_kruskalwithpq_am";
    std::string paddedNumVertices = std::string(8 - std::to_string(numVertices).length(), '0') + std::to_string(numVertices);
    filename += "_" + paddedNumVertices + "_input.txt";

    std::ofstream outputFile(filename);

    if (outputFile.is_open()) {
        // Save the number of vertices
        outputFile << numVertices << std::endl;

        // Save vertex names
        for (size_t i = 0; i < vertexNames.size(); ++i) {
            outputFile << i << " " << vertexNames[i] << std::endl;
        }

        // Save adjacency matrix
        for (const auto& row : graph) {
            for (const auto& weight : row) {
                if (weight == 0) {
                    outputFile << "i ";
                } else {
                    outputFile << weight << " ";
                }
            }
            outputFile << std::endl;
        }

        outputFile.close();
        std::cout << "Graph saved successfully to " << filename << std::endl;
    } else {
        std::cout << "Unable to open the file " << filename << " for writing." << std::endl;
    }
}

int main() {
    int numVertices;

    // Get the number of vertices from the user
    std::cout << "Enter the number of vertices: ";
    std::cin >> numVertices;

    // Prepare vector to hold vertex names
    std::vector<std::string> vertexNames(numVertices);

    // Generate the adjacency matrix graph and vertex names
    std::vector<std::vector<int>> graph = generateAdjacencyMatrixGraph(numVertices, vertexNames);

    // Save the adjacency matrix graph to a text file
    saveAdjacencyMatrixGraphToFile(graph, vertexNames, numVertices);

    return 0;
}

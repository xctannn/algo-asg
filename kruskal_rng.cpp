#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <iomanip> // For std::setw

// Function to generate random weights between vertices
std::vector<std::vector<int>> generateAdjacencyMatrixGraph(int numVertices, std::vector<std::string>& vertexNames) {
    std::vector<std::vector<int>> graph(numVertices, std::vector<int>(numVertices, 0));

    // Set up the random number generator with the seed
    std::mt19937 rng(1191103296);
    std::uniform_int_distribution<int> weightDist(1, 10); // Adjust the range as needed

    // Generate vertex names
    const std::string nameLetter = "A";
    for (int i = 0; i < numVertices; ++i) {
        std::string vertexName = nameLetter + std::to_string(i);
        vertexNames[i] = vertexName;
    }

    // Populate the graph with random weights
    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            int weight = weightDist(rng);
            graph[i][j] = weight;
            graph[j][i] = weight;
        }
    }

    return graph;
}

// Function to save the adjacency matrix graph to a text file
void saveAdjacencyMatrixGraphToFile(const std::vector<std::vector<int>>& graph, const std::vector<std::string>& vertexNames, int numVertices) {
    std::string filename = "kruskalwithoutpq_am";
    std::string paddedNumVertices = std::string(7 - std::to_string(numVertices).length(), '0') + std::to_string(numVertices);
    filename += "_" + paddedNumVertices + "_input.txt";

    std::ofstream outputFile(filename);

    if (outputFile.is_open()) {
        // Save the number of vertices
        outputFile << numVertices << std::endl;
        outputFile << std::endl;

        // Save vertex names
        for (size_t i = 0; i < vertexNames.size(); ++i) {
            outputFile << vertexNames[i] << std::endl;
        }
        outputFile << std::endl;

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

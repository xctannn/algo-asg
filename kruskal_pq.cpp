// *************************************************************************
// Program: group207_num04_kruskalwithpq_am_all_outputs.cpp
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
#include <sstream>
#include <queue>
#include <chrono>

class Edge{
private:
    int source; // source of the edge
    int destination; // destination of the edge
    int weight; // weight of the edge
public:
    // Constructor
    Edge(int source, int destination, int w)
    {
        this->source = source;
        this->destination = destination;
        this->weight = w;
    }

    // Getters
    int getSource() const{
        return source;
    }
    int getDestination() const{
        return destination;
    }
    int getWeight() const{
        return weight;
    }
};

// Compare class to be used for enqueueing the edges of the adjacency matrix graph
class Compare {
public:
    bool operator()(Edge a, Edge b)
    {
        if (a.getWeight() != b.getWeight()){
            return (a.getWeight() > b.getWeight()); // sort by weight first
        }
        else if (a.getSource() != b.getSource()){
            return (a.getSource() > b.getSource()); // then by the source of the edge
        }
        else{
            return (a.getDestination() > b.getDestination()); // and finally by the destination of the edge
        }
    }
};

using namespace std;
// Kruksal with priority queue dunction declarations
int find(int*, int);
void Union(int*, int , int);
bool connected(int*, int, int);
vector<Edge> KruskalMSTWithPq(priority_queue<Edge, vector<Edge>, Compare> , int*, int);
int calculateTotalWeight(vector<Edge>);

// File operation function declarations
vector<string> getVertexNames(string, int);
priority_queue<Edge, vector<Edge>, Compare> enqueueEdges(string, int);
void writeVertexCount(string, int);
bool isInteger(string);
void writeVertexNames(string, vector<string>);
void writeMST(string, vector<Edge>, vector<string>, double);

// Search for the union group that a node belongs to
int find(int* parent, int i){
    int root = i;
    while(root != parent[root])
        root = parent[root];

    // Path Compression
    while (i != root) {
        parent[i] = root; 
        // points every node under the union group 
        // directly to the root node, instead of needing 
        // to traverse through all the other nodes
        int next = parent[i];
        i = next;
    }

    return root;
}

// Combine two union groups together 
void Union(int* parent, int x, int y){
    int root1 = find(parent, x);
    int root2 = find(parent, y);
    
    parent[root2] = root1;
}

// Detect whether the two nodes are from the same union group
bool connected(int* parent, int x, int y){
    return (find(parent, x) == find(parent,y));
}

// Kruksal algorithm with priority queue to find Minimum Spanning Tree
vector<Edge> KruskalMSTWithPq(priority_queue<Edge , vector<Edge>, Compare> priorityQueue, int* parent, int vertexCount){
    vector<Edge> mst;
    int mstEdgeCount = 0;

    // initialise parent vector, every vertex's initial root points to itself
    for (int i = 0; i < vertexCount; i++){
        parent[i] = i;
    }

    while(!priorityQueue.empty()){
        Edge minCostEdge = priorityQueue.top();

        // skip edge if both nodes have the same parent
        if(connected(parent, minCostEdge.getSource(), minCostEdge.getDestination())){ // true = cycle detected
            priorityQueue.pop();
            continue;
        } 

        mst.push_back(minCostEdge);
        Union(parent, minCostEdge.getSource(), minCostEdge.getDestination());
        mstEdgeCount++;
        priorityQueue.pop();

        if(mstEdgeCount == (vertexCount - 1)) break; // Breaks when Minimum Spanning Tree has enough number of edges
    }

    return mst;
}

// Calculate total path cost of the Minimum Spanning Tree
int calculateTotalWeight(vector<Edge> mst)
{
    int totalWeight = 0;
    for (int i = 0; i < mst.size(); i++)
    {
        totalWeight += mst[i].getWeight();
    }
    return totalWeight;
}

// Parse the input file to get a vector of the names of the vertex
vector<string> getVertexNames(string inputFilename, int vertexCount)
{
    fstream inputFile;
    inputFile.open(inputFilename, ios::in);
    vector<string> vertexNames;
    string line, cell;
    int lineCount = 1;

    getline(inputFile, line); //skips first line
    while(lineCount < vertexCount + 1){
        getline(inputFile, line);
        stringstream lineStream(line);

        getline(lineStream, cell, ' ');
        getline(lineStream, cell, ' '); // get 2nd column's data
        vertexNames.push_back(cell);
        
        lineCount++;
    }

    inputFile.close();
    return vertexNames;
}

// Parse the input file to enqueue the edges in adjacency matrix graph into a priority queue
priority_queue<Edge, vector<Edge>, Compare> enqueueEdges(string inputFileName, int vertexCount)
{
    fstream inputFile;
    inputFile.open(inputFileName, ios::in);
    string line, cell;
    stringstream lineStream(line);
    priority_queue<Edge, vector<Edge>, Compare> edgeQueue;
    int n = vertexCount + 2;
    int src, dest, col = 0;
    int lineCount = 1;

    while(src < vertexCount) {
        getline(inputFile, line);
        if (line == "") break; // break when next line is blank       
        if (lineCount >= n) {
            stringstream lineStream(line);
                       
            for(dest = 0; dest < vertexCount; dest++) {
                getline(lineStream, cell, ' ');
                if(isInteger(cell) && src <= dest){ // Check for 'i' in the adjacency matrix graph && source <= destination
                    Edge newEdge = Edge(src, dest, stoi(cell));
                    edgeQueue.push(newEdge);
                }
            }
            src++;
        }
        lineCount++;
    }
    inputFile.close();
    return edgeQueue;
}

// Check if string is an integer
bool isInteger(string string)
{
    char c;
    for (int i = 0; i < string.length(); i++)
    {
        c = string[i];
        if (!isdigit(c) && c != '-')
        {
            return false;
        }
    }
    return true;
}

// Write the number of vertices in the first line of output file
void writeVertexCount(string outputFileName, int vertexCount)
{
    fstream outputFile;
    outputFile.open(outputFileName, ios::out);
    outputFile << vertexCount << endl;
    outputFile.close();
}

// Write the names of the vertices into the output file
void writeVertexNames(string outputFileName, vector<string> vertexNames)
{
    fstream outputFile;
    outputFile.open(outputFileName, fstream::app);
    string line;
    int count = 0;
    for(int i = 0; i < vertexNames.size(); i++){
        outputFile << i << " " << vertexNames[i] << endl;
    }

    outputFile.close();
}

// Writes the edges' source, destiantion and weight into the output file
void writeMST(string outputFileName, vector<Edge> mst, vector<string> vertexNames, double totalTime)
{
    fstream outputFile;
    outputFile.open(outputFileName, fstream::app);

    for (int i = 0; i < mst.size(); i++)
    {
        outputFile << vertexNames[mst[i].getSource()] << " " 
                    << vertexNames[mst[i].getDestination()] << " "
                    << mst[i].getWeight() << endl;
    }
    outputFile << calculateTotalWeight(mst) << endl;
    outputFile << totalTime << "s" << endl;
    outputFile.close();
}

int main()
{
    const int VERTEXCOUNT = 10000; // adjust this value to choose input file 
    string paddedNumVertices = string(8 - std::to_string(VERTEXCOUNT).length(), '0') + std::to_string(VERTEXCOUNT);
    string inputFileName = "kruskalwithoutpq_kruskalwithpq_am_" + paddedNumVertices + "_input.txt";
    string outputFileName = "kruskalwithpq_am_" + paddedNumVertices + "_output.txt";
    vector<string> vertexNames = getVertexNames(inputFileName, VERTEXCOUNT);
    int parent[VERTEXCOUNT]; // contains the root node of the union group of each vertices
    
    priority_queue<Edge, vector<Edge>, Compare> edgePriorityQueue;
    edgePriorityQueue = enqueueEdges(inputFileName, VERTEXCOUNT);

    auto start= chrono::steady_clock::now();
    vector<Edge> mst = KruskalMSTWithPq(edgePriorityQueue, parent, VERTEXCOUNT);
    auto end = chrono::steady_clock::now();
    chrono::duration<double> duration = end - start; // calculate execution time of Kruskal algorithm
    cout << "Duration: " << duration.count() << "s" << endl;
 
    // Results into output file
    writeVertexCount(outputFileName,VERTEXCOUNT);
    writeVertexNames(outputFileName, vertexNames);
    writeMST(outputFileName, mst, vertexNames, duration.count());
    return 0;
}
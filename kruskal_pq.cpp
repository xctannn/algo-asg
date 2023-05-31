// C++ Program to implement
// Custom Comparator in Priority Queue
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
 

class Edge{
private:
    int from;
    int to;
    int weight;
public:
    // Edge();
    Edge(int source, int destination, int w)
    {
        from = source;
        to = destination;
        weight = w;
    }
    // virtual ~Edge();

    int getFrom() const{
        return from;
    }
    int getTo() const{
        return to;
    }
    int getWeight() const{
        return weight;
    }
};

class Compare {
public:
    bool operator()(Edge a, Edge b)
    {
        return (a.getWeight() > b.getWeight());
    }
};

using namespace std;
// Kruksal with PQ
void Union(int*, int , int);
int find(int*, int);
bool connected(int*, int, int);
int kruskalMSTWithPq(priority_queue<Edge, vector<Edge>, Compare>, vector<Edge>, int*, int);
int calculateTotalWeight(vector<Edge>);

// File Operation
int getVerticesCount(string );
void readVertexName(string, vector<string> &, int, string &);
void pasteVertexName(string, string, int);
bool isInteger(string);

int find(int* parent, int i){
    int root = i;
    while(root != parent[root])
        root = parent[root];

    // Path Compression
    while (i != root) {
        int next = parent[i];
        parent[i] = root;
        i = next;
    }

    return root;
}

void Union(int* parent, int x, int y){
    int root1 = find(parent, x);
    int root2 = find(parent, y);
    
    parent[root2] = root1;
}

bool connected(int* parent, int x, int y){
    return (find(parent, x) == find(parent,y));
}

void KruskalMSTWithPq(priority_queue<Edge , vector<Edge>, Compare> priorityQueue, vector<Edge> MST, int* parent, int verticesCount){
    int mstEdgeCount = 0;
    
    for (int i = 0; i < verticesCount; i++){
        parent[i] = i;
    }

    while(!priorityQueue.empty()){
        Edge minCostEdge = priorityQueue.top();

        // skip edge if both nodes have the same parent
        if(connected(parent, minCostEdge.getFrom(), minCostEdge.getTo())){
            priorityQueue.pop();
            continue;
        } 

        MST.push_back(minCostEdge);
        std::cout << minCostEdge.getFrom() << ", " << minCostEdge.getTo() << ", " << minCostEdge.getWeight() << endl;
        Union(parent, minCostEdge.getFrom(), minCostEdge.getTo());
        mstEdgeCount++;
        priorityQueue.pop();

        if(mstEdgeCount == (verticesCount - 1)) break;
    }
}

int calculateTotalWeight(vector<Edge> mst)
{
    int totalWeight = 0;
    for (int i = 0; i < mst.size(); i++)
    {
        totalWeight += mst[i].getWeight();
    }
    return totalWeight;
}

int getVerticesCount(string fileName)
{
    fstream inputFile;
    string line;
    int verticesCount;

    inputFile.open(fileName, ios::in);
    if (inputFile.is_open())
    {
        inputFile >> line;
        verticesCount = stoi(line);
    }
    inputFile.close();
    return verticesCount;
}

void readVertexName(string inputFilename, vector<string> &vertexNameList, int vertexLineTH, string &line)
{
    fstream inputFile;
    inputFile.open(inputFilename, ios::in);
    stringstream lineStream(line);
    string cell;
    for (int i = 0; i < 2; i++)
    {
        getline(lineStream, cell, ' ');
        getline(lineStream, cell, ' ');
        vertexNameList.push_back(cell);
    }
    inputFile.close();
}

void pasteVertexName(string inputFilename, string outputFilename, int V)
{
    fstream inputFile;
    inputFile.open(inputFilename, ios::in);
    fstream outputFile;
    outputFile.open(outputFilename, fstream::app);
    string line;
    int count = 0;
    while (getline(inputFile, line))
    {
        if (count > 0 && count < V + 1)
        {
            outputFile << line << endl;
        }
        count++;
    }
    inputFile.close();
    outputFile.close();
}

priority_queue<Edge, vector<Edge>, Compare> enqueueEdges(string inputFileName, int verticesCount){
    fstream inputFile;
    inputFile.open(inputFileName, ios::in);
    string line, cell;
    stringstream lineStream(line);
    priority_queue<Edge, vector<Edge>, Compare> edgeQueue;
    int n = verticesCount + 2;
    int src, dest, col = 0;
    int lineCount = 1;

    while(src < verticesCount) {
        getline(inputFile, line);
        if (line == "") break;
        
        if (lineCount >= n) {
            stringstream lineStream(line);
                       
            for(dest = 0; dest < verticesCount; dest++) {
                getline(lineStream, cell, ' ');
                if(isInteger(cell) && src <= dest){
                    Edge newEdge = Edge(src, dest, stoi(cell));
                    std::cout << src << ", " << dest << ", " << cell << endl;
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

void writeMST(string outputFilename, vector<Edge> &mst, int totalWeight, double totalTime, vector<string> &vertexNameList)
{
    fstream outputFile;
    outputFile.open(outputFilename, fstream::app);
    for (int i = 0; i < mst.size(); i++)
    {
        outputFile << vertexNameList[mst[i].getFrom()] << " " 
                    << vertexNameList[mst[i].getTo()] << " "
                    << mst[i].getWeight() << endl;
    }
    outputFile << totalWeight << endl;
    outputFile << totalTime << "s" << endl;
    outputFile.close();
}

int main()
{
    int verticesCount = 6; // replace with first line found in input file
    string paddedNumVertices = string(7 - std::to_string(verticesCount).length(), '0') + std::to_string(verticesCount);
    string inputFileName = "kruskalwithoutpq_am_" + paddedNumVertices + "_input.txt";
    string outputFileName = "kruskalwithpq_am_" + paddedNumVertices + "_output.txt";
    vector<string> vertexNameList;
    vector<Edge> MST;
    
    priority_queue<Edge, vector<Edge>, Compare> edgePriorityQueue;
    int parent[verticesCount]; // contains the root node of the union group of each vertices
    
    edgePriorityQueue = enqueueEdges(inputFileName, verticesCount);
    std::cout << "\n";
    KruskalMSTWithPq(edgePriorityQueue, MST, parent, verticesCount);
    // std::cout << "The MST is : \n";
    // int mstCost = KruskalMSTWithPq(priorityQueue, MST, parent, verticesCount);
    // std::cout << "Total path cost of MST is: " << mstCost << endl;

    return 0;
}
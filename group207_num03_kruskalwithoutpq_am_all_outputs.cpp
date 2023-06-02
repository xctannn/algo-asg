// *************************************************************************
// Program: group207_num03_kruskalwithoutpq_am_all_outputs.cpp
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
#include <bits/stdc++.h>
#include <vector>
#include <chrono>

using namespace std;

class DSU;
class Edge;
// Kruskal algorithm without priority queue
int findParent(int, vector<DSU> &);     //find the absolute parent of the edge
void unionOperation(int, int, vector<DSU> &);   //check if the edges form a cycle in MST
void kruskalWithoutPq(vector<Edge>, vector<Edge> &, int, vector<DSU> &);    //kruskal without priority queue algorithm
int calculateTotalWeight(vector<Edge>);     //calculate the total weight of the MST generated
void setDefaultDsu(vector<DSU> &, int);     //set all dsu.parent = -1 and dsu.rank = 0 by default

// read inputFile and write outputFile
bool getNthLine(string, int, string &);     //get nth line in the file
bool isInteger(const string &);             //check whether a string is an integer
void readMatrixLine(string, int, int, vector<Edge> &);      //read edges from a line of an adjacency matrix 
void getVertex(string, int &);              //get the total number of vertices
void pasteVertexName(string, string, int);  //paste all vertices name from inputFile to outputFile
void mstToFile(string, vector<Edge>, int, double, vector<string>);   //write the MST generated, total weight, time to outputFile
void writeOutputFile(string, int);          //open an outputFile
void readVertexName(string, vector<string>&, int, string&); //read vertices name from inputFile

class DSU
{
public:
    int parent;
    int rank;
};

class Edge
{
public:
    int source;
    int dest;
    int weight;

    Edge() {}

    Edge(int s, int d, int w)
    {
        source = s;
        dest = d;
        weight = w;
    }
};

int findParent(int vertex, vector<DSU> &dsu)
{
    if (dsu[vertex].parent == -1)
    {
        return vertex;
    }
    return dsu[vertex].parent = findParent(dsu[vertex].parent, dsu);
}

void unionOperation(int sourceParent, int destParent, vector<DSU> &dsu)
{
    if (dsu[sourceParent].rank > dsu[destParent].rank)
        dsu[destParent].parent = sourceParent;
    else if (dsu[sourceParent].rank < dsu[destParent].rank)
        dsu[sourceParent].parent = destParent;
    else
    {
        dsu[sourceParent].parent = destParent;
        dsu[destParent].rank += 1;
    }
}

void kruskalWithoutPq(vector<Edge> edgeList, vector<Edge> &mst, int V, vector<DSU> &dsu)
{
    int i = 0;
    while (i < V - 1)
    {
        int min = 0;
	    for (int c = 0; c < edgeList.size(); c++){
            if(edgeList[c].weight < edgeList[min].weight){
                min = c;
            }
        }
        Edge currentEdge = edgeList[min];
        int sourceParent = findParent(currentEdge.source, dsu);
        int destParent = findParent(currentEdge.dest, dsu);
        if (sourceParent != destParent)
        {
            unionOperation(sourceParent, destParent, dsu);
            mst.push_back(currentEdge);
            ++i;
        }
        edgeList.erase(edgeList.begin() + min);
    }
}

bool getNthLine(string filename, int nth, string &line)
{
    fstream inputFile;
    inputFile.open(filename, ios::in);
    for (int i = 0; i < nth; ++i)   //skip nth-1 line to get nth line
    {
        getline(inputFile, line);
    }
    if (getline(inputFile, line))   //get nth line
    {
        return true;
    }
    inputFile.close();
    return false;
}

bool isInteger(const string &string)
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

void readMatrixLine(string line, int V, int nth, vector<Edge> &edgeList)
{
    stringstream lineStream(line);
    string cell;
    int dest = 0;
    int source = nth - (V + 1);
    for (int i = 0; i < nth; i++)
    {
        getline(lineStream, cell, ' ');
        if (isInteger(cell) && dest < V && source <= dest)
        {
            Edge newEdge = Edge(source, dest, stoi(cell));
            edgeList.push_back(newEdge);
        }
        dest += 1;
    }
}

int calculateTotalWeight(vector<Edge> mst)
{
    int totalWeight = 0;
    for (int i = 0; i < mst.size(); i++)
    {
        totalWeight += mst[i].weight;
    }
    return totalWeight;
}

void getVertex(string filename, int &V)
{
    fstream inputFile;
    string line;
    inputFile.open(filename, ios::in);
    if (inputFile.is_open())
    {
        inputFile >> line;
        V = stoi(line);
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

void mstToFile(string outputFilename, vector<Edge> mst, int totalWeight, double totalTime, vector<string> vertexNameList)
{
    fstream outputFile;
    outputFile.open(outputFilename, fstream::app);
    for (int i = 0; i < mst.size(); i++)
    {
        outputFile << vertexNameList[mst[i].source] << " " 
                    << vertexNameList[mst[i].dest] << " "
                    << mst[i].weight << endl;
    }
    outputFile << totalWeight << endl;
    outputFile << totalTime << "s" << endl;
    outputFile.close();
}

void writeOutputFile(string outputFilename, int V)
{
    fstream outputFile;
    outputFile.open(outputFilename, ios::out);
    outputFile << V << endl;
    outputFile.close();
}

void setDefaultDsu(vector<DSU> &dsuList, int V)
{
    dsuList.resize(V);
    for (int i = 0; i < V; i++)
    {
        dsuList[i].parent = -1;
        dsuList[i].rank = 0;
    }
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
        if (i == 1)
            vertexNameList.push_back(cell);
    }
    inputFile.close();
}

int main()
{
    vector<Edge> edgeList, mst;
    vector<DSU> dsuList;
    vector<string> vertexNameList;
    string line;
    const int VERTEXCOUNT = 10; // adjust this value to choose input file 
    string paddedNumVertices = string(8 - std::to_string(VERTEXCOUNT).length(), '0') + std::to_string(VERTEXCOUNT);
    string inputFilename = "kruskalwithoutpq_kruskalwithpq_am_" + paddedNumVertices + "_input.txt";
    string outputFilename = "kruskalwithoutpq_am_" + paddedNumVertices + "_output.txt";
    
    int V;
    getVertex(inputFilename, V);

    int nth = V + 1;
    while (getNthLine(inputFilename, nth, line))
    {
        readMatrixLine(line, V, nth, edgeList);
        nth += 1;
    }

    int vertexLineTH = 1;
    while (vertexLineTH < V + 1)
    {
        if (getNthLine(inputFilename, vertexLineTH, line))
        {
            readVertexName(inputFilename, vertexNameList, vertexLineTH, line);
            vertexLineTH += 1;
        }
        else
            break;
    }

    setDefaultDsu(dsuList, V);
    auto start = chrono::system_clock::now();
    kruskalWithoutPq(edgeList, mst, V, dsuList);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Duration: " << duration.count() << "s" << endl;

    int totalW = calculateTotalWeight(mst);
    writeOutputFile(outputFilename, V);
    pasteVertexName(inputFilename, outputFilename, V);
    mstToFile(outputFilename, mst, totalW, duration.count(), vertexNameList);
}
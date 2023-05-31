// *************************************************************************
// Program: group207_num01_kruskalwithoutpq_am_0000006_output.cpp
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
// Member_4: Random input  file generations
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
bool compareEdge(Edge, Edge);
int findParent(int, vector<DSU> &);
void unionOperation(int, int, vector<DSU> &);
void kruskalWithoutPq(vector<Edge> &, vector<Edge> &, int, int, vector<DSU> &);
int calculateTotalWeight(vector<Edge>);
void setDefaultDsu(vector<DSU> &, int);

// read inputFile and write output file
bool getNthLine(string, int, string &);
bool isInteger(const string &);
void readMatrixLine(string, int, int, vector<Edge> &);
void getVertex(string, int &);
void pasteVertexName(string, string, int);
void mstToFile(string, vector<Edge>, int, double, vector<string>);
void writeOutputFile(string, int);
void readVertexName(string, vector<string>&, int, string&);

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

bool compareEdge(Edge e1, Edge e2)
{
    return e1.weight < e2.weight;
}

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

void kruskalWithoutPq(vector<Edge> &edgeList, vector<Edge> &mst, int V, int E, vector<DSU> &dsu)
{
    sort(edgeList.begin(), edgeList.end(), compareEdge);

    int i = 0;
    int j = 0;
    while (i < V - 1 && j < E)
    {
        Edge currentEdge = edgeList[j];
        int sourceParent = findParent(currentEdge.source, dsu);
        int destParent = findParent(currentEdge.dest, dsu);
        if (sourceParent == destParent)
        {
            ++j;
            continue;
        }
        unionOperation(sourceParent, destParent, dsu);
        mst.push_back(edgeList[j]);
        ++i;
    }
}

bool getNthLine(string filename, int nth, string &line)
{
    fstream inputFile;
    inputFile.open(filename, ios::in);
    for (int i = 0; i < nth; ++i)
    {
        getline(inputFile, line);
    }
    if (getline(inputFile, line))
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
    string inputFilename = "kruskalwithoutpq_am_0000006_input.txt";
    string outputFilename = "kruskalwithoutpq_am_0000006_output.txt";

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
    kruskalWithoutPq(edgeList, mst, V, edgeList.size(), dsuList);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    int totalW = calculateTotalWeight(mst);

    writeOutputFile(outputFilename, V);
    pasteVertexName(inputFilename, outputFilename, V);
    mstToFile(outputFilename, mst, totalW, duration.count(), vertexNameList);
}
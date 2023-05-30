#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <vector>
#include <chrono>

using namespace std;

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

    string printEdge()
    {
        return (to_string(source) + " " + to_string(dest) + " " + to_string(weight));
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
    if(dsu[sourceParent].rank > dsu[destParent].rank)
        dsu[destParent].parent = sourceParent;
    else if(dsu[sourceParent].rank < dsu[destParent].rank)
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

int calculateTotalWeight(vector<Edge> &mst)
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

void mstToFile(string outputFilename, vector<Edge> &mst, int totalWeight, double totalTime)
{
    fstream outputFile;
    outputFile.open(outputFilename, fstream::app);
    for (int i = 0; i < mst.size(); i++)
    {
        outputFile << mst[i].printEdge() << endl;
    }
    outputFile << totalWeight << endl;
    outputFile << totalTime << "s" << endl;
    outputFile.close();
}

int main()
{
    vector<Edge> edgeList, mst;
    vector<DSU> dsuList;
    vector<string> vertexNameList;
    string line;
    string inputFilename = "input.txt";

    int V;
    getVertex(inputFilename, V);
    cout << V << endl;

    int nth = V + 1;
    while (getNthLine(inputFilename, nth, line))
    {
        readMatrixLine(line, V, nth, edgeList);
        nth += 1;
    }

    for (int i = 0; i < edgeList.size(); i++)
    {
        cout << edgeList[i].printEdge() << endl;
    }

    dsuList.resize(V);
    for(int i = 0; i < V; i++)
    {
        dsuList[i].parent = -1;
        dsuList[i].rank = -1;
    }

    auto start = chrono::system_clock::now();
    kruskalWithoutPq(edgeList, mst, V, edgeList.size(), dsuList);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    for (int i = 0; i < mst.size(); i++)
    {
        cout << mst[i].printEdge() << endl;
    }
    int totalW = calculateTotalWeight(mst);
    cout << "Duration: " << duration.count() << "s\n";

    fstream outputFile;
    string outputFilename = "output.txt";
    outputFile.open(outputFilename, ios::out);
    outputFile << V << endl;
    pasteVertexName(inputFilename, outputFilename, V);
    mstToFile(outputFilename, mst, totalW, duration.count());
    outputFile.close();
}
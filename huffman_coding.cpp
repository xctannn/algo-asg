#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int getNumChar(string filename)
{
    fstream inputfile;
    string line;
    inputfile.open(filename, ios::in);
    inputfile >> line;
    int N = stoi(line);
    inputfile.close();
    return N;
}

void readWords(string filename, int nth, vector<char>& charList)
{
    fstream inputfile;
    inputfile.open(filename, ios::in);
    string line;
    for (int i = 0; i < nth+1; ++i)   
        getline(inputfile, line);
    
    getline(inputfile, line);

    for(int i = 0; i < line.length(); i++)
    {
        if(line[i] != ' ')
        {
            charList.push_back(line[i]);
        }
    }
    inputfile.close();
}

int main()
{
    const int VERTEXCOUNT = 3; // adjust this value to choose input file 
    string paddedNumVertices = string(8 - std::to_string(VERTEXCOUNT).length(), '0') + std::to_string(VERTEXCOUNT);
    string inputFileName = "huffmancoding_" + paddedNumVertices + "_input.txt";
    string outputFileName = "huffmancoding_" + paddedNumVertices + "_output.txt";
    int N = getNumChar(inputFileName);
    vector<char> charList;
    readWords(inputFileName, N, charList);
    for(int i = 0; i < charList.size(); i++){
        cout << charList[i];
    }
}

#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <map>

using namespace std;

struct miniHeapNode
{
    int freq;
    char character;
    struct miniHeapNode *left, *right;
};

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

void countChar(vector<char> charList, map<char, int>& charFreqMap)
{
    for(int i = 0; i < charList.size(); i++)
    {
        if(charFreqMap.find(charList[i]) != charFreqMap.end())
        {
            charFreqMap[charList[i]] += 1;
        }
        else
        {
            charFreqMap[charList[i]] = 1;
        }
    }
}

int main()
{
    const int VERTEXCOUNT = 3; // adjust this value to choose input file 
    string paddedNumVertices = string(8 - std::to_string(VERTEXCOUNT).length(), '0') + std::to_string(VERTEXCOUNT);
    string inputFileName = "huffmancoding_" + paddedNumVertices + "_input.txt";
    string outputFileName = "huffmancoding_" + paddedNumVertices + "_output.txt";
    int N = getNumChar(inputFileName);
    vector<char> charList;
    map<char, int> charFreqMap;
    readWords(inputFileName, N, charList);
    for(int i = 0; i < charList.size(); i++){
        cout << charList[i];
    }
    cout << endl;
    countChar(charList, charFreqMap);
    map<char, int>::iterator it = charFreqMap.begin();
    while (it != charFreqMap.end())
    {
        cout << it->first << " " << it->second << endl;
        it++;
    }

}

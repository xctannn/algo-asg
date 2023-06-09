// *************************************************************************
// Program: group207_num07_huffmancoding_all_outputs.cpp
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
#include <vector>
#include <bits/stdc++.h>
#include <map>
#include <queue>
#include <chrono>
#include <unordered_map>
#include <iomanip>

using namespace std;

// Node structure in Huffman Tree
struct miniHeapNode
{
    int freq;
    char character;
    miniHeapNode* left;
    miniHeapNode* right;
};

//Function to allocate a new tree node
struct miniHeapNode* getNode(int freq, char character, struct miniHeapNode* left, struct miniHeapNode* right)
{
	miniHeapNode* node = new miniHeapNode();
	node->freq = freq;
	node->character = character;
	node->left = left;
	node->right = right;

	return node;
}

// Comparison to order the heap
struct compare
{
	bool operator() (const miniHeapNode* a, const miniHeapNode* b)
	{
		//highest priority has the lowest frequency
		if (a->freq != b->freq){
            return (a->freq > b->freq);
        }
        else return(a->character > b->character);

	}
};

// Function to check if a node is leaf
bool isLeaf(struct miniHeapNode* root)
{
	return root->left == nullptr && root->right == nullptr;
}

// Traverse the Huffman Tree and store codes in a map
void encode(miniHeapNode* root, string codes, map<char, string>& huffmanEncode)
{
	if (root == nullptr)
	{
		return;
	}

	//if a leaf node is found
	if(root->left == nullptr && root->right == nullptr)
	{
		huffmanEncode[root->character] = codes;
	}

	encode(root->left, codes + "0", huffmanEncode);
	encode(root->right, codes + "1", huffmanEncode);
}

//character frequency
void countChar(vector<char>& charList, map<char, int>& charFreqMap)
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


//read the words from file
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

//get the number of characters from file
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

//open new file output and write data into file
void writeOutputFile(string outputFileName, map<char, int> charFreqMap, map<char, string> huffmanEncode, double totalTime)
{

    ofstream outputFile(outputFileName);

    float bitSize = 0;
    float totalBit = 0;

    if (outputFile.is_open())
    {
        outputFile << charFreqMap.size() << endl;
        for (const auto& pair : charFreqMap)
        {
            char character = pair.first;
            int freq = pair.second;
            string code = huffmanEncode.at(character);
            int codeSize = code.size();
            int totalSize = freq * codeSize;
            outputFile << character << "  " << freq << "  " << code << "  " << totalSize << endl;
            bitSize += totalSize;
            totalBit += freq;
        }

        //calculate the total text bit （*7）
        totalBit = totalBit * 7;


        int totalSpace = (bitSize * 100) / totalBit;

        outputFile << fixed << setprecision(0) << bitSize << "-bit out of " << totalBit << "-bit" << endl;
        outputFile << "total space " << totalSpace << "%" << endl;
        outputFile << totalTime << "s" << endl;
        outputFile.close();
    }
    else
    {
        cout << "Unable to open the output file." << endl;
    }
}


void HuffmanCode(int N, vector<char> charList, string outputFileName) //sLine pending
{
    map<char, int> charFreqMap;
	auto start = chrono::system_clock::now();

	countChar(charList, charFreqMap);

	// Priority queue to store nodes of Huffman tree
    priority_queue<miniHeapNode*, vector<miniHeapNode*>, compare> priorityQueue;


	// Create leaf node and add to priority queue
	for (auto pair: charFreqMap)
	{
		priorityQueue.push(getNode(pair.second, pair.first, nullptr, nullptr));
	}

	// If not 1 node in the queue
	while (priorityQueue.size() != 1)
	{

		// Remove (POP) the 2 nodes of highest priority which is lowest frequency from the queue
		miniHeapNode* left = priorityQueue.top();
		priorityQueue.pop();
		miniHeapNode* right = priorityQueue.top();
		priorityQueue.pop();

		// Create new internal node with 2 children nodes and sum of 2 nodes for the frequency
		int sumFreq = left->freq + right->freq;

		 //Add the new node into priority queue
		priorityQueue.push(getNode(sumFreq, '\0', left, right));
	}

	//stores pointer to the root of Huffman
	miniHeapNode* root = priorityQueue.top();

	//Traverse the Huffman Tree and store the codes
	map<char, string> huffmanEncode;
	encode(root, "", huffmanEncode);

	// Get the end time and calculate duration
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;
	cout << "Duration: " << duration.count() << "s" << endl;

	// Write to the output file
    writeOutputFile(outputFileName, charFreqMap, huffmanEncode, duration.count());

    //free the allocated memory
    delete root;
}


int main()
{
    const int numofWord = 100000; // adjust this value to choose input file
    string paddedNumVertices = string(8 - std::to_string(numofWord).length(), '0') + std::to_string(numofWord);
    string inputFileName = "huffmancoding_" + paddedNumVertices + "_input.txt";
    string outputFileName = "huffmancoding_" + paddedNumVertices + "_output.txt";


    int N = getNumChar(inputFileName); // Call function to get number of character and store into N
    vector<char> charList;
    readWords(inputFileName, N, charList);
	HuffmanCode(N, charList, outputFileName); // Call function to perform Huffman Coding

	return 0;
}


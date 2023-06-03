#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <map>
#include <queue>
#include <chrono>
#include <unordered_map>

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
	bool operator() (const miniHeapNode* a, const miniHeapNode* b) const
	{
		//highest priority has the lowest frequency
		return a->freq > b->freq;
	}
};

// Function to check if tree contains only a single node
bool isLeaf(struct miniHeapNode* root)
{
	return root->left == nullptr && root->right == nullptr;
}

// Traverse the Huffman Tree and store codes in a map
void encode(miniHeapNode* root, string codes, unordered_map<char, string>& huffmanEncode)
{
	if (root == nullptr)
	{
		return;
	}

	//if a leaf node is found
	if (isLeaf(root))
	{
		huffmanEncode[root->character] = codes;
		return;
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

    //count frequecy of character and store to map
	//unordered_map<char, int> frequency;
	//for (char character: charList)
	//{
	//	charFreqMap[character]++;
	//}
}


//unordered_map<char, int> calculateFrequecy

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
void writeOutputFile(string outputFilename, map<char, int> charFreqMap, unordered_map<char, string> huffmanEncode)
{
    //fstream outputFile;
    //outputFile.open(outputFilename, ios::out);
    //outputFile << charList << endl;
    //outputFile.close();

    ofstream outputFile(outputFilename);
    //if (outputFile.is_open())
    //{
    //    for (char ch : charList)
    //    {
    //        outputFile << ch;
    //    }
     //   outputFile << endl;
    //    outputFile.close();
    //}
    //else
    //{
    //cout << "Unable to open the output file." << endl;
    //}

    //ofstream outputFile(filename);
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
        }
        outputFile.close();
    }
    else
    {
        cout << "Unable to open the output file." << endl;
    }
}


void HuffmanCode(string text, int N, vector<char> charList) //sLine pending
{
    //charList;
    map<char, int> charFreqMap;
	//auto start = chrono::system_clocl::now();

	countChar(charList, charFreqMap);

	// Priority queue to store nodes of Huffman tree
    priority_queue<miniHeapNode*, vector<miniHeapNode*>, compare> priorityQueue;


	// Create leaf node and add to priority queue
	for (auto pair: charFreqMap)
	{
		//priorityQueue.push(getNode(pair.first, pair.second, nullptr, nullptr));
		priorityQueue.push(getNode(pair.second, pair.first, nullptr, nullptr));
	}

	// If more than 1 node in the queue
	while (priorityQueue.size() > 1)
	{

		// Remove (POP) the 2 nodes of highest priority which is lowest frequency from the queue
		miniHeapNode* left = priorityQueue.top();
		priorityQueue.pop();
		miniHeapNode* right = priorityQueue.top();
		priorityQueue.pop();

		// Create new internal node with 2 children nodes and sum of 2 nodes for the frequency
		int sumfreq = left->freq + right->freq;

		// Add the new node into priority queue
		//priorityQueue.push(getNode('\0', sumfreq, left, right));
		priorityQueue.push(getNode(sumfreq, '\0', left, right));


		//if(miniHeapNode* right < miniHeapNode* left)
       // {
        //    swap(miniHeapNode* left, miniHeapNode* right)
        //}

       // for (int i = 2; i < priorityQueue.size(); i++)
       // {
       //     if(priorityQueue[i])
       // }
	}

	//stores pointer to the root of Huffman
	miniHeapNode* root = priorityQueue.top();

	//Traverse the Huffman Tree and store the codes
	unordered_map<char, string> huffmanEncode;
	encode(root, "", huffmanEncode);


 //   map<char, int>::iterator it = charFreqMap.begin();
//    map<char, string>::iterator codeIter = huffmanEncode.begin();

    //auto it = charFreqMap.begin();

    double totalBit = 0;
    int totalSize;

    string outputFileName = "huffmancoding_00000003_output.txt";
    ofstream outputFile(outputFileName);
    writeOutputFile(outputFileName, charFreqMap, huffmanEncode);


       //closest to correct
      // while (it != charFreqMap.end() && codeIter != huffmanEncode.end())
      // {
       //    outputFile << it->first << " " << it->second << " "  << codeIter->second << endl;
       //    it++;
       //    codeIter++;
       //}



    //free the allocated memory
    delete root;
}


int main()
{
    const int numofWord = 3; // adjust this value to choose input file
    string paddedNumVertices = string(8 - std::to_string(numofWord).length(), '0') + std::to_string(numofWord);
    string inputFileName = "huffmancoding_" + paddedNumVertices + "_input.txt";
    string outputFileName = "huffmancoding_" + paddedNumVertices + "_output.txt";

	ifstream inputFile;

    int N = getNumChar(inputFileName);
    vector<char> charList;
    map<char, int> charFreqMap;
    readWords(inputFileName, N, charList);


    //for(int i = 0; i < charList.size(); i++){
    //    cout << charList[i];
    //}
    cout << endl;

    string line;
	HuffmanCode(line, N, charList);
	//writeOutputFile(outputFileName, charList);
    //cout << N;

	return 0;
}


// C++ Program to implement
// Custom Comparator in Priority Queue
#include <iostream>
#include <queue>
 
// Pair of Ints = PII
using namespace std;
 
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
 
void Union(int parent[], int x, int y){
    parent[x] = y;
}

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

bool connected(int* parent, int x, int y){
    return (find(parent, x) == find(parent,y));
}

int KruskalMSTWithPq(priority_queue<Edge , vector<Edge>, Compare> priorityQueue, int* parent, int verticesCount){
    for (int i = 0; i < verticesCount; i++){
        parent[i] = i;
    }
    int sum = 0;
    int mstEdgeCount = 0;
    while(!priorityQueue.empty()){
        Edge minCostEdge = priorityQueue.top();

        // skip edge if both nodes have the same parent
        if(connected(parent, minCostEdge.getFrom(), minCostEdge.getTo())) continue;

        std::cout << minCostEdge.getFrom() << " " << minCostEdge.getTo() << " " << minCostEdge.getWeight()
             << "\n";
        priorityQueue.pop();
        sum += minCostEdge.getWeight();
        mstEdgeCount++;

        if(mstEdgeCount == (verticesCount - 1))break;
    }

    if(mstEdgeCount != verticesCount - 1) return 0;
    return sum;
}

int main()
{
    priority_queue<Edge, vector<Edge>, Compare> priorityQueue;
    priorityQueue.push(Edge(0, 1, 2));
    priorityQueue.push(Edge(0, 2, 8));
    priorityQueue.push(Edge(0, 4, 7));
    priorityQueue.push(Edge(1, 2, 5));
    priorityQueue.push(Edge(1, 3, 7));
    priorityQueue.push(Edge(2, 3, 9));
    priorityQueue.push(Edge(2, 4, 8));
    priorityQueue.push(Edge(3, 5, 4));
    priorityQueue.push(Edge(4, 5, 3));
    int n = 6; // replace with first line found in input file
    int parent[n]; // the root ndoe of the union group of each vertices
    
    std::cout << "The MST is : \n";
    int mstCost = KruskalMSTWithPq(priorityQueue, parent, n);
    std::cout << "Total path cost of MST is: " << mstCost << endl;

    return 0;
}
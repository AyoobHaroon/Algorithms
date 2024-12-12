#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <map>
#include<climits>




using namespace std;


class GraphData {
public:
    int numVertices; // Number of vertices in the graph
    vector<vector<int>> edgeList; // List of edges in the graph
    int expectedCycleLength; // Expected shortest cycle length
    string resultingCycle; // Resulting cycle

    // Constructor that reads data from a file
    GraphData(const string& fileName) {
        ifstream file(fileName);
        string line;

        // Read number of vertices
        getline(file, line);
        numVertices = stoi(line);

        // Read edges
        while (getline(file, line) && !line.empty()) {
            stringstream ss(line);
            string item;
            vector<int> edgePair;
            while (getline(ss, item, ' ')) {
                edgePair.push_back(stoi(item));
            }
            edgeList.push_back(edgePair);
        }

        // Read expected shortest cycle length
        getline(file, line);
        expectedCycleLength = stoi(line);

        // Read resulting cycle
        getline(file, line);
        resultingCycle = line;
    }

    // Print graph data
    void printData() {
        cout << "Number of vertices: " << numVertices << endl;

        printEdges(0);

        cout << "Expected shortest cycle length: " << expectedCycleLength << endl;
        cout << "Resulting cycle: " << resultingCycle << endl;
    }

    // Recursive function to print edges
    void printEdges(int i) {
        if (i < edgeList.size()) {
            for (int j = 0; j < edgeList[i].size(); j++) {
                cout << edgeList[i][j] << " ";
            }
            cout << endl;
            printEdges(i + 1);
        }
    }

    // Compute shortest cycle using Floyd-Warshall algorithm
    int computeShortestCycle() {
        vector<vector<int>> shortestPath(numVertices, vector<int>(numVertices, INT_MAX));

        initializeMatrix(shortestPath, 0);

        floydWarshall(shortestPath, 0);

        int shortestCycle = findShortestCycle(shortestPath, 0, INT_MAX);

        if (shortestCycle == INT_MAX) {
            cout << "No cycle found" << endl;
        } else {
            cout << "Shortest cycle length: " << shortestCycle << endl;
        }

        printTestResult(shortestCycle);

        return shortestCycle;
    }

    // Print test result
    void printTestResult(int result) {
        if (result == expectedCycleLength) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }


private:
    // Initialize adjacency matrix
    void initializeMatrix(vector<vector<int>>& shortestPath, int i) {
        if (i < edgeList.size()) {
            shortestPath[edgeList[i][0]][edgeList[i][1]] = 1;
            initializeMatrix(shortestPath, i + 1);
        }
    }

    // Floyd-Warshall algorithm
    void floydWarshall(vector<vector<int>>& shortestPath, int k) {
        if (k < numVertices) {
            updateShortestPath(shortestPath, k, 0);
            floydWarshall(shortestPath, k + 1);
        }
    }

    // Update shortest path matrix
    void updateShortestPath(vector<vector<int>>& shortestPath, int k, int i) {
        if (i < edgeList.size()) {
            updatePath(shortestPath, k, i, 0);
            updateShortestPath(shortestPath, k, i + 1);
        }
    }

    // Update path
    void updatePath(vector<vector<int>>& shortestPath, int k, int i, int j) {
        if (j < edgeList.size()) {
            if (shortestPath[i][k] != INT_MAX && shortestPath[k][j] != INT_MAX) {
                shortestPath[i][j] = min(shortestPath[i][j], shortestPath[i][k] + shortestPath[k][j]);
            }
            updatePath(shortestPath, k, i, j + 1);
        }
    }

    // Find shortest cycle
    int findShortestCycle(vector<vector<int>>& shortestPath, int i, int shortestCycle) {
        if (i < edgeList.size()) {
            if (shortestPath[i][i] != INT_MAX) {
                shortestCycle = min(shortestCycle, shortestPath[i][i]);
            }
            return findShortestCycle(shortestPath, i + 1, shortestCycle);
        } else {
            return shortestCycle;
        }
    }

};

int main() {
    GraphData graphData("testcase4.txt");
    graphData.printData();
    int result = graphData.computeShortestCycle();
    cout << "Computed shortest cycle length: " << result << endl;

    return 0;
}

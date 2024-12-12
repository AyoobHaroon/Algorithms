#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>

using namespace std;

class RouteData {
public:
    map<pair<string, string>, int> connections;
    vector<vector<string>> routes;
    double numericValue;

    RouteData(const string& filePath) {
        loadRouteData(filePath);
    }

    void printData() {
        for (const auto& connection : connections) {
            cout << connection.first.first << "-" << connection.first.second << " " << connection.second << endl;
        }

        for (const auto& route : routes) {
            for (int i = 0; i < route.size(); i++) {
                cout << route[i];
                if (i != route.size() - 1) {
                    cout << "-";
                }
            }
            cout << endl;
        }

        cout << numericValue << endl;
    }

    void addReverseEdges() {
        map<pair<string, string>, int> tempEdges = connections;
        for (const auto& edge : tempEdges) {
            pair<string, string> reverseEdge = make_pair(edge.first.second, edge.first.first);
            connections[reverseEdge] = edge.second;
        }
    }

    void displayAllRoutes(int index = 0) {
        if (index >= routes.size()) {
            cout << "Number of routes: " << routes.size() << endl;
            return;
        }

        const auto& route = routes[index];
        int totalCost = 0;
        int i = 0;
        while (i < route.size() - 1) {
            pair<string, string> connection = make_pair(route[i], route[i + 1]);
            totalCost += connections[connection];
            i++;
        }

        cout << "Route: ";
        i = 0;
        while (i < route.size()) {
            cout << route[i];
            if (i != route.size() - 1) {
                cout << "-";
            }
            i++;
        }
        cout << " Cost: " << totalCost << endl;

        displayAllRoutes(index + 1);
    }

    double averageTimeToMoveBetweenLocations(int index = 0, double totalTime = 0) {
        if (index >= routes.size()) {
            return totalTime / routes.size();
        }

        const auto& route = routes[index];
        int routeCost = 0;
        int i = 0;
        while (i < route.size() - 1) {
            pair<string, string> connection = make_pair(route[i], route[i + 1]);
            routeCost += connections[connection];
            i++;
        }
        totalTime += routeCost;

        return averageTimeToMoveBetweenLocations(index + 1, totalTime);
    }

private:
    void loadRouteData(const string& filePath) {
        ifstream dataFile(filePath);
        string dataLine;

        // Read the connections
        while (getline(dataFile, dataLine) && !dataLine.empty()) {
            stringstream dataStream(dataLine);
            string connection, value;
            getline(dataStream, connection, ' ');
            pair<string, string> connectionPair = make_pair(connection.substr(0, 1), connection.substr(2, 1));
            getline(dataStream, value);
            connections[connectionPair] = stoi(value);
        }

        // Read the routes
        while (getline(dataFile, dataLine) && !dataLine.empty()) {
            vector<string> route;
            stringstream dataStream(dataLine);
            string value;
            while (getline(dataStream, value, '-')) {
                route.push_back(value);
            }
            routes.push_back(route);
        }

        // Read the numeric value
        dataFile >> numericValue;
    }
};

int main() {

    RouteData routeData("test3.txt");
    routeData.printData();
    routeData.addReverseEdges();
    routeData.displayAllRoutes();
    double averageTime = routeData.averageTimeToMoveBetweenLocations();
    cout << "Average travel time: " << fixed << setprecision(1) << averageTime << endl;
    if (abs(averageTime - routeData.numericValue) < 0.1) {
        cout << "Test passed: Average time is equal to numeric value to one decimal place." << endl;
    } else {
        cout << "Test failed: Average time is not equal to numeric value to one decimal place." << endl;
    }
    return 0;
}
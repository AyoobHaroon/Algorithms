#include<iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <map>
using namespace std;

void readFile(const string& filename, int& n, vector<vector<pair<int, int>>>& coordinates, vector<int>& prices) {
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        getline(file, line);
        n = stoi(line);

        while (getline(file, line)) {
            vector<pair<int, int>> tempCoordinates;
            int price;
            stringstream ss(line);
            string part;

            while (getline(ss, part, ',')) {
                if (part[0] == '(') {
                    int x = stoi(part.substr(1));
                    getline(ss, part, ',');
                    int y = stoi(part.substr(0, part.size() - 1));
                    tempCoordinates.push_back({x, y});
                } else if (part[0] == '{') {
                    price = stoi(part.substr(1, part.size() - 2));
                }
            }

            coordinates.push_back(tempCoordinates);
            prices.push_back(price);
        }

        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

//cout data from the file
void coutData(int n, vector<vector<pair<int, int>>>& coordinates, vector<int>& prices) {
    cout << n << endl;

    for (int i = 0; i < coordinates.size(); i++) {
        for (int j = 0; j < coordinates[i].size(); j++) {
            cout << "(" << coordinates[i][j].first << "," << coordinates[i][j].second << "),";
        }

        cout << "{" << prices[i] << "}" << endl;
    }
}


//function to find path and max profit
int maxProfit(int n, vector<vector<pair<int, int>>>& coordinates, vector<int>& prices) {
    vector<int> dp(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < coordinates.size(); j++) {
            for (auto& p : coordinates[j]) {
                int area = p.first * p.second;
                if (i >= area) {
                    dp[i] = max(dp[i], dp[i - area] + prices[j]);
                }
            }
        }
    }

    return dp[n];
}

map<int, int> memo;

int maxProfitmemo(int n, vector<vector<pair<int, int>>>& coordinates, vector<int>& prices) {
    if (n == 0) return 0;
    if (memo.find(n) != memo.end()) return memo[n];

    int max_profit = 0;
    for (int j = 0; j < coordinates.size(); j++) {
        for (auto& p : coordinates[j]) {
            int area = p.first * p.second;
            if (n >= area) {
                max_profit = max(max_profit, prices[j] + maxProfitmemo(n - area, coordinates, prices));
            }
        }
    }

    memo[n] = max_profit;
    return max_profit;
}


vector<int> memo1;

int maxProfitmemo2(int n, vector<vector<pair<int, int>>>& coordinates, vector<int>& prices) {
    if (memo1.empty()) {
        memo1.resize(n + 1, -1);
        memo1[0] = 0;
    }

    if (memo1[n] != -1) return memo1[n];

    int max_profit = 0;
    for (int j = 0; j < coordinates.size(); j++) {
        for (auto& p : coordinates[j]) {
            int area = p.first * p.second;
            if (n >= area) {
                max_profit = max(max_profit, prices[j] + maxProfitmemo2(n - area, coordinates, prices));
            }
        }
    }

    memo1[n] = max_profit;
    return max_profit;
}





int main() {
    int n;
    vector<vector<pair<int, int>>> coordinates;
    vector<int> prices;

    readFile("testcase.txt", n, coordinates, prices);
    coutData(n, coordinates, prices);

    vector<int> memo(n+1, -1);
   //cout wothout memoization
    cout << "Max Profit: " << maxProfit(n, coordinates, prices) << endl;

    //cout with memo
    cout<<"Max Profit with memo: "<<maxProfitmemo(n, coordinates, prices)<<endl;
   //
    cout<<"Max Profit with memo2: "<<maxProfitmemo2(n, coordinates, prices)<<endl;
    return 0;
}
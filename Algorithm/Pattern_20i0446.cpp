#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include<map>

using namespace std;

struct TestCase {
    int rows;
    int cols;
    vector<vector<char>> matrix;
    string pattern;
    int expectedResult;
};

TestCase readTestCase(const string& fileName) {
    ifstream file(fileName);
    TestCase testCase;
    string line;

    // Read the matrix size indicator
    getline(file, line);
    line = line.substr(2, line.size() - 3); // Remove "T(" and ")"
    stringstream ss(line);
    string item;
    getline(ss, item, 'x');
    testCase.rows = stoi(item);
    getline(ss, item);
    testCase.cols = stoi(item);

    // Read the matrix
    for (int i = 0; i < testCase.rows; ++i) {
        getline(file, line);
        vector<char> row;
        stringstream ss(line);
        string item;
        while (getline(ss, item, ',')) {
            if (!item.empty()) {
                row.push_back(item[0]);
            }
        }
        testCase.matrix.push_back(row);
    }
    // Skip the empty line
    getline(file, line);

    // Read the pattern
    getline(file, testCase.pattern);

    // Read the expected result
    file >> testCase.expectedResult;

    return testCase;
}

void printMatrix(const vector<vector<char>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& item : row) {
            cout << item << " ";
        }
        cout << endl;
    }
}

void printTestCase(const TestCase& testCase) {
    cout << "Matrix size: " << testCase.rows << "x" << testCase.cols << endl;
    cout << "Matrix:" << endl;
    printMatrix(testCase.matrix);
    cout << "Pattern: " << testCase.pattern << endl;
    cout << "Expected result: " << testCase.expectedResult << endl;
}

//convert the pattern string to a matrix
vector<vector<char>> convertPatternToMatrix(const string& pattern) {
    vector<vector<char>> matrix;
    int n = pattern.size();
    int m = 1;
    while (m * m < n) {
        ++m;
    }
    int index = 0;
    for (int i = 0; i < m; ++i) {
        vector<char> row;
        for (int j = 0; j < m; ++j) {
            if (index < n) {
                row.push_back(pattern[index]);
                ++index;
            }
        }
        matrix.push_back(row);
    }
    return matrix;
}
/*
There must be a minimum of two blocks (occurrences) of
the pattern in the diagonal positions. More
than two blocks
are also permissible. Otherwise, the diagonal pattern is considered
non-existent.
In simple words, even if you found multiple occurrences throughout the array that are not diagonal, then just return 0, For example:

A,B,C,A,B,
F,G,H,F,G,
K,L,M,N,O,
P,Q,R,S,T,
U,V,W,X,Y

ABFG

*/

//function to find the diagonal pattern two blocks (occurrences) of the pattern in the diagonal positions
int findDiagonalPattern(const vector<vector<char>>& matrix, const vector<vector<char>>& pattern) {
    int n = matrix.size();
    int m = pattern.size();
    int count = 0;
    for (int i = 0; i <= n - m; ++i) {
        for (int j = 0; j <= n - m; ++j) {
            bool found = true;
            for (int k = 0; k < m; ++k) {
                for (int l = 0; l < m; ++l) {
                    if (matrix[i + k][j + l] != pattern[k][l]) {
                        found = false;
                        break;
                    }
                }
                if (!found) {
                    break;
                }
            }
            if (found) {
                ++count;
            }
        }
    }
    return count >= 2 ? count : 0;
}

//function to check expected result with the actual result
void checkResult(const TestCase& testCase, int actualResult) {
    if (testCase.expectedResult == actualResult) {
        cout<<"Actual result: "<<actualResult<<endl;
        cout << "Test case passed" << endl;

    }
    else {
        cout << "Test case failed" << endl;
        cout << "Expected result: " << testCase.expectedResult << endl;
        cout << "Actual result: " << actualResult << endl;
    }
}

int main() {
    TestCase testCase = readTestCase("test2.txt");
    printTestCase(testCase);

    vector<vector<char>> pattern = convertPatternToMatrix(testCase.pattern);
    int actualResult = findDiagonalPattern(testCase.matrix, pattern);
    checkResult(testCase, actualResult);

    return 0;
}
#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using boost::multiprecision::int128_t;

vector<int128_t> getRow(long long rowIndex) {
    vector<vector<int128_t>> pascalTriangle(2);

    for(long long i = 0; i <= rowIndex; i++) {
        pascalTriangle[(i) % 2] = vector<int128_t>(i + 1, 1);
        for(long long j = 1; j < i; j++) {
            pascalTriangle[(i) % 2][j] =
                pascalTriangle[(i - 1) % 2][j - 1] + 
                pascalTriangle[(i - 1) % 2][j];
        }
    }
    return pascalTriangle[(rowIndex) % 2];
}

int main() {
    int rowIndex;
    cout << "Enter a row index: "; cin >> rowIndex;
    auto row = getRow(rowIndex);
    
    for(auto element: row)
        cout << element << " ";
    return 0;
}
#include <iostream>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <chrono>

// TODO: cleanup

using namespace std;

void test() {

}

int main() {
    test();

    int n = 30, k = 3239;

    n--; k--;
    string row = "0";
    while(n--) {
        string homomorphism = "";
        for(char symbol: row) {
            if(symbol == '0')
                homomorphism += "01";
            else if(symbol == '1')
                homomorphism += "10";
        }
        row = homomorphism;
        cout << row << endl << endl;
    }
    cout << row[k] - '0' << endl;

    return 0;
}
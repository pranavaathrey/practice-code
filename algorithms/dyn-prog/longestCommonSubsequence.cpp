#include <iostream>
#include <vector>

using namespace std;

class longestCommonSubsequence {
    string str1, str2;
    int m, n;
    vector<vector<int>> length;
    vector<vector<char>> arrow;

    public:
    longestCommonSubsequence(string str1, string str2) {
        this->str1 = str1; 
        this->str2 = str2;
        m = str1.size(); 
        n = str2.size();
        length = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
        arrow = vector<vector<char>>(m, vector<char>(n, 'O'));
    }

    int size() {
        for(int i = 1; i <= m; i++) 
            for(int j = 1; j <= n; j++) {
                if(str1[i - 1] == str2[j - 1]) {
                    length[i][j] = length[i - 1][j - 1] + 1;
                    arrow[i - 1][j - 1] = '\\';
                } else {
                    if(length[i - 1][j] > length[i][j - 1]) {
                        length[i][j] = length[i - 1][j];
                        arrow[i - 1][j - 1] = '|';
                    } else {
                        length[i][j] = length[i][j - 1];
                        arrow[i - 1][j - 1] = '_';
                    }
                }
            }
        return length[m][n];
    }
    void buildLCSstring(int i, int j, string &str) {
        if(i < 0 || j < 0)
            return;
        
        if(arrow[i][j] == '\\') {
            buildLCSstring(i - 1, j - 1, str);
            str += str1.at(i);
        } else if(arrow[i][j] == '|') 
            buildLCSstring(i - 1, j, str);
        else
            buildLCSstring(i, j - 1, str);
    }
    string getLCSstring() {
        string LCSstr;
        buildLCSstring(m - 1, n - 1, LCSstr);
        return LCSstr;
    }
};

int main() {
    string str1, str2;
    cout << "Enter a pair of strings: " << endl;
    cin >> str1; cin >> str2;

    longestCommonSubsequence LCS(str1, str2);
    cout << "Length of the longest common subsequence: "
         << LCS.size() << endl;
    cout << "The LCS of input string: " << LCS.getLCSstring();
    return 0;
}
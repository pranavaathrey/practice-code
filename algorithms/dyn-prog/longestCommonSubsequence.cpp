#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class LCS {
    string str1, str2;
    vector<vector<int>> length;
    vector<vector<char>> arrow;

    int getLength() {
        for(int i = 1; i <= str1.length(); i++) 
            for(int j = 1; j <= str2.length(); j++) {
                if(str1[i - 1] == str2[j - 1]) {
                    length[i][j] = length[i - 1][j - 1] + 1;
                    arrow[i][j] = '\\';
                } else {
                    if(length[i - 1][j] > length[i][j - 1]) {
                        length[i][j] = length[i - 1][j];
                        arrow[i][j] = '|';
                    } else {
                        length[i][j] = length[i][j - 1];
                        arrow[i][j] = '-';                        
                    }
                }
            }
        return length[str1.length()][str2.length()];
    }
    string getLCS(int i, int j) {
        if(i == 0 || j == 0)
            return "";

        if(arrow[i][j] == '\\') 
            return getLCS(i - 1, j - 1) + str1[i - 1];
        else    if(arrow[i][j] == '|')
            return getLCS(i - 1, j);
        else // if(arrow[i][j] == '-')
            return getLCS(i, j - 1);
    }

    public:
    string LCSstring;

    LCS(const string &str1, const string &str2): str1(str1), str2(str2) {
        length = vector<vector<int>>(str1.length() + 1, 
                         vector<int>(str2.length() + 1, 0));
        arrow = vector<vector<char>>(str1.length() + 1, 
                        vector<char>(str2.length() + 1, '\0'));        
        getLength(); 
        LCSstring = getLCS(str1.length(), str2.length());
    }
};

int main() {
    LCS lcs("stone", "lemon");
    cout << lcs.LCSstring;
}
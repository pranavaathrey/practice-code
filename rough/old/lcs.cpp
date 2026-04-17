#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> length;
vector<vector<char>> arrow;
string str;

int getLCSlength(string a, string b) {
    int m = a.length(), n = b.length(); str = a;
    length = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
    arrow = vector<vector<char>>(m + 1, vector<char>(n + 1, 'o'));

    for(int i = 1; i < m + 1; i++) 
        for(int j = 1; j < n + 1; j++) {
            if(a[i - 1] == b[j - 1]) {
                length[i][j] = 1 + length[i - 1][j - 1];
                arrow[i][j] = '\\';
            } else {
                if(length[i - 1][j] > length[i][j - 1]) {
                    length[i][j] = length[i - 1][j];
                    arrow[i][j] = '|';
                } else {
                    length[i][j] = length[i][j - 1];
                    arrow[i][j] = '_';
                }
            }
        }
    return length[m][n];
}
string getLCSstring(int i, int j, string lcs) {
    if(i <= 0 || j <= 0) return lcs;

    if(arrow[i][j] == '|')
        return getLCSstring(i - 1, j, lcs);
    if(arrow[i][j] == '_')
        return getLCSstring(i, j - 1, lcs);
    return getLCSstring(i - 1, j - 1, str[i - 1] + lcs);
}

int main() {
    string a, b; cin >> a >> b;
    cout << getLCSlength(a, b) << endl;
    cout << getLCSstring(a.length(), b.length(), "");
}
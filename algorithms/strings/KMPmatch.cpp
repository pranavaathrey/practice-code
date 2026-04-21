#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> buildLPS(const string &pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);

    for(int i = 1, len = 0; i < m;) {
        if(pattern[i] == pattern[len]) 
            lps[i++] = ++len;
        else if(len > 0) 
            len = lps[len - 1];
        else 
            lps[i++] = 0;
    }
    return lps;
}
int KMPmatch(const string &text, const string &pattern) {
    int n = text.size();
    int m = pattern.size();

    vector<int> lps = buildLPS(pattern);
    for(int i = 0, j = 0; i < n;) {
        if(text[i] == pattern[j]) {
            i++; j++;
            if(j == m) 
                return i - j;
        } else if(j > 0) 
            j = lps[j - 1];
          else 
            i++;
    }
    return -1;
}

int main() {
    string text, pattern;
    cout << "Enter text: ";
    if(!getline(cin, text)) return 0;
    cout << "Enter pattern: ";
    if(!getline(cin, pattern)) return 0;
    cout << KMPmatch(text, pattern) << "\n";
    return 0;
}
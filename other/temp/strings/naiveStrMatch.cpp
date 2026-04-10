#include <iostream>
#include <string>

using namespace std;

int naiveMatch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m == 0) return 0;

    for(int i = 0, j; i <= n - m; i++) {
        for(j = 0; j < m; j++) 
            if(text[i + j] != pattern[j]) 
                break;
        if(j == m) return i;
    }
    return -1;
}

int main() {
    string text, pattern;
    if (!getline(cin, text)) return 0;
    if (!getline(cin, pattern)) return 0;

    cout << naiveMatch(text, pattern) << "\n";
    return 0;
}
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int naiveMatch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    for(int i = 0, j; i <= n - m; i++) {
        for(j = 0; j < m; j++) 
            if(text[i + j] != pattern[j]) 
                break;
        if(j == m) return i;
    }
    return -1;
}

int main() {
    cout << "Enter searchspace text: ";
    string text; getline(cin, text);
    cout << "Enter pattern to match: ";
    string pattern; getline(cin, pattern);
    
    cout << "Searching... " << endl;
    int index = naiveMatch(text, pattern);

    if(index != -1)
        cout << "Pattern found at index " << index << endl;    
    else
        cout << "Pattern not found :(" << endl;    
    return 0;
}
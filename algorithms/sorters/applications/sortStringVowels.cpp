#include <iostream>

using namespace std;

class Solution {
    private:
    bool isVowel(char ch) {
        ch = tolower(ch);
        if(ch == 'a' || ch == 'e' || ch == 'i' 
        || ch == 'o' || ch == 'u')
            return true;
        return false;
    }
    public:
    string sortVowels(string s) {
        int len = s.length();
        for(int i = 0; i < len; i++) {
            if(!isVowel(s[i])) 
                continue;
            for(int j = i; j < len; j++) {
                if(isVowel(s[j]) && s[j] < s[i])
                    swap(s[j], s[i]);
            }
        }
        return s;
    }
};

int main() {
    Solution s;
    string input; cin >> input;
    cout << s.sortVowels(input);
    return 0;
}
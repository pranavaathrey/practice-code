#include <iostream>
#include <vector>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;
using namespace std;

class NumberToWords {
    private:
    inline static const vector<string> under20 = {
        "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", 
        "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
    };
    inline static const vector<string> tens = {
        "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
    };
    inline static const vector<pair<int128_t, string>> scales = {
        {int128_t("1000000000000000000000000000000000"), "Decillion"},
        {int128_t("10000000000000000000000000000000"), "Nonillion"},
        {int128_t("1000000000000000000000000000"), "Octillion"},
        {int128_t("1000000000000000000000000"), "Septillion"},
        {int128_t("1000000000000000000000"), "Sextillion"},
        {int128_t("1000000000000000000"), "Quintillion"},
        {int128_t("1000000000000000"), "Quadrillion"},
        {int128_t("1000000000000"), "Trillion"},
        {int128_t("1000000000"), "Billion"},
        {int128_t("1000000"), "Million"},
        {int128_t("1000"), "Thousand"}
    };
    static string helper(int128_t num) {
        if (num == 0) return "";
        if (num < 20) return under20[(size_t)num] + " ";
        if (num < 100) return tens[(size_t)(num / 10)] + " " + helper(num % 10);
        return under20[(size_t)(num / 100)] + " Hundred " + helper(num % 100);
    }

    public:
    static string numberToWords(int128_t num) {
        if (num == 0) return "Zero";
        
        string res = "";
        for (const auto& scale : scales) {
            if (num >= scale.first) {
                res += helper(num / scale.first) + scale.second + " ";
                num %= scale.first;
            }
        }
        res += helper(num);
        size_t last = res.find_last_not_of(' '); // trim trailing spaces
        return (last == string::npos) ? res : res.substr(0, last + 1);
    }
};

int main() {
    int128_t input;
    if (cin >> input) 
        cout << NumberToWords::numberToWords(input) << endl;
    return 0;
}
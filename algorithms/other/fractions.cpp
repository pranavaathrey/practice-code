#include <iostream>
#include <numeric>
#define ll long long
using namespace std;

class Fractions {
    public:
    static string improperToMixed(int numerator, int denominator) {
        if(numerator == 0) return "0";

        string result = "";
        if((numerator < 0) ^ (denominator < 0))
            result += "-";

        ll num = abs((ll) numerator);
        ll den = abs((ll) denominator);

        result += to_string(num / den);
        num %= den;
        
        if(num == 0) return result;

        ll common = gcd(num, den);
        num /= common; den /= common;

        if(stoi(result) == 0) return to_string(num) 
                             + "/" + to_string(den);
        return result + " " + to_string(num) 
                      + "/" + to_string(den);
    }
};

int main() {
    cout << "98/4   ->  " << Fractions::improperToMixed(98, 4) << endl;
    cout << "15/3   ->  " << Fractions::improperToMixed(15, 3) << endl;
    cout << "2/4    ->  " << Fractions::improperToMixed(2, 4) << endl;
    cout << "-10/8  ->  " << Fractions::improperToMixed(-10, 8) << endl;
}

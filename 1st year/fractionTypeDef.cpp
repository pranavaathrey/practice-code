#include <iostream>
#include <iomanip>
using namespace std;

class Fraction{
    private:
    int numerator;
    int denominator;

    public:
    Fraction(int n, int d = 1){
        numerator = n;
        denominator = d;
    }
    void displayFraction(){
        cout << numerator << "/" << denominator;
    }
    float operator/(Fraction dividend){
        float quotient;

        int temp = dividend.numerator;
        dividend.numerator = dividend.denominator;
        dividend.denominator = temp;

        dividend.numerator *= numerator;
        dividend.denominator *= denominator;

        quotient = dividend.numerator / dividend.denominator;
        return quotient;
    }
};

int main() {
    int totalBill;
    cout << "Enter the total bill amount: ";
    cin >> totalBill;

    Fraction totalAmount(totalBill);
    Fraction numPeople(14);

    cout << "Each person pays (fraction): ";
    totalAmount.displayFraction();
    cout << " / ";
    numPeople.displayFraction();

    double result = totalAmount / numPeople;
    cout << fixed << setprecision(2); 
    cout << "\nEach person pays (float): " << result << endl;

    return 0;
}
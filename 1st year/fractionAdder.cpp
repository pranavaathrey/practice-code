#include <iostream>
using namespace std;

class Fraction{
    public:
    int numerator, denominator;
    
    Fraction(int n, int d){
        numerator = n; 
        denominator = d;
    }

    friend Fraction addMixedFraction(const Fraction &f1, const Fraction &f2);

    void reduce(){
        int x = gcd(numerator, denominator);
        numerator /= x;
        denominator /= x;
    }

    private:
    int gcd(int a, int b){
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
};

Fraction addMixedFraction(const Fraction &f1, const Fraction &f2){
    int sn, sd;
    
    int f1n = f1.numerator;
    int f1d = f1.denominator;
    int f2n = f2.numerator;
    int f2d = f2.denominator;
    
    if(f1d != f2d){
        f1d *= f2.denominator;
        f2d *= f1.denominator;
        
        f1n *= f2.denominator;
        f2n *= f1.denominator;
    }
    
    sn = f1n + f2n;
    sd = f1d;
    Fraction sum(sn, sd);
    sum.reduce();
    
    return sum;
}

int main(){
    int f1n, f1d, f2n, f2d;
    cin >> f1n >> f1d;
    cin >> f2n >> f2d;
    Fraction f1(f1n, f1d), f2(f2n, f2d);
    
    Fraction sum = addMixedFraction(f1, f2);
    cout << sum.numerator << "/" << sum.denominator << endl;
    
    return 0;
}

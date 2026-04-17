#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

int main() {
    int att; int tot;
    cout << "Enter att/tot: ";
    cin >> att >> tot;
    cout << "Current %: " << (double)att / tot;

    while(true) {
        string choice;
        cout << endl << "\nSkip/Go: "; 
        cin >> choice; to_lower(choice); 
        
        if(choice == "skip" || choice == "0") {
            tot++;
            cout << "Current %: " << (double)att / tot;
        } else if(choice == "go" || choice == "1") {
            att++; tot++;
            cout << "Current %: " << (double)att / tot;
        } else {
            cout << "Invalid. Try again" << endl;
        }
    }
}
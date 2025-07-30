#include <iostream>
#include <string>
using namespace std;

class LibraryItem {
    protected:
    string dueDate;
    string returnDate;
    
    int toDays(string date) {
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));
        
        int monthDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int days = year * 365 + day;
        
        for (int i = 1; i < month; i++) days += monthDays[i];
        
        days += (year / 4 - year / 100 + year / 400);
        
        if (month > 2 && isLeap(year)) days += 1;
        
        return days;
    }
    
    bool isLeap(int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }
    
    int getDaysLate() {
        int due = toDays(dueDate);
        int ret = toDays(returnDate);
        int diff = ret - due;
        return diff > 0 ? diff : 0;
    }
    
    public:
    LibraryItem(string due, string ret) : dueDate(due), returnDate(ret) {}
    
    virtual void calculateFine() = 0;
};

class Book : public LibraryItem {
    public:
    Book(string due, string ret) : LibraryItem(due, ret) {}
    void calculateFine() {
        int fine = getDaysLate() * 1;
        cout << "Due Date: " << dueDate << endl;
        cout << "Return Date: " << returnDate << endl;
        cout << "Late Fine: " << fine << endl;
    }
};

class DVD : public LibraryItem {
    public:
    DVD(string due, string ret) : LibraryItem(due, ret) {}
    void calculateFine() {
        int fine = getDaysLate() * 2;
        cout << "Due Date: " << dueDate << endl;
        cout << "Return Date: " << returnDate << endl;
        cout << "Late Fine: " << fine << endl;
    }
};

int main() {
    string due, ret;
    getline(cin, due);
    getline(cin, ret);
    
    Book book(due, ret);
    DVD dvd(due, ret);
    
    book.calculateFine();
    dvd.calculateFine();
    
    return 0;
}
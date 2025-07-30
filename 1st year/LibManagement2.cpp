#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Librarian;

class LibraryBook{
    private:
    string name;
    string author;
    int availability;
    static int issueCount; 

    public:
    LibraryBook(string name, string author){
        this->name = name;
        this->author = author;
        availability = 1;
    }
    void issueBook(){
        if(availability == 1){
            availability = 0;
            issueCount++;
            cout << "Book \"" << name << "\" issued." << endl;
        }else
            cout << "Book \"" << name << "\" unavailable." << endl;
    }
    void returnBook(){
        if(availability == 0){
            availability = 1;
            cout << "Book \"" << name << "\" returned." << endl;
        }else
            cout << "Book \"" << name << "\" was already returned." << endl;
    }
    friend class Librarian;
};
int LibraryBook::issueCount = 0;

class Librarian{
    public:
    int numberOfIssuedBooks(){
        return LibraryBook::issueCount;
    }
    void displayBooksDetails(LibraryBook book){
        if(book.availability == 1)
            cout << "Book Name: " << book.name << endl
                 << "Author: " << book.author << endl;
    }
};

int main(){
    vector<LibraryBook> books;
    Librarian librarian;

    books.emplace_back("huh", "b");
    books.emplace_back("ahuh", "c");
    books.emplace_back("bhuh", "d");

    //display available books
    cout << "\nAvailable books: " << endl;
    for(auto book: books){
        librarian.displayBooksDetails(book);
    }

    cout << endl;
    books.at(0).issueBook();
    books.at(0).issueBook();
    books.at(2).issueBook();
    books.at(1).returnBook();
    books.at(0).returnBook();

    //display available books
    cout << "\nAvailable books: " << endl;
    for(auto book: books){
        librarian.displayBooksDetails(book);
    }

    cout << "\nNumber of issued books: " 
         << librarian.numberOfIssuedBooks() << endl;

    return 0;
}
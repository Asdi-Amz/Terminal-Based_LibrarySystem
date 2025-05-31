//Header File for book logic
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

using namespace std;

class Book {
private:
    string title;
    string author;
    string isbn;
    bool available;

public:
    // Constructors
    Book();
    Book(const string& title, const string& author, const string& isbn, bool available = true);
    
    // Getters
    string getTitle() const;
    string getAuthor() const;
    string getISBN() const;
    bool isAvailable() const;
    
    // Setters
    void setTitle(const string& title);
    void setAuthor(const string& author);
    void setISBN(const string& isbn);
    void setAvailable(bool available);
    
    // Display methods
    void displayBook() const;
    string toString() const;
    
    // Search methods
    bool matchesTitle(const string& searchTitle) const;
    bool matchesAuthor(const string& searchAuthor) const;
    bool matchesISBN(const string& searchISBN) const;
};

#endif
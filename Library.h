//Header FIles for Library logid
#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include <vector>
#include <string>

using namespace std;

class Library {
private:
    vector<Book> books;
    string filename;
    
    // Helper methods
    void clearScreen() const;
    void pauseScreen() const;
    string trim(const string& str) const;
    bool isValidISBN(const string& isbn) const;
    int findBookByISBN(const string& isbn) const;

public:
    // Constructor
    Library(const string& filename = "books.txt");
    
    // File operations
    bool loadBooksFromFile();
    bool saveBooksToFile() const;
    
    // CRUD Operations
    bool addBook(const Book& book);
    void displayAllBooks() const;
    bool updateBook(const string& isbn);
    bool removeBook(const string& isbn);
    
    // Search operations
    void searchByTitle(const string& title) const;
    void searchByAuthor(const string& author) const;
    void searchByISBN(const string& isbn) const;
    
    // Menu and UI
    void displayMenu() const;
    void runLibrarySystem();
    
    // Utility
    int getTotalBooks() const;
    int getAvailableBooks() const;
    void displayStatistics() const;
};

#endif  // LIBRARY_H
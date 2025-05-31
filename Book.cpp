//Implementation File for Book src
#include "Book.h"
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;

// Default constructor
Book::Book() : title(""), author(""), isbn(""), available(true) {}

// Parameterized constructor
Book::Book(const string& title, const string& author, const string& isbn, bool available)
    : title(title), author(author), isbn(isbn), available(available) {}

// Getters
string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

string Book::getISBN() const {
    return isbn;
}

bool Book::isAvailable() const {
    return available;
}

// Setters
void Book::setTitle(const string& title) {
    this->title = title;
}

void Book::setAuthor(const string& author) {
    this->author = author;
}

void Book::setISBN(const string& isbn) {
    this->isbn = isbn;
}

void Book::setAvailable(bool available) {
    this->available = available;
}

// Display book information
void Book::displayBook() const {
    cout << setw(20) << left << title 
         << setw(20) << left << author 
         << setw(15) << left << isbn 
         << (available ? "Available" : "Not Available") << endl;
}

// Convert book to string format for file storage
string Book::toString() const {
    return title + "|" + author + "|" + isbn + "|" + (available ? "1" : "0");
}

// Helper function to convert string to lowercase for case-insensitive search
string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(),
              [](unsigned char c) { return tolower(c); });
    return result;
}

// Search methods with case-insensitive matching
bool Book::matchesTitle(const string& searchTitle) const {
    return toLowerCase(title).find(toLowerCase(searchTitle)) != string::npos;
}

bool Book::matchesAuthor(const string& searchAuthor) const {
    return toLowerCase(author).find(toLowerCase(searchAuthor)) != string::npos;
}

bool Book::matchesISBN(const string& searchISBN) const {
    return isbn.find(searchISBN) != string::npos;
}
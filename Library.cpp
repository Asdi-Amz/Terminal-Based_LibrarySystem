// Implementation for the Library logic
#include "Library.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <iomanip>

#ifdef _WIN32
#include <cstdlib>
#else
#include <cstdlib>
#endif

using namespace std;

// Constructor
Library::Library(const string &filename) : filename(filename)
{
    loadBooksFromFile();
}

// Cross-platform screen clearing
void Library::clearScreen() const
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayThankYou() {
    string thankYouArt[] = {
        "    ╔══════════════════════════════════════════════════════╗",
        "    ║     ▀▀▄▀▀ █  █ ▄▀▀▄ █▄ █ █ █   █  █ ▄▀▀▄ █  █ █      ║",
        "    ║       █   █▀▀█ █▄▄█ █▀██ ██    █▄▄█ █  █ █  █ █      ║",
        "    ║       █   █  █ █  █ █  █ █ █    ▄▄█ ▀▄▄▀ ▀▄▄▀ ▄      ║",
        "    ║                                                      ║",
        "    ║        For using the Library Management System       ║",
        "    ║                     Goodbye! 👋                      ║",
        "    ╚══════════════════════════════════════════════════════╝"
    };

    const size_t arraySize = sizeof(thankYouArt) / sizeof(thankYouArt[0]);

    // Gold to bronze gradient for elegant exit
    for (size_t i = 0; i < arraySize; ++i) {
        float ratio = static_cast<float>(i) / (arraySize - 1);
        int red = 218 - static_cast<int>(40 * ratio);
        int green = 165 - static_cast<int>(60 * ratio);
        int blue = 32 - static_cast<int>(20 * ratio);
        cout << "\033[38;2;" << red << ";" << green << ";" << blue << "m" 
             << thankYouArt[i] << "\033[0m" << endl;
    }
}


void displayLibraryShelf()
{
    cout << endl;
    string asciiArt[] = {
        " ┏━━━━━━━━━━━━━━━ L I B R A R Y S Y S T E M ━━━━━━━━━━━━━━━┓",
        " ┃ ┏━┓ ┏━┓ ┏━┓ ┏━┓ ┏━┓ ┏━┓ ┏━┓ ┏━┓ ┏━┓ ┏━┓ ┏━┓ ┏━┓ ┏━┓ ┏━┓ ┃",
        " ┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃",
        " ┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃█┃ ┃",
        " ┃ ┗━┛ ┗━┛ ┗━┛ ┗━┛ ┗━┛ ┗━┛ ┗━┛ ┗━┛ ┗━┛ ┗━┛ ┗━┛ ┗━┛ ┗━┛ ┗━┛ ┃",
        " ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"};
    // Warm golden brown gradient
    for (size_t i = 0; i < 6; ++i)
    {
        float ratio = static_cast<float>(i) / 5.0f;
        int red = 205 - static_cast<int>(60 * ratio);
        int green = 133 - static_cast<int>(50 * ratio);
        int blue = 63 - static_cast<int>(30 * ratio);
        cout << "\033[38;2;" << red << ";" << green << ";" << blue << "m"
             << asciiArt[i] << "\033[0m" << endl;
    }
}

// Pause screen for user to read output
void Library::pauseScreen() const
{
    string dummy;
    cout << "\nPress Enter to continue...";
    // cin.ignore();
    getline(cin, dummy);
}

// Trim whitespace from string
string Library::trim(const string &str) const
{
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Basic ISBN validation (checks if it contains only digits and hyphens)
bool Library::isValidISBN(const string &isbn) const
{
    if (isbn.empty())
        return false;
    for (char c : isbn)
    {
        if (!isdigit(c) && c != '-')
        {
            return false;
        }
    }
    return true;
}

// Find book index by ISBN
int Library::findBookByISBN(const string &isbn) const
{
    for (size_t i = 0; i < books.size(); ++i)
    {
        if (books[i].getISBN() == isbn)
        {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Load books from file
bool Library::loadBooksFromFile()
{
    ifstream file(filename);
    if (!file.is_open())
    {
        // Create empty file if it doesn't exist
        ofstream createFile(filename);
        if (createFile.is_open())
        {
            createFile.close();
            return true;
        }
        return false;
    }

    books.clear();
    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string title, author, isbn, availableStr;

        if (getline(ss, title, '|') &&
            getline(ss, author, '|') &&
            getline(ss, isbn, '|') &&
            getline(ss, availableStr))
        {

            bool available = (availableStr == "1");
            books.emplace_back(title, author, isbn, available);
        }
    }

    file.close();
    return true;
}

// Save books to file
bool Library::saveBooksToFile() const
{
    ofstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    for (const auto &book : books)
    {
        file << book.toString() << endl;
    }

    file.close();
    return true;
}

// Add a new book
bool Library::addBook(const Book &book)
{
    // Check if ISBN already exists
    if (findBookByISBN(book.getISBN()) != -1)
    {
        cout << "Error: A book with ISBN " << book.getISBN() << " already exists!\n";
        return false;
    }

    books.push_back(book);
    if (saveBooksToFile())
    {
        cout << "\nBook added successfully!\n";
        return true;
    }
    else
    {
        books.pop_back(); // Remove the book if save failed
        cout << "Error: Failed to save book to file!\n";
        return false;
    }
}

// Display all books
void Library::displayAllBooks() const
{
    if (books.empty())
    {
        cout << "No books in the library.\n";
        return;
    }

    cout << "\n"
         << string(80, '=') << endl;
    cout << "                        LIBRARY BOOKS COLLECTION" << endl;
    cout << string(80, '=') << endl;
    cout << setw(20) << left << "Title"
         << setw(20) << left << "Author"
         << setw(15) << left << "ISBN"
         << "Status" << endl;
    cout << string(80, '-') << endl;

    for (const auto &book : books)
    {
        book.displayBook();
    }
    cout << string(80, '=') << endl;
    cout << "Total Books: " << books.size() << endl;
}

// Update book information
bool Library::updateBook(const string &isbn)
{
    int index = findBookByISBN(isbn);
    if (index == -1)
    {
        cout << "Book with ISBN " << isbn << " not found!\n";
        return false;
    }

    cout << "\nCurrent book information:\n";
    cout << string(50, '-') << endl;
    books[index].displayBook();

    string newTitle, newAuthor, newISBN;
    int availableChoice;

    cout << "\nEnter new information (press Enter to keep current value):\n";

    // Update title
    cout << "New Title [" << books[index].getTitle() << "]: ";
    getline(cin, newTitle);
    if (!newTitle.empty())
    {
        books[index].setTitle(trim(newTitle));
    }

    // Update author
    cout << "New Author [" << books[index].getAuthor() << "]: ";
    getline(cin, newAuthor);
    if (!newAuthor.empty())
    {
        books[index].setAuthor(trim(newAuthor));
    }

    // Update ISBN
    cout << "New ISBN [" << books[index].getISBN() << "]: ";
    getline(cin, newISBN);
    if (!newISBN.empty())
    {
        newISBN = trim(newISBN);
        if (!isValidISBN(newISBN))
        {
            cout << "Invalid ISBN format! Update cancelled.\n";
            return false;
        }
        // Check if new ISBN already exists (but not for current book)
        int existingIndex = findBookByISBN(newISBN);
        if (existingIndex != -1 && existingIndex != index)
        {
            cout << "Error: A book with ISBN " << newISBN << " already exists!\n";
            return false;
        }
        books[index].setISBN(newISBN);
    }

    // Update availability
    cout << "Availability (1 for Available, 0 for Not Available) ["
         << (books[index].isAvailable() ? "1" : "0") << "]: ";
    if (cin >> availableChoice)
    {
        if (availableChoice == 0 || availableChoice == 1)
        {
            books[index].setAvailable(availableChoice == 1);
        }
    }
    cin.ignore(); // Clear input buffer

    if (saveBooksToFile())
    {
        cout << "Book updated successfully!\n";
        return true;
    }
    else
    {
        cout << "Error: Failed to save changes to file!\n";
        return false;
    }
}

// Remove a book
bool Library::removeBook(const string &isbn)
{
    int index = findBookByISBN(isbn);
    if (index == -1)
    {
        cout << "Book with ISBN " << isbn << " not found!\n";
        return false;
    }

    cout << "\nBook to be removed:\n";
    cout << string(50, '-') << endl;
    books[index].displayBook();

    char confirm;
    cout << "\nAre you sure you want to remove this book? (y/N): ";
    cin >> confirm;
    cin.ignore(); // Clear input buffer

    if (confirm == 'y' || confirm == 'Y')
    {
        books.erase(books.begin() + index);
        if (saveBooksToFile())
        {
            cout << "Book removed successfully!\n";
            return true;
        }
        else
        {
            cout << "Error: Failed to save changes to file!\n";
            return false;
        }
    }
    else
    {
        cout << "Book removal cancelled.\n";
        return false;
    }
}

// Search by title
void Library::searchByTitle(const string &title) const
{
    vector<Book> results;
    for (const auto &book : books)
    {
        if (book.matchesTitle(title))
        {
            results.push_back(book);
        }
    }

    if (results.empty())
    {
        cout << "No books found with title containing: " << title << endl;
        return;
    }

    cout << "\nSearch Results (" << results.size() << " found):\n";
    cout << string(80, '=') << endl;
    cout << setw(20) << left << "Title"
         << setw(20) << left << "Author"
         << setw(15) << left << "ISBN"
         << "Status" << endl;
    cout << string(80, '-') << endl;

    for (const auto &book : results)
    {
        book.displayBook();
    }
}

// Search by author
void Library::searchByAuthor(const string &author) const
{
    vector<Book> results;
    for (const auto &book : books)
    {
        if (book.matchesAuthor(author))
        {
            results.push_back(book);
        }
    }

    if (results.empty())
    {
        cout << "No books found by author containing: " << author << endl;
        return;
    }

    cout << "\nSearch Results (" << results.size() << " found):\n";
    cout << string(80, '=') << endl;
    cout << setw(20) << left << "Title"
         << setw(20) << left << "Author"
         << setw(15) << left << "ISBN"
         << "Status" << endl;
    cout << string(80, '-') << endl;

    for (const auto &book : results)
    {
        book.displayBook();
    }
}

// Search by ISBN
void Library::searchByISBN(const string &isbn) const
{
    vector<Book> results;
    for (const auto &book : books)
    {
        if (book.matchesISBN(isbn))
        {
            results.push_back(book);
        }
    }

    if (results.empty())
    {
        cout << "No books found with ISBN containing: " << isbn << endl;
        return;
    }

    cout << "\nSearch Results (" << results.size() << " found):\n";
    cout << string(80, '=') << endl;
    cout << setw(20) << left << "Title"
         << setw(20) << left << "Author"
         << setw(15) << left << "ISBN"
         << "Status" << endl;
    cout << string(80, '-') << endl;

    for (const auto &book : results)
    {
        book.displayBook();
    }
}

// Display main menu
void Library::displayMenu() const
{
    cout << "\n"
         << string(60, '=') << endl; // ===
    cout << string(17, ' ') << "LIBRARY MANAGEMENT SYSTEM" << endl;
    cout << string(60, '=') << endl; // ===
    cout << string(20, ' ') << "1. Add New Book" << endl;
    cout << string(20, ' ') << "2. Display All Books" << endl;
    cout << string(20, ' ') << "3. Update Book" << endl;
    cout << string(20, ' ') << "4. Remove Book" << endl;
    cout << string(20, ' ') << "5. Search by Title" << endl;
    cout << string(20, ' ') << "6. Search by Author" << endl;
    cout << string(20, ' ') << "7. Search by ISBN" << endl;
    cout << string(20, ' ') << "8. Library Statistics" << endl;
    cout << string(20, ' ') << "9. Exit" << endl;
    cout << string(60, '=') << endl; // ===
    cout << string(20, ' ') << "Enter your choice: ";
}

// Get total number of books
int Library::getTotalBooks() const
{
    return static_cast<int>(books.size());
}

// Get number of available books
int Library::getAvailableBooks() const
{
    int count = 0;
    for (const auto &book : books)
    {
        if (book.isAvailable())
        {
            count++;
        }
    }
    return count;
}

// Display library statistics
void Library::displayStatistics() const
{
    cout << "\n"
         << string(60, '=') << endl;
    cout << string(20, ' ') << "LIBRARY STATISTICS" << endl;
    cout << string(60, '=') << endl;
    cout << string(20, ' ') << "Total Books: " << getTotalBooks() << endl;
    cout << string(20, ' ') << "Available Books: " << getAvailableBooks() << endl;
    cout << string(20, ' ') << "Borrowed Books: " << (getTotalBooks() - getAvailableBooks()) << endl;
    cout << string(60, '=') << endl;
}

// Main library system loop
void Library::runLibrarySystem()
{
    int choice;
    int lenght = 20;
    string input, title, author, isbn;

    while (true)
    {
        clearScreen();
        displayLibraryShelf();
        displayMenu();

        // Input validation for menu choice
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            pauseScreen();
            continue;
        }
        cin.ignore(); // Clear input buffer

        switch (choice)
        {
        case 1:
        { // Add new book
            clearScreen();
            displayLibraryShelf();
            cout << string(lenght, ' ') << "=== ADD NEW BOOK ===\n";

            cout << "\nEnter book title: ";
            getline(cin, title);
            title = trim(title);
            if (title.empty())
            {
                cout << "Error: Title cannot be empty!\n";
                pauseScreen();
                break;
            }

            cout << "Enter author name: ";
            getline(cin, author);
            author = trim(author);
            if (author.empty())
            {
                cout << "Error: Author cannot be empty!\n";
                pauseScreen();
                break;
            }

            cout << "Enter ISBN: ";
            getline(cin, isbn);
            isbn = trim(isbn);
            if (isbn.empty() || !isValidISBN(isbn))
            {
                cout << "Error: Invalid ISBN format!\n";
                pauseScreen();
                break;
            }

            Book newBook(title, author, isbn, true);
            addBook(newBook);
            pauseScreen();
            break;
        }

        case 2: // Display all books
            clearScreen();
            displayLibraryShelf();
            displayAllBooks();
            pauseScreen();
            break;

        case 3:
        { // Update book
            clearScreen();
            displayLibraryShelf();
            cout << string(lenght, ' ') << "=== UPDATE BOOK ===\n";
            cout << "\nEnter ISBN of book to update: ";
            getline(cin, isbn);
            isbn = trim(isbn);
            if (isbn.empty())
            {
                cout << "Error: ISBN cannot be empty!\n";
            }
            else
            {
                updateBook(isbn);
            }
            pauseScreen();
            break;
        }

        case 4:
        { // Remove book
            clearScreen();
            displayLibraryShelf();
            cout << string(lenght, ' ') << "=== REMOVE BOOK ===\n";
            cout << "\nEnter ISBN of book to remove: ";
            getline(cin, isbn);
            isbn = trim(isbn);
            if (isbn.empty())
            {
                cout << "Error: ISBN cannot be empty!\n";
            }
            else
            {
                removeBook(isbn);
            }
            pauseScreen();
            break;
        }

        case 5:
        { // Search by title
            clearScreen();
            displayLibraryShelf();
            cout << string(lenght, ' ') << "=== SEARCH BY TITLE ===\n";
            cout << "\nEnter title to search: ";
            getline(cin, title);
            title = trim(title);
            if (title.empty())
            {
                cout << "Error: Search term cannot be empty!\n";
            }
            else
            {
                searchByTitle(title);
            }
            pauseScreen();
            break;
        }

        case 6:
        { // Search by author
            clearScreen();
            displayLibraryShelf();
            cout << string(lenght, ' ') << "=== SEARCH BY AUTHOR ===\n";
            cout << "\nEnter author to search: ";
            getline(cin, author);
            author = trim(author);
            if (author.empty())
            {
                cout << "Error: Search term cannot be empty!\n";
            }
            else
            {
                searchByAuthor(author);
            }
            pauseScreen();
            break;
        }

        case 7:
        { // Search by ISBN
            clearScreen();
            displayLibraryShelf();
            cout << string(lenght, ' ') << "=== SEARCH BY ISBN ===\n";
            cout << "\nEnter ISBN to search: ";
            getline(cin, isbn);
            isbn = trim(isbn);
            if (isbn.empty())
            {
                cout << "Error: Search term cannot be empty!\n";
            }
            else
            {
                searchByISBN(isbn);
            }
            pauseScreen();
            break;
        }

        case 8: // Library statistics
            clearScreen();
            displayLibraryShelf();
            displayStatistics();
            pauseScreen();
            break;

        case 9: // Exit
            clearScreen();
            displayThankYou();
            //cout << "Thank you for using the Library Management System!\n";
            //cout << "Goodbye!\n";
            return;

        default:
            cout << "Invalid choice! Please select 1-9.\n";
            pauseScreen();
            break;
        }
    }
}
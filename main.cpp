// Asdi V. Amamence (SAT MAY 31, 2025)
// The main of the Library Management System
#include "Library.h"
#include <iostream>
#include <exception>

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayLibraryTitle() {
    cout << endl;
    string asciiArt[] = {
        "    ██╗     ██╗██████╗ ██████╗  █████╗ ██████╗ ██╗   ██╗",
        "    ██║     ██║██╔══██╗██╔══██╗██╔══██╗██╔══██╗╚██╗ ██╔╝",
        "    ██║     ██║██████╔╝██████╔╝███████║██████╔╝ ╚████╔╝ ",
        "    ██║     ██║██╔══██╗██╔══██╗██╔══██║██╔══██╗  ╚██╔╝  ",
        "    ███████╗██║██████╔╝██║  ██║██║  ██║██║  ██║   ██║   ",
        "    ╚══════╝╚═╝╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝   "
    };

    // Red gradient from light to darker
    for (size_t i = 0; i < 6; ++i) {
        float ratio = static_cast<float>(i) / 5.0f;
        int red = 255;
        int green = 150 - static_cast<int>(150 * ratio);
        int blue = 150 - static_cast<int>(150 * ratio);
        cout << "\033[38;2;" << red << ";" << green << ";" << blue << "m" << asciiArt[i] << "\033[0m" << endl;
    }
}

int main() {
    try {

        clearScreen();
        displayLibraryTitle();
        // Initialize library with books.txt file
        Library library("books.txt");
        
        // Display welcome message
        cout << "\n" << string(60, '=') << endl;
        cout << "         WELCOME TO THE LIBRARY MANAGEMENT SYSTEM" << endl;
        cout << string(60, '=') << endl;
        cout << "This system allows you to manage your library's book collection." << endl;
        cout << "Features include: Add, View, Update, Delete, and Search books." << endl;
        cout << "All data is automatically saved to 'books.txt' file." << endl;
        cout << string(60, '=') << endl;
        
        cout << "\nPress Enter to continue...";
        cin.get();
        
        // Start the library management system
        library.runLibrarySystem();
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "An unknown error occurred!" << endl;
        return 1;
    }
    
    return 0;
}
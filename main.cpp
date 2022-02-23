/*---------------------------------------------------------------------------
Author: Thanushan Satheeskumar (FlamingNinja925)

Project: Register and Login System
Date Created: January 3, 2022
Date Last Modified: January 5, 2022

Description: Basic menu system where user can create an account with a username
             and password. The user can then login with the same username and
             password afterwards. The user will successfully login if their
             inputted password matches the username. They will fail if the
             password doesn't match, or if there is no account with that
             username.
---------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>

using namespace std;

//Description: Clears the output screen
//Parameters: N/A
//Returns: N/A
void clearScreen() {
    cout << "\033[2J\033[1;1H";

    return;
}

//Description: Asks the user to press a key to continue
//Parameters: N/A
//Returns: N/A
void pressToContinue() {
    cout << "Press [ENTER] to Continue...\n";
    cin.ignore();

    return;
}

//Description: Clears the screen, then displays the company's intro
//Parameters: N/A
//Returns: N/A
void displayCompanyIntro() {
    clearScreen();

    cout << "----------------------------------------------\n";
    cout << "\tWelcome to Flaming Ninja Inc.\n";
    cout << "----------------------------------------------\n\n";

    return;
}

//Description: Displays the menu, and asks the user to select an option
//Parameters: N/A
//Returns: An int value that contains the option that the user selected
int menuSelection() {
    int optionSelected;

    cout << "Select One of the Options Below (Press -1 to Quit):\n";
    cout << "(1) - Register\n";
    cout << "(2) - Login\n";
    cin >> optionSelected;

    return optionSelected;
}

//Description: Checks if a file exists
//Parameters: A string that contains the name of the file
//Returns: A bool that shows if the file exists or not
bool fileExists(string fileName) {
    ifstream file;
    file.open(fileName + ".txt");

    if (file) {
        return true;
    }
    else {
        return false;
    }

    file.close();
}

//Description: Makes a word all lowercase
//Parameters: A string that contains the word
//Returns: A string that contains the word with lowercase letters
string convertLowercase(string word) {
    for (int i = 0; i < word.length(); i++) {
        word[i] = tolower(word[i]);
    }

    return word;
}

//Description: Creates a file with the username as the file name and its password as the text inside
//Parameters: N/A
//Returns: N/A
void accountRegister() {
    string currentUsername, currentPassword;
    
    displayCompanyIntro();

    cout << "You have Selected the Register Option\n\n";
    cout << "Create a Username: ";
    cin >> currentUsername;

    currentUsername = convertLowercase(currentUsername);

    while (fileExists(currentUsername)) {
        displayCompanyIntro();

        cout << "Username Taken! (Enter -1 to Cancel)\n\n";
        cout << "Create a Username: ";
        cin >> currentUsername;

        if (currentUsername == "-1") {
            return;
        }
    }

    displayCompanyIntro();

    cout << "Username Available!\n\n";
    cout << "Create a Password: ";
    cin >> currentPassword;

    ofstream file (currentUsername + ".txt");
    file << currentPassword;
    file.close();

    cout << "\nAccount Successfully Registered\n";
    pressToContinue();
    cin.ignore();

    return;
}

//Description: Searches text files to find an account, and checks if given username and password match
//Parameters: N/A
//Returns: A bool that represents if the user has logged in or not
bool accountLogin() {
    string currentUsername, currentPassword, accountPassword;
    
    displayCompanyIntro();

    cout << "You have Selected the Login Option\n\n";
    cout << "Username: ";
    cin >> currentUsername;

    currentUsername = convertLowercase(currentUsername);

    while (!(fileExists(currentUsername))) {
        displayCompanyIntro();

        cout << "Account Does Not Exist! (Enter -1 to Cancel)\n\n";
        cout << "Username: ";
        cin >> currentUsername;

        if (currentUsername == "-1") {
            return false;
        }
    }

    displayCompanyIntro();

    cout << "Account Found!\n\n";
    cout << "Password: ";
    cin >> currentPassword;

    ifstream file (currentUsername + ".txt");
    file >> accountPassword;

    while (currentPassword != accountPassword) {
        displayCompanyIntro();

        cout << "Password is Incorrect (Enter -1 to Cancel)\n\n";
        cout << "Password: ";
        cin >> currentPassword;

        if (currentPassword == "-1") {
            return false;
        }
    }

    file.close();

    cout << "\nSuccessfully Logged into Account\n";
    pressToContinue();
    cin.ignore();

    return true;
}

int main() {
    int optionSelected;

    displayCompanyIntro();
    pressToContinue();

    while (optionSelected != -1) {
        displayCompanyIntro();
        optionSelected = menuSelection();

        if (optionSelected == 1) {
            displayCompanyIntro();
            accountRegister();
        }
        else if (optionSelected == 2) {
            displayCompanyIntro();

            if (accountLogin()) {
                clearScreen();
                return 0;
            }
        }
    }

    return 0;
}
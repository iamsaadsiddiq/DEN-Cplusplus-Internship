#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>  // For Windows-specific system commands
#else
#include <unistd.h>   // For Unix-based system commands
#endif

using namespace std;

class Contact {
private:
    string name;
    string phoneNumber;

public:
    Contact(string n, string p) : name(n), phoneNumber(p) {}

    string getName() const {
        return name;
    }

    string getPhoneNumber() const {
        return phoneNumber;
    }

    void setName(string n) {
        name = n;
    }

    void setPhoneNumber(string p) {
        phoneNumber = p;
    }

    void displayContact() const {
        cout << setw(20) << left << name << setw(15) << left << phoneNumber << endl;
    }
};

void displayMenu();
void addContact(vector<Contact>& contacts);
void viewContacts(const vector<Contact>& contacts);
void deleteContact(vector<Contact>& contacts);
void searchContact(const vector<Contact>& contacts);
void editContact(vector<Contact>& contacts);
void pressEnterToContinue();
void clearScreen();

void displayMenu() {
    cout << "\n";
    cout << "=====================================\n";
    cout << "        CONTACT MANAGEMENT SYSTEM    \n";
    cout << "=====================================\n";
    cout << "1. Add Contact\n";
    cout << "2. View All Contacts\n";
    cout << "3. Search Contact\n";
    cout << "4. Edit Contact\n";
    cout << "5. Delete Contact\n";
    cout << "6. Exit\n";
    cout << "=====================================\n";
    cout << "Please enter your choice: ";
}

void addContact(vector<Contact>& contacts) {
    string name, phoneNumber;
    cout << "\nEnter Contact Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Phone Number: ";
    getline(cin, phoneNumber);

    contacts.push_back(Contact(name, phoneNumber));
    cout << "\nContact added successfully!\n";
    pressEnterToContinue();
}

void viewContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "\nNo contacts available.\n";
    }
    else {
        cout << "\n-------------------------------------\n";
        cout << setw(20) << left << "Name" << setw(15) << left << "Phone Number" << endl;
        cout << "-------------------------------------\n";
        for (const auto& contact : contacts) {
            contact.displayContact();
        }
        cout << "-------------------------------------\n";
    }
    pressEnterToContinue();
}

void searchContact(const vector<Contact>& contacts) {
    string name;
    cout << "\nEnter the name to search: ";
    cin.ignore();
    getline(cin, name);

    bool found = false;
    for (const auto& contact : contacts) {
        if (contact.getName() == name) {
            cout << "\nContact found:\n";
            cout << setw(20) << left << "Name" << setw(15) << left << "Phone Number" << endl;
            cout << "-------------------------------------\n";
            contact.displayContact();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nContact not found.\n";
    }
    pressEnterToContinue();
}

void editContact(vector<Contact>& contacts) {
    string name;
    cout << "\nEnter the name of the contact to edit: ";
    cin.ignore();
    getline(cin, name);

    auto it = find_if(contacts.begin(), contacts.end(), [&name](const Contact& c) {
        return c.getName() == name;
        });

    if (it != contacts.end()) {
        string newPhoneNumber;
        cout << "Enter the new phone number: ";
        getline(cin, newPhoneNumber);
        it->setPhoneNumber(newPhoneNumber);
        cout << "\nContact updated successfully!\n";
    }
    else {
        cout << "\nContact not found.\n";
    }
    pressEnterToContinue();
}

void deleteContact(vector<Contact>& contacts) {
    string name;
    cout << "\nEnter the name of the contact to delete: ";
    cin.ignore();
    getline(cin, name);

    auto it = find_if(contacts.begin(), contacts.end(), [&name](const Contact& c) {
        return c.getName() == name;
        });

    if (it != contacts.end()) {
        contacts.erase(it);
        cout << "\nContact deleted successfully!\n";
    }
    else {
        cout << "\nContact not found.\n";
    }
    pressEnterToContinue();
}

void pressEnterToContinue() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void clearScreen() {
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

int main() {
    vector<Contact> contacts;
    int choice;

    do {
        clearScreen();
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            addContact(contacts);
            break;
        case 2:
            viewContacts(contacts);
            break;
        case 3:
            searchContact(contacts);
            break;
        case 4:
            editContact(contacts);
            break;
        case 5:
            deleteContact(contacts);
            break;
        case 6:
            cout << "\nExiting the program. Goodbye!\n";
            break;
        default:
            cout << "\nInvalid choice. Please try again.\n";
            pressEnterToContinue();
        }
    } while (choice != 6);

    return 0;
}

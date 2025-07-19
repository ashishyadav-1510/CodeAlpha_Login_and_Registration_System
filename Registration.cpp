#include <iostream> 
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <regex>
#include <iomanip>
#include <limits>

using namespace std;

const string USER_FILE = "users.txt";
const int MAX_ATTEMPTS = 3;

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    if (first == string::npos || last == string::npos) return "";
    return str.substr(first, last - first + 1);
}

bool isValidUsername(const string& username) {
    return regex_match(username, regex("^[a-z]+[0-9]*$"));
}

bool isValidPassword(const string& password) {
    if (password.length() < 6) return false;
    bool hasLetter = false, hasDigit = false, hasSpecial = false;
    for (size_t i = 0; i < password.length(); ++i) {
        char ch = password[i];
        if (isalpha(ch)) hasLetter = true;
        else if (isdigit(ch)) hasDigit = true;
        else hasSpecial = true;
    }
    return hasLetter && hasDigit && hasSpecial;
}

void ensureFileExists() {
    ifstream infile(USER_FILE);
    if (!infile.good()) {
        ofstream outfile(USER_FILE);
        outfile << left << setw(8) << "Sr.No." << "|"
                << setw(20) << "Username" << "|"
                << setw(20) << "Password" << "\n";
    }
}

pair<unordered_map<string, string>, int> loadUsers() {
    unordered_map<string, string> users;
    ifstream file(USER_FILE);
    string line;
    int maxSerial = 0;

    if (!file.is_open()) return make_pair(users, maxSerial);

    getline(file, line); // skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string serialStr, username, password;
        getline(ss, serialStr, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');

        // Trim whitespace
        username = trim(username);
        password = trim(password);

        users[username] = password;

        try {
            int serial = stoi(trim(serialStr));
            if (serial > maxSerial) maxSerial = serial;
        } catch (...) {}
    }

    return make_pair(users, maxSerial);
}

bool saveUser(int serial, const string& username, const string& password) {
    ofstream file(USER_FILE, ios::app);
    if (!file.is_open()) return false;

    file << left << setw(8) << serial << "|"
         << setw(20) << username << "|"
         << setw(20) << password << "\n";
    return true;
}

bool usernameAvailable(const unordered_map<string, string>& users, const string& username) {
    return users.find(username) == users.end();
}

bool usernameExists(const unordered_map<string, string>& users, const string& username) {
    return users.find(username) != users.end();
}

string getValidatedUsername(const unordered_map<string, string>& users) {
    string username;
    int attempts = 0;
    while (attempts < MAX_ATTEMPTS) {
        cout << "Enter username: ";
        cin >> username;
        if (username == "exit") return "";
        if (!isValidUsername(username)) {
            cout << "Invalid format! Only lowercase letters + optional digits.\n";
        } else if (!usernameAvailable(users, username)) {
            cout << "Username already exists.\n";
        } else {
            return username;
        }
        attempts++;
    }
    return "";
}

string getValidatedPassword() {
    string password;
    int attempts = 0;
    while (attempts < MAX_ATTEMPTS) {
        cout << "Enter password: ";
        cin >> password;
        if (password == "exit") return "";
        if (!isValidPassword(password)) {
            cout << "Invalid password! Must be 6+ chars with letters, digits & symbols.\n";
        } else {
            return password;
        }
        attempts++;
    }
    return "";
}

void registerUser() {
    ensureFileExists();
    pair<unordered_map<string, string>, int> result = loadUsers();
    unordered_map<string, string> users = result.first;
    int maxSerial = result.second;

    cout << "\n*** User Registration ***\n(Type 'exit' to cancel)\n";

    string username = getValidatedUsername(users);
    if (username.empty()) {
        cout << "Registration cancelled.\n";
        return;
    }

    string password = getValidatedPassword();
    if (password.empty()) {
        cout << "Registration cancelled.\n";
        return;
    }

    if (saveUser(maxSerial + 1, username, password))
        cout << "Registration successful!\n";
    else
        cout << "Error saving user.\n";
}

void loginUser() {
    pair<unordered_map<string, string>, int> result = loadUsers();
    unordered_map<string, string> users = result.first;

    cout << "\n*** User Login ***\n(Type 'exit' to cancel)\n";

    string username;
    int attempts = 0;
    while (attempts < MAX_ATTEMPTS) {
        cout << "Enter username: ";
        cin >> username;
        if (username == "exit") {
            cout << "Login cancelled.\n";
            return;
        }
        if (usernameExists(users, username)) break;
        cout << "Username not found.\n";
        attempts++;
    }

    if (attempts == MAX_ATTEMPTS) {
        cout << "Too many failed attempts.\n";
        return;
    }

    string password;
    attempts = 0;
    while (attempts < MAX_ATTEMPTS) {
        cout << "Enter password: ";
        cin >> password;
        if (password == "exit") {
            cout << "Login cancelled.\n";
            return;
        }
        if (users[username] == password) {
            cout << "Login successful. Welcome, " << username << "!\n";
            return;
        } else {
            cout << "Incorrect password.\n";
        }
        attempts++;
    }

    cout << "Too many incorrect password attempts. Login aborted.\n";
}

int main() {
    int choice;
    do {
        cout << "\n=== Login & Registration Menu ===\n"
             << "1. Register\n"
             << "2. Login\n"
             << "3. Exit\n"
             << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid number.\n";
            continue;
        }

        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: cout << "Exiting program. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try 1-3.\n";
        }
    } while (choice != 3);

    return 0;
}

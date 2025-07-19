# User Registration and Login System (C++)

This is a command-line based User Registration and Login System implemented in C++. It stores user credentials (username and password) in a file (`users.txt`) and supports both registration and login functionalities with basic validation.

### Features

* **Register new users**
  * Validates username format (`lowercase letters` + `optional digits`)
  * Validates password strength (minimum 6 characters, includes letters, digits, and special characters)
* **Login for existing users**
  * Verifies credentials against stored data
  * Allows a maximum of 3 attempts
* **Data Persistence**
  * Stores users in a `users.txt` file
  * Auto-generates file with headers if missing
* **Exit anytime**
  * Typing `exit` during prompts cancels the current operation

### Technologies Used

* **C++**
* File I/O using `<fstream>`
* String and regex handling with `<regex>`, `<sstream>`, and `<iomanip>`
* Data storage using `unordered_map`

### Username & Password Rules

#### Username Format:

* Only lowercase letters, optionally followed by digits
* Example: `john`, `alice123`, `user99`

#### Password Format:

* At least 6 characters
* Must include:

  * One letter
  * One digit
  * One special character (e.g., `!`, `@`, `#`, etc.)

#### === Login & Registration Menu ===

1. Register
2. Login
3. Exit
   Enter your choice: 1

*** User Registration ***
(Type 'exit' to cancel)
Enter username: john123
Enter password: pass@123
Registration successful!

### How to Compile and Run

g++ -o user_system main.cpp
./user_system

## Screenshot
### Code:
![image](https://github.com/ashishyadav-1510/CodeAlpha_Login_and_Registration_System/blob/main/Screenshot/Screenshot%202025-07-19%20111340.png?raw=true)
![image](https://github.com/ashishyadav-1510/CodeAlpha_Login_and_Registration_System/blob/main/Screenshot/Screenshot%202025-07-19%20111359.png?raw=true)
![image](https://github.com/ashishyadav-1510/CodeAlpha_Login_and_Registration_System/blob/main/Screenshot/Screenshot%202025-07-19%20111453.png?raw=true)
![image](https://github.com/ashishyadav-1510/CodeAlpha_Login_and_Registration_System/blob/main/Screenshot/Screenshot%202025-07-19%20111531.png?raw=true)
![image](https://github.com/ashishyadav-1510/CodeAlpha_Login_and_Registration_System/blob/main/Screenshot/Screenshot%202025-07-19%20111557.png?raw=true)

### Output:
![image](https://github.com/ashishyadav-1510/CodeAlpha_Login_and_Registration_System/blob/main/Screenshot/Screenshot%202025-07-19%20111637.png?raw=true)

## Video

[Video on YouTube](https://youtu.be/jQrXqpOFKA0)

## Explaination:

🔹 Header Files
#include <iostream>
For input/output operations (cin, cout).

#include <fstream>
For file reading/writing operations (ifstream, ofstream).

#include <unordered_map>
Provides a hash table-based key-value store (unordered_map), used to store usernames and passwords.

#include <sstream>
For working with string streams (stringstream) used to parse lines from the file.

#include <regex>
For regular expressions to validate usernames.

#include <iomanip>
For formatted output (setw, left for table formatting).

#include <limits>
For handling numeric limits (used to clean cin input buffer).

using namespace std;
To avoid writing std:: before standard functions and types.

🔹 Constants

const string USER_FILE = "users.txt";
File where user data is stored.

const int MAX_ATTEMPTS = 3;
Maximum retries for entering valid credentials.

🔹 Helper Functions
trim()

string trim(const string& str) { ... }
Removes leading and trailing whitespaces from a string.

isValidUsername()

bool isValidUsername(const string& username) {
    return regex_match(username, regex("^[a-z]+[0-9]*$"));
}
Returns true if the username has only lowercase letters followed by optional digits (e.g., john123).

isValidPassword()

bool isValidPassword(const string& password) { ... }
Checks if the password has:
At least 6 characters
At least one letter, one digit, and one special character

🔹 File Setup
ensureFileExists()

void ensureFileExists() {
    ifstream infile(USER_FILE);
    if (!infile.good()) {
        ofstream outfile(USER_FILE);
        outfile << left << setw(8) << "Sr.No." << "|"
                << setw(20) << "Username" << "|"
                << setw(20) << "Password" << "\n";
    }
}
Checks if users.txt exists; if not, creates it with column headers.

🔹 User File Loading
loadUsers()

pair<unordered_map<string, string>, int> loadUsers() { ... }
Reads each line (excluding the header) from users.txt.
Parses username and password and stores them in an unordered_map.
Also keeps track of the highest serial number (for new user registration).

🔹 Saving New Users
saveUser()

bool saveUser(int serial, const string& username, const string& password) { ... }
Appends a new user (with serial number, username, password) to the file.

🔹 Username Existence Checks

bool usernameAvailable(...) { return users.find(...) == users.end(); }
Returns true if username is not yet taken.

bool usernameExists(...) { return users.find(...) != users.end(); }
Returns true if username already exists.

🔹 Username & Password Input (with Validation)
getValidatedUsername()

string getValidatedUsername(const unordered_map<string, string>& users) { ... }
Prompts for a username.
Ensures it's in correct format and not already taken.
Allows up to MAX_ATTEMPTS, or returns empty if canceled.
getValidatedPassword()

string getValidatedPassword() { ... }
Prompts for a password.
Checks length and complexity.
Allows up to MAX_ATTEMPTS, or returns empty if canceled.

🔹 User Registration

void registerUser() { ... }
Loads users.
Prompts user for valid username and password.
If valid, adds new user to users.txt.

🔹 User Login

void loginUser() { ... }
Loads user data.
Prompts for username; validates existence.
Prompts for password; checks match.
Allows up to 3 tries for both username and password.

🔹 Main Menu

int main() {
    int choice;
    do {
        ...
        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: cout << "Exiting program. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try 1-3.\n";
        }
    } while (choice != 3);

    return 0;
}
Displays menu repeatedly until user chooses "3. Exit".
Uses a switch to handle choices:
1: Call registerUser()
2: Call loginUser()
3: Exit
Input validation ensures non-integer entries don't break the loop.


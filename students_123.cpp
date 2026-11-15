#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// Constants for score validation
const int PASS_MARK = 60;
const int MIN_SCORE = 0;
const int MAX_SCORE = 100;

// Clears failed input so the program can continue
void clearBadInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Score Checking function
bool isValidScore(int score) {
    return score >= MIN_SCORE && score <= MAX_SCORE;
}

// Returns the index of a student, or -1 if not found
int findByName(const vector<string>& names, const string& target) {

    for (size_t i = 0; i < names.size(); i++) {
        if (names[i] == target) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// ADD STUDENT FUNCTION
void addStudent(vector<string>& names, vector<int>& scores) {
    string name;
    int score;

    cout << "Name: ";
    cin >> name;

    cout << "Score (" << MIN_SCORE << "-"
         << MAX_SCORE << "): ";

    if (!(cin >> score)) {
        clearBadInput();
        cout << "Invalid score. Student not added.\n";
        return;
    }

    if (!isValidScore(score)) {
        cout << "Invalid score. Student not added.\n";
        return;
    }
    // Prevent duplicate student names.
    if (findByName(names, name) != -1) {
        cout << "A student named " << name
             << " already exists. Not added.\n";
        return;
    }

    // .
    names.push_back(name);
    scores.push_back(score);

    cout << "Added " << name << ".\n";
}

// FEATURE 2: View All Students
void viewAll(const vector<string>& names,
             const vector<int>& scores) {

    if (names.empty()) {
        cout << "No records yet.\n";
        return;
    }

    cout << "\n=== Student Records ===\n";

    for (size_t i = 0; i < names.size(); i++) {
        cout << setw(2) << i + 1 << ". "
             << left << setw(15) << names[i]
             << right << setw(4) << scores[i]
             << "\n";
    }
}

//FEATURE 3: SEARCH STUDENT
void searchStudent(const vector<string>& names,
                   const vector<int>& scores) {

    string target;

    cout << "Name to search: ";
    cin >> target;

    int idx = findByName(names, target);

    if (idx == -1) {
        cout << target << " not found.\n";
        return;
    }

    cout << target << " has score "
         << scores[idx] << ".\n";
}


int main() {

    vector<string> names;
    vector<int> scores;

    int choice;

    do {
        cout << "\n=== Student Records Manager ===\n";
        cout << "1. Add student\n";
        cout << "2. View all\n";
        cout << "3. Search by name\n";
        cout << "0. Exit\n";
        cout << "Choice: ";

        if (!(cin >> choice)) {
            clearBadInput();
            cout << "Invalid choice.\n";
            continue;
        }

        switch (choice) {

            case 1:
                addStudent(names, scores);
                break;

            case 2:
                viewAll(names, scores);
                break;

            case 3:
                searchStudent(names, scores);
                break;

            case 0:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}

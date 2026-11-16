// Nathanael and Handy Integrated Program
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

// FEATURE 4: SORT BY SCORE (High to Low)
// Bubble sort. Names and scores are swapped together so they stay paired.
void sortByScoreDescending(vector<string>& names,
                           vector<int>& scores) {

    if (names.empty()) {
        cout << "No records yet.\n";
        return;
    }

    for (size_t pass = 0; pass + 1 < scores.size(); pass++) {
        for (size_t i = 0; i + 1 < scores.size() - pass; i++) {

            if (scores[i] < scores[i + 1]) {
                swap(scores[i], scores[i + 1]);
                swap(names[i], names[i + 1]);
            }
        }
    }

    cout << "Sorted.\n";
}

// FEATURE 5: STATISTICS
// Helper functions (only called when the list is not empty)

// Average of all scores
double computeAverage(const vector<int>& scores) {
    int total = 0;

    for (size_t i = 0; i < scores.size(); i++) {
        total += scores[i];
    }
    return static_cast<double>(total) / scores.size();
}

// Highest score
int findHighest(const vector<int>& scores) {
    int highest = scores[0];

    for (size_t i = 1; i < scores.size(); i++) {
        if (scores[i] > highest) {
            highest = scores[i];
        }
    }
    return highest;
}

// Lowest score
int findLowest(const vector<int>& scores) {
    int lowest = scores[0];

    for (size_t i = 1; i < scores.size(); i++) {
        if (scores[i] < lowest) {
            lowest = scores[i];
        }
    }
    return lowest;
}

// Number of students who reached the pass mark
int countPassing(const vector<int>& scores) {
    int passing = 0;

    for (size_t i = 0; i < scores.size(); i++) {
        if (scores[i] >= PASS_MARK) {
            passing++;
        }
    }
    return passing;
}

// Shows all the statistics
void showStatistics(const vector<int>& scores) {

    if (scores.empty()) {
        cout << "No records yet.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "Average: " << computeAverage(scores) << "\n";
    cout << "Highest: " << findHighest(scores) << "\n";
    cout << "Lowest : " << findLowest(scores) << "\n";
    cout << "Passing: " << countPassing(scores)
         << " of " << scores.size() << "\n";
}

// FEATURE 6: REMOVE STUDENT
void removeStudent(vector<string>& names,
                   vector<int>& scores) {

    string target;

    cout << "Name to remove: ";
    cin >> target;

    int idx = findByName(names, target);

    if (idx == -1) {
        cout << target << " not found.\n";
        return;
    }

    // Erase from both vectors so they stay the same size
    names.erase(names.begin() + idx);
    scores.erase(scores.begin() + idx);

    cout << "Removed " << target << ".\n";
}


int main() {

    vector<string> names;
    vector<int> scores;

    int choice = -1;

    do {
        cout << "\n=== Student Records Manager ===\n";
        cout << "1. Add student\n";
        cout << "2. View all\n";
        cout << "3. Search by name\n";
        cout << "4. Sort by score\n";
        cout << "5. Statistics\n";
        cout << "6. Remove student\n";
        cout << "0. Exit\n";
        cout << "Choice: ";

        if (!(cin >> choice)) {
            clearBadInput();
            cout << "Invalid choice.\n";
            choice = -1;
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
            case 4:
                sortByScoreDescending(names, scores);
                break;
            case 5:
                showStatistics(scores);
                break;
            case 6:
                removeStudent(names, scores);
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

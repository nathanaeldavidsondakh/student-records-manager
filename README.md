Student Records Manager

A console program in C++ that keeps student names and scores for one class in memory. Made for Week 9 (Programming Fundamentals Integration) of Algorithms and Object-Oriented Programming & Lab at Swiss German University.

Features
Add student (score must be 0-100)
View all students
Search by name
Sort by score, high to low (bubble sort)
Statistics: average, highest, lowest, number passing (pass mark 60)
Remove student by name
Exit

The menu keeps running until you choose 0. Invalid input is rejected and does not crash the program.

Build and run
g++ -std=c++17 -Wall -Wextra student_manager.cpp -o student_manager
./student_manager

On Windows, run student_manager.exe instead.

How it works
Two vectors, names and scores, share the same index. Adding, removing and sorting always change both so they stay matched.
main() only shows the menu and calls one function for each choice.
findByName returns the index of a student or -1. Search, remove and the duplicate check all use it.
The pass mark is a constant (PASS_MARK) at the top of the file.
Limits
Names are one word (no spaces), case-sensitive, and must be unique.
Data is only kept while the program runs.
Testing

The test cases and the bug note are in TEST_PLAN_AND_BUG_NOTE.md.

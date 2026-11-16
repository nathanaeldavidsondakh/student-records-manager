# Student Records Manager - Test Plan and Bug Note

Nathanael David Sondakh, IT Business Innovation, Swiss German University

Program file: student_manager.cpp

Compiled with: `g++ -std=c++17 -Wall -Wextra student_manager.cpp -o student_manager` (no warnings)

## Test Plan

I wrote the tests before running the program. In the Input column, the menu number comes first (1 = add, 2 = view, 3 = search, 4 = sort, 5 = statistics, 6 = remove, 0 = exit).

| No. | Type | What I tested | Input | Expected | Actual | Pass/Fail |
|---|---|---|---|---|---|---|
| 1 | Normal | Add one student | 1, Ani, 78 | Added Ani. | Added Ani. | Pass |
| 2 | Invalid | Score too high | 1, Dewi, 150, then 2 | Invalid score, nothing stored | Invalid score. Student not added. View shows No records yet. | Pass |
| 3 | Empty | Statistics with no records | 5 | No records yet. | No records yet. | Pass |
| 4 | Normal | Search for a name that is not there | 3, Zed | Zed not found. | Zed not found. | Pass |
| 5 | Normal | Statistics with 3 records | Ani 78, Bima 92, Citra 55, then 5 | Average 75.00, highest 92, lowest 55, passing 2 of 3 | Average 75.00, Highest 92, Lowest 55, Passing 2 of 3 | Pass |
| 6 | Normal | Sort, then view | same 3 records, then 4, 2 | Bima 92, Ani 78, Citra 55 | 1. Bima 92, 2. Ani 78, 3. Citra 55 | Pass |
| 7 | Normal | Remove a student, then view | 6, Citra, then 2 | Removed Citra. Two records left | Removed Citra. List shows Ani 78 and Bima 92 | Pass |
| 8 | Boundary | Scores 0 and 100 | A 0, B 100, then 2 | Both accepted | Both added, list shows 0 and 100 | Pass |
| 9 | Boundary | Scores 59 and 60 around the pass mark | A 59, B 60, then 5 | Average 59.50, passing 1 of 2 | Average 59.50, Highest 60, Lowest 59, Passing 1 of 2 | Pass |
| 10 | Invalid | Negative score | 1, A, -5, then 2 | Rejected, nothing stored | Invalid score. Student not added. List empty | Pass |
| 11 | Invalid | Menu number that does not exist | 9 | Invalid choice. Menu comes back | Invalid choice. Menu came back | Pass |
| 12 | Invalid | Letter at the menu | abc | Invalid choice. Menu comes back | Invalid choice. Menu came back (this failed before the fix, see Bug Note) | Pass |
| 13 | Invalid | Remove a name that is not there | 6, Zed | Zed not found. | Zed not found. | Pass |
| 14 | Boundary | Only one record | Solo 70, then 5, 3 (Solo) | Average, highest and lowest all 70, passing 1 of 1, search shows 70 | Average 70.00, Highest 70, Lowest 70, Passing 1 of 1. Solo has score 70. | Pass |
| 15 | Invalid | Score typed as letters | 1, Ani, xyz, then 2 | Rejected, no crash | Invalid score. Student not added. List empty | Pass |
| 16 | Invalid | Same name added twice | Ani 70, then Ani 80, then 2 | Second one rejected, one record | A student named Ani already exists. Not added. List has 1 record | Pass |
| 17 | Normal | Sort with equal scores, then remove | A 50, B 80, C 80, D 90, sort, remove B | D 90, B 80, C 80, A 50, then D 90, C 80, A 50 | Same as expected, every name kept its own score | Pass |

## Bug Note

**The bug.** When I typed a letter at the main menu (test 12), the program printed "Invalid choice." and then closed by itself, even though I never chose 0.

**How I found it.** Test 12 was in my plan because the slides list a letter at the menu as an invalid case. I ran it with the input `abc`, then tried to add a student afterwards. The program printed "Invalid choice." and ended, without showing the menu again or saying "Goodbye!".

**Why it happened.** When `cin` fails to read a number, it sets the variable to 0. The loop condition is `while (choice != 0)`, so a bad input looked exactly like choosing Exit. My code cleared the input and printed the message, but it never reset `choice`.

**The fix.** I set `choice = -1` before the `continue` in `main()`, and gave `choice` a starting value of -1. Now the program prints "Invalid choice." and shows the menu again. I ran test 12 again and it passes.

/***************************************************************
 * EECS 348 — Lab 13: Debugging and Testing
 * Name: Elliott Erhard
 *
 * ---------------------- Written Answers ----------------------
 *
 * 1. Is there a fault in the program? If so, locate it and explain.
 *    Yes. The for-loop in the original function starts at index 1
 *    instead of index 0, meaning the first attendance entry is
 *    never checked. This is a fault because it causes the program
 *    to ignore the first lecture completely.
 *
 * 2. Define a test case that does NOT execute the fault.
 *    This is impossible. The loop always iterates from i = 1 to 9
 *    for all valid inputs (size 10). Because of this, the fault
 *    (starting at index 1) is always executed no matter what the
 *    attendance record is. There is no input that avoids the loop.
 *
 * 3. Define a test case that executes the fault but does NOT result
 *    in an error state.
 *    Test Case: {1,1,1,1,1,1,1,1,1,1}
 *    Expected Output (correct function): false
 *    Actual Output   (buggy function)  : false
 *    Explanation: The fault executes (index 0 is skipped), but
 *    since index 0 is a '1' (present), skipping it does not change
 *    the result. The internal absent count matches the correct one.
 *
 * 4. Define a test case that results in an error state but NOT a failure.
 *    Test Case: {0,1,1,1,1,1,1,1,1,1}
 *    Expected Output (correct): false
 *    Actual Output   (buggy): false
 *    Explanation: Skipping index 0 causes the buggy version to count
 *    0 absences instead of 1. This is an incorrect internal state
 *    (error state), but the final returned value is still the same
 *    (false), so there is no external failure.
 *
 * 5. Define a test case that results in failure.
 *    Test Case: {0,0,0,1,1,1,1,1,1,1}
 *    Expected Output (correct): true  (3 absences → fail)
 *    Actual Output   (buggy):  false (only counts 2 absences)
 *    Explanation: The incorrect state (absent_count = 2 instead of 3)
 *    changes the final returned value. This produces a failure because
 *    the output visible to the user is wrong.
 *
 ***************************************************************/

#include <iostream>
#include <vector>
using namespace std;

//Original Function
bool failecture(const vector<int>& attendance_records) {
    int absent_count = 0;
    for (int i = 1; i < attendance_records.size(); ++i) {
        absent_count += (attendance_records[i] == 0);
    }
    return absent_count >= 3;
}

//Corrected Function
bool failecture_correct(const vector<int>& attendance_records) {
    int absent_count = 0;
    for (int i = 0; i < attendance_records.size(); ++i) {
        absent_count += (attendance_records[i] == 0);
    }
    return absent_count >= 3;
}

int main() {
    vector<vector<int>> tests = {
        //Executes fault but no error state
        {1,1,1,1,1,1,1,1,1,1},

        //Error state but no failure
        {0,1,1,1,1,1,1,1,1,1},

        //Failure
        {0,0,0,1,1,1,1,1,1,1}
    };

    for (auto& t : tests) {
        cout << "Test: ";
        for (int x : t) cout << x << " ";
        cout << "\nActual Output (buggy)   : " << failecture(t);
        cout << "\nExpected Output (correct): " << failecture_correct(t);
        cout << "\n-----------------------------\n";
    }
}

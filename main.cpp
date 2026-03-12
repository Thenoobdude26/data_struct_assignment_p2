// ============================================================
//  ASIA PACIFIC UNIVERSITY
//  Data Structures
// ============================================================
//  Team Members:
//    Task 1 - Learner Registration & Session Management : [Name / ID]
//    Task 2 - Activity Navigation & Session Flow        : [Name / ID]
//    Task 3 - Recent Activity Logging & Perf. History   : [Name / ID]
//    Task 4 - At-Risk Learner Priority & Recommendation : [Name / ID]
// ============================================================

#include <iostream>
#include <string>
using namespace std;
// Example shared learner record – adjust fields as needed
struct Learner {
    int    id;
    string name;
    float  score;
};

// Example shared activity record – adjust fields as needed
struct Activity {
    int    activityId;
    string topic;
    string difficulty;   // e.g. "Easy", "Medium", "Hard"
    float  score;
    int    learnerId;
};

// ============================================================
//  TASK 1: LEARNER REGISTRATION & SESSION MANAGEMENT
//  Author : [Name / Student ID]
//  Data Structure : Queue (for session flow) + Array/Linked-List
// ============================================================

// TODO: Implement your data structure(s) here
//   e.g. a Queue class, a registration list, etc.

class Task1 {
public:

    // ----------------------------------------------------------
    // Register a new learner into the system
    // ----------------------------------------------------------
    void registerLearner() {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Move a registered learner into an active learning session
    // ----------------------------------------------------------
    void joinSession() {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Handle the case where session capacity is full
    // ----------------------------------------------------------
    void handleFullSession() {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Allow a learner to exit a session and free up a slot
    // ----------------------------------------------------------
    void exitSession() {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Display current registration list and active session list
    // ----------------------------------------------------------
    void displayLists() {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Entry point for Task 1 menu / demo
    // ----------------------------------------------------------
    void run() {
        cout << "\n===== TASK 1: LEARNER REGISTRATION & SESSION MANAGEMENT =====\n";

    }
};

// ============================================================
//  TASK 2: ACTIVITY NAVIGATION & SESSION FLOW
//  Author : [Name / Student ID]
//  Data Structure : Stack (for backtracking) + Queue (for upcoming)
// ============================================================

// TODO: Implement your data structure(s) here
//   e.g. a Stack class, an activity queue, etc.

class Task2 {
public:

    // ----------------------------------------------------------
    // Load / initialise the sequence of activities for a session
    // ----------------------------------------------------------
    void loadActivities() {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Move forward to the next activity
    // ----------------------------------------------------------
    void nextActivity() {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Go back / undo to revisit the previous activity
    // ----------------------------------------------------------
    void previousActivity() {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Record the outcome of a completed activity
    // (score, topic, difficulty) and forward to Task 3 logger
    // ----------------------------------------------------------
    void recordOutcome() {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Entry point for Task 2 menu / demo
    // ----------------------------------------------------------
    void run() {
        cout << "\n===== TASK 2: ACTIVITY NAVIGATION & SESSION FLOW =====\n";
        // TODO: implement menu loop
    }
};

// ============================================================
//  TASK 3: RECENT ACTIVITY LOGGING & PERFORMANCE HISTORY
//  Author : [Name / Student ID]
//  Data Structure : Circular Queue (fixed-size activity log)
// ============================================================

// TODO: Implement your data structure(s) here
//   e.g. a CircularQueue class with fixed capacity

class Task3 {
public:

    // ----------------------------------------------------------
    // Add a new activity attempt to the circular log
    // (oldest entry is overwritten when the log is full)
    // ----------------------------------------------------------
    void logActivity(/* Activity a */) {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // View all current entries in the activity log
    // ----------------------------------------------------------
    void viewAllLogs() {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Filter and display log entries for a specific learner
    // ----------------------------------------------------------
    void filterByLearner(int learnerId) {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Export all log entries to a CSV / text file
    // ----------------------------------------------------------
    void exportLogs() {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Entry point for Task 3 menu / demo
    // ----------------------------------------------------------
    void run() {
        cout << "\n===== TASK 3: RECENT ACTIVITY LOGGING & PERFORMANCE HISTORY =====\n";
        // TODO: implement menu loop
    }
};

// ============================================================
//  TASK 4: AT-RISK LEARNER PRIORITY & RECOMMENDATION ENGINE
//  Author : [Name / Student ID]
//  Data Structure : Priority Queue (max-heap by risk score)
// ============================================================

// TODO: Implement your data structure(s) here
//   e.g. a PriorityQueue class, a risk-score calculator, etc.

class Task4 {
public:

    // ----------------------------------------------------------
    // Calculate a risk score for a learner based on performance
    // indicators (recent scores, failed attempts, consistency,
    // time vs progress)
    // ----------------------------------------------------------
    float calculateRiskScore(int learnerId) {
        // TODO: implement
        return 0.0f;
    }

    // ----------------------------------------------------------
    // Enqueue all learners into the priority queue by risk score
    // ----------------------------------------------------------
    void buildPriorityQueue() {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Display the highest-priority (most at-risk) learners
    // ----------------------------------------------------------
    void displayAtRiskLearners() {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Attach and display recommended actions for each at-risk
    // learner (e.g. repeat topic, attempt easier activity)
    // ----------------------------------------------------------
    void showRecommendations() {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Export the at-risk list and recommendations to a file
    // ----------------------------------------------------------
    void exportAtRiskList() {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Entry point for Task 4 menu / demo
    // ----------------------------------------------------------
    void run() {
        cout << "\n===== TASK 4: AT-RISK LEARNER PRIORITY & RECOMMENDATION ENGINE =====\n";
        // TODO: implement menu loop
    }
};

// ============================================================
//  MAIN MENU
// ============================================================

int main() {
    Task1 task1;
    Task2 task2;
    Task3 task3;
    Task4 task4;

    int choice = 0;

    do {
        cout << "\n========================================\n";
        cout << "  PLAPS – Main Menu\n";
        cout << "========================================\n";
        cout << "  1. Learner Registration & Session Mgmt\n";
        cout << "  2. Activity Navigation & Session Flow\n";
        cout << "  3. Recent Activity Logging & History\n";
        cout << "  4. At-Risk Learner Priority & Recs\n";
        cout << "  0. Exit\n";
        cout << "----------------------------------------\n";
        cout << "  Enter choice: ";
        cin  >> choice;

        switch (choice) {
            case 1: task1.run(); break;
            case 2: task2.run(); break;
            case 3: task3.run(); break;
            case 4: task4.run(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
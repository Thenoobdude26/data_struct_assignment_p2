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
#include <cstring>
using namespace std;

struct Learner
{
    int id;
    string name;
    float score;
};

struct Activity
{
    int activityId;
    string topic;
    string difficulty;
    float score;
    int learnerId;
};

// ============================================================
//  TASK 1: LEARNER REGISTRATION & SESSION MANAGEMENT
//  Author : [Name / Student ID]
//  Data Structure : Queue (for session flow) + Array/Linked-List
// ============================================================

// Node for linked-list registration queue
struct Node
{
    Learner data;
    Node *next;
};

// FIFO queue for learner registration
class RegistrationQueue
{
private:
    Node *front;
    Node *rear;
    int count;

public:
    RegistrationQueue() : front(NULL), rear(NULL), count(0) {}

    ~RegistrationQueue()
    {
        while (!isEmpty())
            dequeue();
    }

    bool isEmpty() { return front == NULL; }
    int getCount() { return count; }

    bool containsId(int id)
    {
        Node *cur = front;
        while (cur)
        {
            if (cur->data.id == id)
                return true;
            cur = cur->next;
        }
        return false;
    }

    void enqueue(Learner learner)
    {
        Node *n = new Node;
        n->data = learner;
        n->next = NULL;
        if (!rear)
        {
            front = rear = n;
        }
        else
        {
            rear->next = n;
            rear = n;
        }
        count++;
    }

    Learner dequeue()
    {
        Learner tmp;
        tmp.id = -1;
        tmp.name, "";
        if (isEmpty())
            return tmp;
        Node *del = front;
        tmp = front->data;
        front = front->next;
        if (!front)
            rear = NULL;
        delete del;
        count--;
        return tmp;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Waiting queue is empty.\n";
            return;
        }
        Node *cur = front;
        cout << "\n--- Waiting Queue ---\n";
        while (cur)
        {
            cout << "  ID: " << cur->data.id << " | Name: " << cur->data.name << "\n";
            cur = cur->next;
        }
        cout << "  Total waiting: " << count << "\n";
    }
};

// Circular queue for active session
class ActiveSessionQueue
{
private:
    Learner *arr;
    int front, rear, count, capacity;

public:
    ActiveSessionQueue(int size) : front(0), rear(-1), count(0), capacity(size)
    {
        arr = new Learner[capacity];
    }
    ~ActiveSessionQueue() { delete[] arr; }

    bool isEmpty() { return count == 0; }
    bool isFull() { return count == capacity; }
    int getCount() { return count; }
    int getCapacity() { return capacity; }

    bool containsId(int id)
    {
        int idx = front;
        for (int i = 0; i < count; i++)
        {
            if (arr[idx].id == id)
                return true;
            idx = (idx + 1) % capacity;
        }
        return false;
    }

    void enqueue(Learner learner)
    {
        if (isFull())
        {
            cout << "Active session is full.\n";
            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = learner;
        count++;
    }

    Learner dequeue()
    {
        Learner tmp;
        tmp.id = -1;
        tmp.name, "";
        if (isEmpty())
            return tmp;
        tmp = arr[front];
        front = (front + 1) % capacity;
        count--;
        return tmp;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Active session is empty.\n";
            return;
        }
        cout << "\n--- Active Session ---\n";
        int idx = front;
        for (int i = 0; i < count; i++)
        {
            cout << "  ID: " << arr[idx].id << " | Name: " << arr[idx].name << "\n";
            idx = (idx + 1) % capacity;
        }
        cout << "  Active: " << count << "/" << capacity << "\n";
    }
};

// Admit next learner from registration queue into active session
void admitNextLearner(RegistrationQueue &rq, ActiveSessionQueue &sq)
{
    if (rq.isEmpty())
    {
        cout << "No learners waiting.\n";
        return;
    }
    if (sq.isFull())
    {
        cout << "Cannot admit – session is full.\n";
        return;
    }
    Learner l = rq.dequeue();
    sq.enqueue(l);
    cout << "Learner admitted: " << l.name << "\n";
}

// Remove learner from active session (FIFO) and auto-admit next if waiting
void exitLearner(RegistrationQueue &rq, ActiveSessionQueue &sq)
{
    if (sq.isEmpty())
    {
        cout << "No learners in active session.\n";
        return;
    }
    Learner exited = sq.dequeue();
    cout << "Learner exited: " << exited.name << "\n";
    if (!rq.isEmpty() && !sq.isFull())
    {
        Learner next = rq.dequeue();
        sq.enqueue(next);
        cout << "Next learner auto-admitted: " << next.name << "\n";
    }
}

class Task1
{
private:
    RegistrationQueue regQueue;
    ActiveSessionQueue sessionQueue;

public:
    Task1(int sessionSize) : sessionQueue(sessionSize) {}

    void run()
    {
        int choice;
        do
        {
            cout << "\n===== TASK 1: LEARNER REGISTRATION & SESSION MANAGEMENT =====\n";
            cout << "  [1] Register learner\n";
            cout << "  [2] Admit next learner to session\n";
            cout << "  [3] Exit learner from session\n";
            cout << "  [4] Display waiting queue\n";
            cout << "  [5] Display active session\n";
            cout << "  [6] System summary\n";
            cout << "  [0] Back to main menu\n";
            cout << "  Enter choice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1)
            {
                Learner l;
                cout << "  Enter learner ID: ";
                cin >> l.id;
                cin.ignore();
                if (regQueue.containsId(l.id) || sessionQueue.containsId(l.id))
                {
                    cout << "  Error: ID already exists.\n";
                    continue;
                }
                cout << "  Enter learner name: ";
                getline(cin, l.name);
                l.score = 0.0f;
                regQueue.enqueue(l);
                cout << "  Learner registered successfully.\n";
            }
            else if (choice == 2)
            {
                admitNextLearner(regQueue, sessionQueue);
            }
            else if (choice == 3)
            {
                exitLearner(regQueue, sessionQueue);
            }
            else if (choice == 4)
            {
                regQueue.display();
            }
            else if (choice == 5)
            {
                sessionQueue.display();
            }
            else if (choice == 6)
            {
                cout << "\n  --- System Summary ---\n";
                cout << "  Waiting : " << regQueue.getCount() << "\n";
                cout << "  Active  : " << sessionQueue.getCount()
                     << "/" << sessionQueue.getCapacity() << "\n";
            }
            else if (choice != 0)
            {
                cout << "  Invalid choice.\n";
            }

        } while (choice != 0);
    }
};
// ============================================================
//  TASK 2: ACTIVITY NAVIGATION & SESSION FLOW
//  Author : [Name / Student ID]
//  Data Structure : Stack (for backtracking) + Queue (for upcoming)
// ============================================================

// TODO: Implement your data structure(s) here
//   e.g. a Stack class, an activity queue, etc.

class Task2
{
public:
    // ----------------------------------------------------------
    // Load / initialise the sequence of activities for a session
    // ----------------------------------------------------------
    void loadActivities()
    {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Move forward to the next activity
    // ----------------------------------------------------------
    void nextActivity()
    {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Go back / undo to revisit the previous activity
    // ----------------------------------------------------------
    void previousActivity()
    {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Record the outcome of a completed activity
    // (score, topic, difficulty) and forward to Task 3 logger
    // ----------------------------------------------------------
    void recordOutcome()
    {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Entry point for Task 2 menu / demo
    // ----------------------------------------------------------
    void run()
    {
        cout << "\n===== ACTIVITY NAVIGATION & SESSION FLOW =====\n";
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

class Task3
{
public:
    // ----------------------------------------------------------
    // Add a new activity attempt to the circular log
    // (oldest entry is overwritten when the log is full)
    // ----------------------------------------------------------
    void logActivity(/* Activity a */)
    {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // View all current entries in the activity log
    // ----------------------------------------------------------
    void viewAllLogs()
    {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Filter and display log entries for a specific learner
    // ----------------------------------------------------------
    void filterByLearner(int learnerId)
    {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Export all log entries to a CSV / text file
    // ----------------------------------------------------------
    void exportLogs()
    {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Entry point for Task 3 menu / demo
    // ----------------------------------------------------------
    void run()
    {
        cout << "\n===== RECENT ACTIVITY LOGGING & PERFORMANCE HISTORY =====\n";
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

class Task4
{
public:
    // ----------------------------------------------------------
    // Calculate a risk score for a learner based on performance
    // indicators (recent scores, failed attempts, consistency,
    // time vs progress)
    // ----------------------------------------------------------
    float calculateRiskScore(int learnerId)
    {
        // TODO: implement
        return 0.0f;
    }

    // ----------------------------------------------------------
    // Enqueue all learners into the priority queue by risk score
    // ----------------------------------------------------------
    void buildPriorityQueue()
    {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Display the highest-priority (most at-risk) learners
    // ----------------------------------------------------------
    void displayAtRiskLearners()
    {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Attach and display recommended actions for each at-risk
    // learner (e.g. repeat topic, attempt easier activity)
    // ----------------------------------------------------------
    void showRecommendations()
    {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Export the at-risk list and recommendations to a file
    // ----------------------------------------------------------
    void exportAtRiskList()
    {
        // TODO: implement
    }

    // ----------------------------------------------------------
    // Entry point for Task 4 menu / demo
    // ----------------------------------------------------------
    void run()
    {
        cout << "\n===== AT-RISK LEARNER PRIORITY & RECOMMENDATION ENGINE =====\n";
        // TODO: implement menu loop
    }
};

// ============================================================
//  MAIN MENU
// ============================================================

int main()
{

    int sessionSize;
    cout << "Enter Active Session Capacity: ";
    cin >> sessionSize;
    cin.ignore();

    Task1 task1(sessionSize);
    Task2 task2;
    Task3 task3;
    Task4 task4;

    int choice = 0;

    do
    {
        cout << "=============================================\n";
        cout << "                   Main Menu                 \n";
        cout << "=============================================\n";
        cout << "  [1] Learner Registration & Session Mgmt\n";
        cout << "  [2] Activity Navigation & Session Flow\n";
        cout << "  [3] Recent Activity Logging & History\n";
        cout << "  [4] At-Risk Learner Priority & Recs\n";
        cout << "  [0] Exit\n";
        cout << "=============================================\n";
        cout << "  Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            task1.run();
            break;
        case 2:
            task2.run();
            break;
        case 3:
            task3.run();
            break;
        case 4:
            task4.run();
            break;
        case 0:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
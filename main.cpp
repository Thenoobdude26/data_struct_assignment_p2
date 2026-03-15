// ============================================================
//  ASIA PACIFIC UNIVERSITY
//  Programming Learning Analytics & Personalisation System
// ============================================================
//  Team Members:
//    Task 1 - Learner Registration & Session Management : [Name / ID]
//    Task 2 - Activity Navigation & Session Flow        : [Name / ID]
//    Task 3 - Recent Activity Logging & Perf. History   : [Name / ID]
//    Task 4 - At-Risk Learner Priority & Recommendation : [Name / ID]
// ============================================================

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <fstream>
using namespace std;

// ============================================================
//  SHARED STRUCTS
// ============================================================

struct Learner {
    int    id;
    string name;
    float  score;
};

struct Activity {
    int    id;
    string title;
    string question;
    string answer;
    int    pointsValue;

    Activity() : id(0), pointsValue(0) {}
    Activity(int i, string t, string q, string a, int p)
        : id(i), title(t), question(q), answer(a), pointsValue(p) {}
};

struct LogRecord {
    int    learnerId;
    string learnerName;
    string activityTitle;
    int    score;
    int    maxScore;
    int    attempts;
    bool   completed;
};

struct AtRiskLearner {
    int    learnerId;
    string learnerName;
    float  riskScore;
    string recommendation;
};

// ============================================================
//  TASK 1: LEARNER REGISTRATION & SESSION MANAGEMENT
//  Author : [Name / Student ID]
//  Data Structures : Linked-List Queue (registration)
//                  + Circular Queue (active session)
// ============================================================

struct Node {
    Learner data;
    Node*   next;
};

class RegistrationQueue {
private:
    Node* front;
    Node* rear;
    int   count;

public:
    RegistrationQueue() : front(NULL), rear(NULL), count(0) {}

    ~RegistrationQueue() {
        while (!isEmpty()) dequeue();
    }

    bool isEmpty()  { return front == NULL; }
    int  getCount() { return count; }

    bool containsId(int id) {
        Node* cur = front;
        while (cur) {
            if (cur->data.id == id) return true;
            cur = cur->next;
        }
        return false;
    }

    void enqueue(Learner learner) {
        Node* n = new Node;
        n->data = learner;
        n->next = NULL;
        if (!rear) { front = rear = n; }
        else       { rear->next = n; rear = n; }
        count++;
    }

    Learner dequeue() {
        Learner tmp; tmp.id = -1; tmp.name = "";
        if (isEmpty()) return tmp;
        Node* del = front;
        tmp   = front->data;
        front = front->next;
        if (!front) rear = NULL;
        delete del;
        count--;
        return tmp;
    }

    void display() {
        if (isEmpty()) { cout << "  Waiting queue is empty.\n"; return; }
        Node* cur = front;
        cout << "\n  --- Waiting Queue ---\n";
        while (cur) {
            cout << "  ID: " << cur->data.id << " | Name: " << cur->data.name << "\n";
            cur = cur->next;
        }
        cout << "  Total waiting: " << count << "\n";
    }
};

class ActiveSessionQueue {
private:
    Learner* arr;
    int front, rear, count, capacity;

public:
    ActiveSessionQueue(int size) : front(0), rear(-1), count(0), capacity(size) {
        arr = new Learner[capacity];
    }
    ~ActiveSessionQueue() { delete[] arr; }

    bool isEmpty()     { return count == 0; }
    bool isFull()      { return count == capacity; }
    int  getCount()    { return count; }
    int  getCapacity() { return capacity; }

    bool containsId(int id) {
        int idx = front;
        for (int i = 0; i < count; i++) {
            if (arr[idx].id == id) return true;
            idx = (idx + 1) % capacity;
        }
        return false;
    }

    // Returns a learner by ID — used by Task 2 to identify who is starting
    Learner getLearnerById(int id) {
        int idx = front;
        for (int i = 0; i < count; i++) {
            if (arr[idx].id == id) return arr[idx];
            idx = (idx + 1) % capacity;
        }
        Learner e; e.id = -1; e.name = ""; return e;
    }

    void enqueue(Learner learner) {
        if (isFull()) { cout << "  Active session is full.\n"; return; }
        rear      = (rear + 1) % capacity;
        arr[rear] = learner;
        count++;
    }

    Learner dequeue() {
        Learner tmp; tmp.id = -1; tmp.name = "";
        if (isEmpty()) return tmp;
        tmp   = arr[front];
        front = (front + 1) % capacity;
        count--;
        return tmp;
    }

    bool isSessionEmpty() { return count == 0; }

    void display() {
        if (isEmpty()) { cout << "  Active session is empty.\n"; return; }
        cout << "\n  --- Active Session ---\n";
        int idx = front;
        for (int i = 0; i < count; i++) {
            cout << "  ID: " << arr[idx].id << " | Name: " << arr[idx].name << "\n";
            idx = (idx + 1) % capacity;
        }
        cout << "  Active: " << count << "/" << capacity << "\n";
    }
};

void admitNextLearner(RegistrationQueue& rq, ActiveSessionQueue& sq) {
    if (rq.isEmpty()) { cout << "  No learners waiting.\n"; return; }
    if (sq.isFull())  { cout << "  Cannot admit - session is full.\n"; return; }
    Learner l = rq.dequeue();
    sq.enqueue(l);
    cout << "  Learner admitted: " << l.name << "\n";
}

void exitLearner(RegistrationQueue& rq, ActiveSessionQueue& sq) {
    if (sq.isEmpty()) { cout << "  No learners in active session.\n"; return; }
    Learner exited = sq.dequeue();
    cout << "  Learner exited: " << exited.name << "\n";
    if (!rq.isEmpty() && !sq.isFull()) {
        Learner next = rq.dequeue();
        sq.enqueue(next);
        cout << "  Next learner auto-admitted: " << next.name << "\n";
    }
}

class Task1 {
private:
    RegistrationQueue  regQueue;
    ActiveSessionQueue sessionQueue;

public:
    Task1(int sessionSize) : sessionQueue(sessionSize) {}

    // Returns a specific learner from the active session by ID
    Learner getLearnerById(int id) {
        return sessionQueue.getLearnerById(id);
    }

    bool isSessionEmpty() {
        return sessionQueue.isSessionEmpty();
    }

    void run() {
        int choice;
        do {
            cout << "\n===== TASK 1: LEARNER REGISTRATION & SESSION MANAGEMENT =====\n";
            cout << "  [1] Register learner\n";
            cout << "  [2] Admit next learner to session\n";
            cout << "  [3] Exit learner from session\n";
            cout << "  [4] Display waiting queue\n";
            cout << "  [5] Display active session\n";
            cout << "  [6] System summary\n";
            cout << "  [0] Back to main menu\n";
            cout << "  Enter choice: ";
            cin >> choice; cin.ignore();

            if (choice == 1) {
                Learner l;
                cout << "  Enter learner ID: ";
                cin >> l.id; cin.ignore();
                if (regQueue.containsId(l.id) || sessionQueue.containsId(l.id)) {
                    cout << "  Error: ID already exists.\n"; continue;
                }
                cout << "  Enter learner name: ";
                getline(cin, l.name);
                l.score = 0.0f;
                regQueue.enqueue(l);
                cout << "  Learner registered successfully.\n";
            }
            else if (choice == 2) { admitNextLearner(regQueue, sessionQueue); }
            else if (choice == 3) { exitLearner(regQueue, sessionQueue); }
            else if (choice == 4) { regQueue.display(); }
            else if (choice == 5) { sessionQueue.display(); }
            else if (choice == 6) {
                cout << "\n  --- System Summary ---\n";
                cout << "  Waiting : " << regQueue.getCount() << "\n";
                cout << "  Active  : " << sessionQueue.getCount()
                     << "/" << sessionQueue.getCapacity() << "\n";
            }
            else if (choice != 0) { cout << "  Invalid choice.\n"; }
        } while (choice != 0);
    }
};

// ============================================================
//  TASK 2: ACTIVITY NAVIGATION & SESSION FLOW
//  Author : [Name / Student ID]
//  Data Structures : Custom Stack (backtracking + redo)
// ============================================================

class Task3; // forward declaration

class ActivityStack {
private:
    static const int MAX = 50;
    Activity data[MAX];
    int      top;

public:
    ActivityStack() : top(-1) {}

    bool isEmpty() { return top == -1; }
    bool isFull()  { return top == MAX - 1; }

    void push(Activity a) { if (!isFull()) data[++top] = a; }

    Activity pop() {
        if (!isEmpty()) return data[top--];
        return Activity();
    }

    void clear() { top = -1; }
};

struct ActivityOutcome {
    int    activityId;
    string title;
    int    score;
    int    maxScore;
    int    attempts;
    bool   completed;

    ActivityOutcome() : activityId(0), score(0), maxScore(10), attempts(0), completed(false) {}
};

class ActivityLogger {
private:
    static const int MAX_OUTCOMES = 50;
    ActivityOutcome  outcomes[MAX_OUTCOMES];
    int              count;

public:
    ActivityLogger() : count(0) {}

    ActivityOutcome* findOutcome(int activityId) {
        for (int i = 0; i < count; i++)
            if (outcomes[i].activityId == activityId) return &outcomes[i];
        return NULL;
    }

    void logOutcome(int activityId, const string& title, int scoreEarned, int maxPoints, int attemptCount) {
        ActivityOutcome* o = findOutcome(activityId);
        if (o) {
            o->score     = scoreEarned;
            o->attempts  = attemptCount;
            o->completed = true;
        } else if (count < MAX_OUTCOMES) {
            outcomes[count].activityId = activityId;
            outcomes[count].title      = title;
            outcomes[count].score      = scoreEarned;
            outcomes[count].maxScore   = maxPoints;
            outcomes[count].attempts   = attemptCount;
            outcomes[count].completed  = true;
            count++;
        }
    }

    int getAttempts(int activityId) {
        ActivityOutcome* o = findOutcome(activityId);
        return o ? o->attempts : 0;
    }

    int getCount() { return count; }

    void reset() { count = 0; }

    void displayFinalReport() const {
        int totalScore = 0, totalPossible = 0, completedCount = 0;
        cout << "\n" << string(60, '=') << "\n";
        cout << "=== SESSION COMPLETION REPORT ===\n";
        cout << string(60, '=') << "\n";
        cout << "\n  " << left << setw(5) << "ID" << setw(40) << "Activity"
             << setw(12) << "Score" << setw(10) << "Attempts" << "\n";
        cout << "  " << string(66, '-') << "\n";

        for (int i = 0; i < count; i++) {
            if (outcomes[i].completed) {
                string t = outcomes[i].title.length() > 38
                    ? outcomes[i].title.substr(0, 35) + "..."
                    : outcomes[i].title;
                cout << "  " << left << setw(5) << outcomes[i].activityId
                     << setw(40) << t
                     << setw(12) << (to_string(outcomes[i].score) + "/" + to_string(outcomes[i].maxScore))
                     << setw(10) << outcomes[i].attempts << "\n";
                totalScore    += outcomes[i].score;
                totalPossible += outcomes[i].maxScore;
                completedCount++;
            }
        }
        cout << "  " << string(66, '-') << "\n";
        double pct = totalPossible > 0
            ? (static_cast<double>(totalScore) / totalPossible) * 100.0 : 0.0;
        cout << "\n  Activities Completed : " << completedCount << "\n";
        cout << "  Total Score          : " << totalScore << "/" << totalPossible << "\n";
        cout << "  Overall Percentage   : " << fixed << setprecision(1) << pct << "%\n";
    }
};

class EducationalSession {
private:
    static const int MAX_ACTIVITIES = 50;
    Activity       activities[MAX_ACTIVITIES];
    int            activityCount;
    ActivityStack  progressStack;
    ActivityStack  redoStack;
    ActivityLogger logger;
    int            currentActivityIndex;
    Task3*         task3Ref;
    Task1*         task1Ref;
    Learner        activeLearner; // locked in at session start

public:
    EducationalSession(Task3* t3, Task1* t1)
        : activityCount(0), currentActivityIndex(-1), task3Ref(t3), task1Ref(t1) {
        activeLearner.id = -1;
        activeLearner.name = "";
        initializeActivities();
    }

    void initializeActivities() {
        activities[activityCount++] = Activity(1, "Activity 1", "2B or not 2B?", "2B", 2);
        activities[activityCount++] = Activity(2, "Activity 2", "Does key taste better than bread?", "No", 2);
        activities[activityCount++] = Activity(3, "Activity 3", "What is the airspeed velocity of an unladened swallow?", "Dunno", 2);
        activities[activityCount++] = Activity(4, "Activity 4", "Sorewa TM", "Opera O", 2);
        activities[activityCount++] = Activity(5, "Activity 5", "Bakushin Armpit?", "Lick", 2);
    }

    void checkAnswer(Activity& activity, string answer);

    void showCurrentActivity() {
        if (currentActivityIndex >= 0 && currentActivityIndex < activityCount) {
            Activity& cur = activities[currentActivityIndex];
            cout << "\n" << string(50, '=') << "\n";
            cout << "  Activity " << cur.id << ": " << cur.title << "\n";
            cout << string(50, '=') << "\n";
            cout << "  Question: " << cur.question << "\n";
            cout << "  Your answer (or 'skip'): ";
            string ans;
            getline(cin, ans);
            if (ans != "skip") checkAnswer(cur, ans);
        }
    }

    void nextActivity() {
        if (currentActivityIndex < activityCount - 1) {
            if (currentActivityIndex >= 0) {
                progressStack.push(activities[currentActivityIndex]);
                redoStack.clear();
            }
            currentActivityIndex++;
            cout << "\n  -> Moving to next activity...\n";
            showCurrentActivity();
        } else {
            cout << "\n  Congratulations! You have completed all activities!\n";
        }
    }

    void previousActivity() {
        if (!progressStack.isEmpty()) {
            if (currentActivityIndex >= 0)
                redoStack.push(activities[currentActivityIndex]);
            Activity prev = progressStack.pop();
            for (int i = 0; i < activityCount; i++)
                if (activities[i].id == prev.id) { currentActivityIndex = i; break; }
            cout << "\n  <- Going back...\n";
            showCurrentActivity();
        } else {
            cout << "\n  You are at the beginning.\n";
        }
    }

    void redoActivity() {
        if (!redoStack.isEmpty()) {
            if (currentActivityIndex >= 0)
                progressStack.push(activities[currentActivityIndex]);
            Activity redo = redoStack.pop();
            for (int i = 0; i < activityCount; i++)
                if (activities[i].id == redo.id) { currentActivityIndex = i; break; }
            cout << "\n  Redoing activity...\n";
            showCurrentActivity();
        } else {
            cout << "\n  No activities to redo.\n";
        }
    }

    void run() {
        cout << "\n=== Welcome to the Interactive Learning Session ===\n";
        cout << "  N = Next  |  B = Back  |  R = Redo  |  Q = Quit\n";

        if (task1Ref->isSessionEmpty()) {
            cout << "\n  No learners in active session.\n";
            cout << "  Please admit a learner in Task 1 first.\n";
            return;
        }

        // Ask which learner is starting — they must be in the active session
        int learnerId;
        cout << "\n  Enter your learner ID to start: ";
        cin >> learnerId;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        activeLearner = task1Ref->getLearnerById(learnerId);
        if (activeLearner.id == -1) {
            cout << "\n  Learner ID " << learnerId << " is not in the active session.\n";
            cout << "  Please admit this learner in Task 1 first.\n";
            return;
        }

        // Reset logger for fresh session
        logger.reset();
        progressStack.clear();
        redoStack.clear();
        currentActivityIndex = 0;

        cout << "  Starting session for: " << activeLearner.name << "\n";
        showCurrentActivity();

        char choice;
        do {
            cout << "\n  Navigation: [N]ext  [B]ack  [R]edo  [Q]uit\n";
            cout << "  Enter choice: ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (toupper(choice)) {
                case 'N': nextActivity();     break;
                case 'B': previousActivity(); break;
                case 'R': redoActivity();     break;
                case 'Q':
                    cout << "\n  Thanks for learning!\n";
                    if (logger.getCount() > 0) logger.displayFinalReport();
                    break;
                default:
                    cout << "\n  Invalid choice.\n";
            }
        } while (toupper(choice) != 'Q');
    }
};

class Task2 {
private:
    EducationalSession session;

public:
    Task2(Task3* t3, Task1* t1) : session(t3, t1) {}

    void run() {
        cout << "\n===== TASK 2: ACTIVITY NAVIGATION & SESSION FLOW =====\n";
        session.run();
    }
};

// ============================================================
//  TASK 3: RECENT ACTIVITY LOGGING & PERFORMANCE HISTORY
//  Author : [Name / Student ID]
//  Data Structure : Circular Queue (fixed-size activity log)
// ============================================================

const int MAX_LOG = 20;

class CircularLog {
private:
    LogRecord data[MAX_LOG];
    int front, rear, count;

public:
    CircularLog() : front(0), rear(-1), count(0) {}

    int getCount() { return count; }

    void addRecord(LogRecord record) {
        if (count == MAX_LOG) {
            front = (front + 1) % MAX_LOG;
            count--;
        }
        rear       = (rear + 1) % MAX_LOG;
        data[rear] = record;
        count++;
    }

    void displayAll() {
        if (count == 0) { cout << "  Log is empty.\n"; return; }
        cout << "\n  --- Activity Log ---\n";
        int idx = front;
        for (int i = 0; i < count; i++) {
            cout << "  Learner ID   : " << data[idx].learnerId   << "\n";
            cout << "  Learner Name : " << data[idx].learnerName << "\n";
            cout << "  Activity     : " << data[idx].activityTitle << "\n";
            cout << "  Score        : " << data[idx].score << "/" << data[idx].maxScore << "\n";
            cout << "  Attempts     : " << data[idx].attempts << "\n";
            cout << "  Completed    : " << (data[idx].completed ? "Yes" : "No") << "\n";
            cout << "  ----------\n";
            idx = (idx + 1) % MAX_LOG;
        }
    }

    void filterByLearner(int learnerId) {
        bool found = false;
        int  idx   = front;
        for (int i = 0; i < count; i++) {
            if (data[idx].learnerId == learnerId) {
                if (!found) {
                    cout << "\n  --- Records for Learner " << learnerId << " ---\n";
                    found = true;
                }
                cout << "  Activity  : " << data[idx].activityTitle << "\n";
                cout << "  Score     : " << data[idx].score << "/" << data[idx].maxScore << "\n";
                cout << "  Attempts  : " << data[idx].attempts << "\n";
                cout << "  Completed : " << (data[idx].completed ? "Yes" : "No") << "\n";
                cout << "  ----------\n";
            }
            idx = (idx + 1) % MAX_LOG;
        }
        if (!found) cout << "  No records found for Learner " << learnerId << ".\n";
    }

    void exportCSV() {
        ofstream file("activitylog.csv");
        if (!file.is_open()) { cout << "  Error: Could not create file.\n"; return; }
        file << "learner_id,learner_name,activity_title,score,max_score,attempts,completed\n";
        int idx = front;
        for (int i = 0; i < count; i++) {
            file << data[idx].learnerId     << ","
                 << data[idx].learnerName   << ","
                 << data[idx].activityTitle << ","
                 << data[idx].score         << ","
                 << data[idx].maxScore      << ","
                 << data[idx].attempts      << ","
                 << (data[idx].completed ? "Yes" : "No") << "\n";
            idx = (idx + 1) % MAX_LOG;
        }
        file.close();
        cout << "  Log successfully exported to activity_log.csv\n";
    }

    int getRecordsByLearner(int learnerId, LogRecord* out, int maxOut) {
        int found = 0, idx = front;
        for (int i = 0; i < count && found < maxOut; i++) {
            if (data[idx].learnerId == learnerId)
                out[found++] = data[idx];
            idx = (idx + 1) % MAX_LOG;
        }
        return found;
    }

    int getUniqueLearnerIds(int* out, int maxOut) {
        int found = 0, idx = front;
        for (int i = 0; i < count; i++) {
            int  lid = data[idx].learnerId;
            bool dup = false;
            for (int j = 0; j < found; j++)
                if (out[j] == lid) { dup = true; break; }
            if (!dup && found < maxOut) out[found++] = lid;
            idx = (idx + 1) % MAX_LOG;
        }
        return found;
    }

    string getLearnerName(int learnerId) {
        int idx = front;
        for (int i = 0; i < count; i++) {
            if (data[idx].learnerId == learnerId) return data[idx].learnerName;
            idx = (idx + 1) % MAX_LOG;
        }
        return "Unknown";
    }
};

class Task3 {
private:
    CircularLog log;

public:
    void   logActivity(LogRecord record)                            { log.addRecord(record); }
    int    getRecordsByLearner(int id, LogRecord* out, int maxOut)  { return log.getRecordsByLearner(id, out, maxOut); }
    int    getUniqueLearnerIds(int* out, int maxOut)                { return log.getUniqueLearnerIds(out, maxOut); }
    string getLearnerName(int id)                                   { return log.getLearnerName(id); }
    int    getTotalCount()                                          { return log.getCount(); }

    void run() {
        int choice;
        do {
            cout << "\n===== TASK 3: RECENT ACTIVITY LOGGING & PERFORMANCE HISTORY =====\n";
            cout << "  [1] View all logs\n";
            cout << "  [2] Filter by learner ID\n";
            cout << "  [3] Export to CSV\n";
            cout << "  [0] Back to main menu\n";
            cout << "  Enter choice: ";
            cin >> choice; cin.ignore();

            if (choice == 1)      { log.displayAll(); }
            else if (choice == 2) {
                int id;
                cout << "  Enter learner ID: ";
                cin >> id; cin.ignore();
                log.filterByLearner(id);
            }
            else if (choice == 3) { log.exportCSV(); }
            else if (choice != 0) { cout << "  Invalid choice.\n"; }
        } while (choice != 0);
    }
};

// ============================================================
//  checkAnswer — defined after Task3 so it can call logActivity
// ============================================================

void EducationalSession::checkAnswer(Activity& activity, string answer) {
    string aLow = answer, cLow = activity.answer;
    transform(aLow.begin(), aLow.end(), aLow.begin(), ::tolower);
    transform(cLow.begin(), cLow.end(), cLow.begin(), ::tolower);

    int attempts = logger.getAttempts(activity.id) + 1;

    if (aLow == cLow) {
        int earned = (attempts == 1) ? activity.pointsValue : max(1, activity.pointsValue / 2);
        logger.logOutcome(activity.id, activity.title, earned, activity.pointsValue, attempts);

        // Use activeLearner locked in at session start — correct learner every time
        LogRecord r;
        r.learnerId     = activeLearner.id;
        r.learnerName   = activeLearner.name;
        r.activityTitle = activity.title;
        r.score         = earned;
        r.maxScore      = activity.pointsValue;
        r.attempts      = attempts;
        r.completed     = true;
        task3Ref->logActivity(r);

        cout << "\n  Correct! You earned " << earned << " point(s)!\n";
        nextActivity();
    } else {
        cout << "\n  Not quite. Correct answer: " << activity.answer << "\n";
        logger.logOutcome(activity.id, activity.title, 0, activity.pointsValue, attempts);
        cout << "  Attempts so far: " << attempts << "\n";
        cout << "  Try again? (y/n): ";
        char t; cin >> t; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (tolower(t) == 'y') showCurrentActivity();
    }
}

// ============================================================
//  TASK 4: AT-RISK LEARNER PRIORITY & RECOMMENDATION ENGINE
//  Author : [Name / Student ID]
//  Data Structure : Priority Queue (max-heap by risk score)
// ============================================================

class PriorityQueue {
private:
    static const int MAX = 50;
    AtRiskLearner    data[MAX];
    int              count;

    void heapifyUp(int idx) {
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (data[idx].riskScore > data[parent].riskScore) {
                AtRiskLearner tmp = data[idx];
                data[idx]        = data[parent];
                data[parent]     = tmp;
                idx = parent;
            } else break;
        }
    }

    void heapifyDown(int idx) {
        while (true) {
            int left    = 2 * idx + 1;
            int right   = 2 * idx + 2;
            int largest = idx;
            if (left  < count && data[left].riskScore  > data[largest].riskScore) largest = left;
            if (right < count && data[right].riskScore > data[largest].riskScore) largest = right;
            if (largest != idx) {
                AtRiskLearner tmp = data[idx];
                data[idx]         = data[largest];
                data[largest]     = tmp;
                idx = largest;
            } else break;
        }
    }

public:
    PriorityQueue() : count(0) {}

    bool isEmpty()  { return count == 0; }
    int  getCount() { return count; }

    void insert(AtRiskLearner learner) {
        if (count < MAX) {
            data[count++] = learner;
            heapifyUp(count - 1);
        }
    }

    AtRiskLearner extractMax() {
        AtRiskLearner top = data[0];
        data[0] = data[--count];
        heapifyDown(0);
        return top;
    }
};

class Task4 {
private:
    Task3* task3Ref;

    // Risk score formula:
    //   +1.0 per failed attempt
    //   +up to 3.0 for low score ratio (below 60%)
    //   +2.0 per incomplete activity
    float calculateRiskScore(int learnerId) {
        LogRecord records[MAX_LOG];
        int count = task3Ref->getRecordsByLearner(learnerId, records, MAX_LOG);
        if (count == 0) return 0.0f;
        float risk = 0.0f;
        for (int i = 0; i < count; i++) {
            risk += (records[i].attempts - 1) * 1.0f;
            if (records[i].maxScore > 0) {
                float ratio = (float)records[i].score / records[i].maxScore;
                if (ratio < 0.6f) risk += (1.0f - ratio) * 3.0f;
            }
            if (!records[i].completed) risk += 2.0f;
        }
        return risk;
    }

    string generateRecommendation(int learnerId, float riskScore) {
        LogRecord records[MAX_LOG];
        int count = task3Ref->getRecordsByLearner(learnerId, records, MAX_LOG);
        if (count == 0) return "No activity data available.";

        int   worstIdx   = 0;
        float worstRatio = 1.0f;
        for (int i = 0; i < count; i++) {
            float ratio = records[i].maxScore > 0
                ? (float)records[i].score / records[i].maxScore : 0.0f;
            if (ratio < worstRatio) { worstRatio = ratio; worstIdx = i; }
        }
        string worst = records[worstIdx].activityTitle;

        if      (riskScore >= 5.0f) return "High risk   - Repeat " + worst + " and attempt an easier version.";
        else if (riskScore >= 2.0f) return "Medium risk - Review " + worst + " before moving on.";
        else                        return "Low risk    - Keep going! Focus on " + worst + " for improvement.";
    }

    void buildQueue(PriorityQueue& pq) {
        int ids[MAX_LOG];
        int count = task3Ref->getUniqueLearnerIds(ids, MAX_LOG);
        for (int i = 0; i < count; i++) {
            AtRiskLearner a;
            a.learnerId      = ids[i];
            a.learnerName    = task3Ref->getLearnerName(ids[i]);
            a.riskScore      = calculateRiskScore(ids[i]);
            a.recommendation = generateRecommendation(ids[i], a.riskScore);
            pq.insert(a);
        }
    }

public:
    Task4(Task3* t3) : task3Ref(t3) {}

    void displayAtRiskLearners() {
        PriorityQueue pq;
        buildQueue(pq);
        if (pq.isEmpty()) { cout << "  No data found. Complete activities in Task 2 first.\n"; return; }

        cout << "\n  --- At-Risk Learner Rankings (Highest Risk First) ---\n";
        cout << "  " << string(70, '-') << "\n";
        cout << "  " << left << setw(5) << "Rank" << setw(20) << "Name"
             << setw(12) << "Risk Score" << "Recommendation\n";
        cout << "  " << string(70, '-') << "\n";

        int rank = 1;
        while (!pq.isEmpty()) {
            AtRiskLearner a = pq.extractMax();
            cout << "  " << left << setw(5) << rank++
                 << setw(20) << a.learnerName
                 << setw(12) << fixed << setprecision(1) << a.riskScore
                 << a.recommendation << "\n";
        }
        cout << "  " << string(70, '-') << "\n";
    }

    void exportAtRiskList() {
        PriorityQueue pq;
        buildQueue(pq);
        if (pq.isEmpty()) { cout << "  No data to export.\n"; return; }

        ofstream file("ARL.csv");
        if (!file.is_open()) { cout << "  Error: Could not create file.\n"; return; }
        file << "learner_id,learner_name,risk_score,recommendation\n";
        while (!pq.isEmpty()) {
            AtRiskLearner a = pq.extractMax();
            file << a.learnerId   << ","
                 << a.learnerName << ","
                 << fixed << setprecision(1) << a.riskScore << ","
                 << a.recommendation << "\n";
        }
        file.close();
        cout << "  Exported to at_risk_learners.csv\n";
    }

    void run() {
        int choice;
        do {
            cout << "\n===== TASK 4: AT-RISK LEARNER PRIORITY & RECOMMENDATION ENGINE =====\n";
            cout << "  [1] Display at-risk learner rankings\n";
            cout << "  [2] Export at-risk list to CSV\n";
            cout << "  [0] Back to main menu\n";
            cout << "  Enter choice: ";
            cin >> choice; cin.ignore();

            if (choice == 1)      { displayAtRiskLearners(); }
            else if (choice == 2) { exportAtRiskList(); }
            else if (choice != 0) { cout << "  Invalid choice.\n"; }
        } while (choice != 0);
    }
};

// ============================================================
//  MAIN MENU
// ============================================================

int main() {
    int sessionSize;
    cout << "Enter active session capacity: ";
    cin >> sessionSize; cin.ignore();

    Task1 task1(sessionSize);
    Task3 task3;
    Task2 task2(&task3, &task1);
    Task4 task4(&task3);

    int choice = 0;
    do {
        cout << "\n=============================================\n";
        cout << "               PLAPS  Main Menu              \n";
        cout << "=============================================\n";
        cout << "  [1] Learner Registration & Session Mgmt\n";
        cout << "  [2] Activity Navigation & Session Flow\n";
        cout << "  [3] Recent Activity Logging & History\n";
        cout << "  [4] At-Risk Learner Priority & Recs\n";
        cout << "  [0] Exit\n";
        cout << "=============================================\n";
        cout << "  Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: task1.run(); break;
            case 2: task2.run(); break;
            case 3: task3.run(); break;
            case 4: task4.run(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "  Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
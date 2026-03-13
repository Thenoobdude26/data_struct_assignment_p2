#include <iostream>
#include <cstring>
using namespace std;

// Stores learner details
struct Learner {
    int id;
    char name[50];
};

// Node for linked-list registration queue
struct Node {
    Learner data;
    Node* next;
};

// FIFO queue for learner registration
class RegistrationQueue {
private:
    Node* front;
    Node* rear;
    int count;

public:
    RegistrationQueue() {
        front = NULL;
        rear = NULL;
        count = 0;
    }

    ~RegistrationQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() {
        return front == NULL;
    }

    int getCount() {
        return count;
    }

    bool containsId(int id) {
        Node* current = front;
        while (current != NULL) {
            if (current->data.id == id) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void enqueue(Learner learner) {
        Node* newNode = new Node;
        newNode->data = learner;
        newNode->next = NULL;

        if (rear == NULL) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }

        count++;
    }

    Learner dequeue() {
        Learner temp;
        temp.id = -1;
        strcpy_s(temp.name, "");

        if (isEmpty()) {
            return temp;
        }

        Node* toDelete = front;
        temp = front->data;
        front = front->next;

        if (front == NULL) {
            rear = NULL;
        }

        delete toDelete;
        count--;
        return temp;
    }

    void display() {
        if (isEmpty()) {
            cout << "Waiting queue is empty.\n";
            return;
        }

        Node* current = front;
        cout << "\n--- Waiting Queue ---\n";
        while (current != NULL) {
            cout << "ID: " << current->data.id
                << " | Name: " << current->data.name << endl;
            current = current->next;
        }
        cout << "Total waiting learners: " << count << endl;
    }
};

// Circular queue for active session
class ActiveSessionQueue {
private:
    Learner* arr;
    int front;
    int rear;
    int count;
    int capacity;

public:
    ActiveSessionQueue(int size) {
        capacity = size;
        arr = new Learner[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    ~ActiveSessionQueue() {
        delete[] arr;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }

    int getCount() {
        return count;
    }

    int getCapacity() {
        return capacity;
    }

    bool containsId(int id) {
        int index = front;
        for (int i = 0; i < count; i++) {
            if (arr[index].id == id) {
                return true;
            }
            index = (index + 1) % capacity;
        }
        return false;
    }

    void enqueue(Learner learner) {
        if (isFull()) {
            cout << "Active session is full.\n";
            return;
        }

        rear = (rear + 1) % capacity;
        arr[rear] = learner;
        count++;
    }

    Learner dequeue() {
        Learner temp;
        temp.id = -1;
        strcpy_s(temp.name, "");

        if (isEmpty()) {
            return temp;
        }

        temp = arr[front];
        front = (front + 1) % capacity;
        count--;
        return temp;
    }

    void display() {
        if (isEmpty()) {
            cout << "Active session is empty.\n";
            return;
        }

        cout << "\n--- Active Session ---\n";
        int index = front;
        for (int i = 0; i < count; i++) {
            cout << "ID: " << arr[index].id
                << " | Name: " << arr[index].name << endl;
            index = (index + 1) % capacity;
        }
        cout << "Active learners: " << count << "/" << capacity << endl;
    }
};

// Admit next learner from registration queue into active session
void admitNextLearner(RegistrationQueue& regQueue, ActiveSessionQueue& sessionQueue) {
    if (regQueue.isEmpty()) {
        cout << "No learners waiting in registration queue.\n";
        return;
    }

    if (sessionQueue.isFull()) {
        cout << "Cannot admit learner. Active session is full.\n";
        return;
    }

    Learner learner = regQueue.dequeue();
    sessionQueue.enqueue(learner);

    cout << "Learner admitted: " << learner.name << endl;
}

// Remove learner from active session in FIFO order
void exitLearner(RegistrationQueue& regQueue, ActiveSessionQueue& sessionQueue) {
    if (sessionQueue.isEmpty()) {
        cout << "No learners in active session.\n";
        return;
    }

    Learner exited = sessionQueue.dequeue();
    cout << "Learner exited session: " << exited.name << endl;

    if (!regQueue.isEmpty() && !sessionQueue.isFull()) {
        Learner next = regQueue.dequeue();
        sessionQueue.enqueue(next);
        cout << "Next learner admitted automatically: " << next.name << endl;
    }
}

int main() {
    int sessionSize;
    cout << "Enter active session capacity: ";
    cin >> sessionSize;
    cin.ignore();

    RegistrationQueue regQueue;
    ActiveSessionQueue sessionQueue(sessionSize);

    int choice;

    do {
        cout << "\n===== PLAPS: Learner Registration & Session Management =====\n";
        cout << "1. Register learner\n";
        cout << "2. Admit next learner to session\n";
        cout << "3. Exit learner from session\n";
        cout << "4. Display waiting queue\n";
        cout << "5. Display active session\n";
        cout << "6. Display system summary\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            Learner learner;
            cout << "Enter learner ID: ";
            cin >> learner.id;
            cin.ignore();

            if (regQueue.containsId(learner.id) || sessionQueue.containsId(learner.id)) {
                cout << "Error: Learner ID already exists.\n";
                continue;
            }

            cout << "Enter learner name: ";
            cin.getline(learner.name, 50);

            regQueue.enqueue(learner);
            cout << "Learner registered successfully.\n";
        }
        else if (choice == 2) {
            admitNextLearner(regQueue, sessionQueue);
        }
        else if (choice == 3) {
            exitLearner(regQueue, sessionQueue);
        }
        else if (choice == 4) {
            regQueue.display();
        }
        else if (choice == 5) {
            sessionQueue.display();
        }
        else if (choice == 6) {
            cout << "\n--- System Summary ---\n";
            cout << "Waiting learners: " << regQueue.getCount() << endl;
            cout << "Active learners: " << sessionQueue.getCount()
                << "/" << sessionQueue.getCapacity() << endl;
        }
        else if (choice == 0) {
            cout << "Exiting system...\n";
        }
        else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}
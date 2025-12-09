#include <iostream>
using namespace std;


struct CustomerNode {
    int customerID; 
    CustomerNode* next; 

    CustomerNode(int id) : customerID(id), next(nullptr) {}
};

class Queue {
private:
    CustomerNode* head; 
    CustomerNode* rear; 

public:
    
    Queue() : head(nullptr), rear(nullptr) {}

    ~Queue() {
        while (head) {
            CustomerNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void enqueue(int id) {
        CustomerNode* newCustomer = new CustomerNode(id);
        
        if (!head) {

            head = rear = newCustomer;
        } else {
            
            rear->next = newCustomer;
            rear = newCustomer;
        }
        cout << "Customer " << id << " joined the queue.\n";
    }


    void dequeue() {
        if (!head) {
            cout << "Queue is empty. No customers to serve.\n";
            return;
        }

        CustomerNode* temp = head;
        cout << "Serving customer " << head->customerID << ".\n";
        
        head = head->next;
        delete temp;

        if (!head) {

            rear = nullptr;
        }
    }

    void displayQueue() const {
        if (!head) {
            cout << "Queue is empty.\n";
            return;
        }

        cout << "Current queue: [";
        CustomerNode* current = head;
        while (current) {
            cout << current->customerID;
            if (current->next) cout << ", ";
            current = current->next;
        }
        cout << "]\n";
    }

    void Peek() const {
        if (!head) {
            cout << "Queue is empty. No customers waiting.\n";
        } else {
            cout << "Next customer to be served: " << head->customerID << "\n";
        }
    }
};

int main() {
 
    Queue bankQueue;

    cout << "=== Bank Queue Simulation ===\n\n";


    cout << "Adding customers to queue:\n";
    bankQueue.enqueue(101);
    bankQueue.enqueue(102);
    bankQueue.enqueue(103);
    bankQueue.enqueue(104);
    bankQueue.enqueue(105);
    
    cout << "\nInitial queue state:\n";
    bankQueue.displayQueue();

    cout << "\nServing customers:\n";

    bankQueue.dequeue(); 
    bankQueue.dequeue();  

    cout << "\nRemaining customers in queue:\n";
    bankQueue.displayQueue(); 

    cout << "\nChecking next customer:\n";
    bankQueue.Peek();  

    return 0;
}

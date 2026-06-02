#include "OrderManagement.hpp"
#include <iostream>

using namespace std;


Order::Order(int id, std::string item) {
    orderId = id;
    itemName = item;
    status = "pending";
    next = nullptr;
}

OrderQueue::OrderQueue(int maxCapacity) {
    front = nullptr;
    rear = nullptr;
    size = 0;
    maxSize = maxCapacity; // default max capacity = 20
    completedHead = nullptr;
}

// Destructor 
OrderQueue::~OrderQueue() {

    // Delete all pending orders
    Order* temp = front;
    while (temp != nullptr) {
        Order* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    front = nullptr;
    rear = nullptr;

    // Delete all completed orders
    temp = completedHead;
    while (temp != nullptr) {
        Order* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    completedHead = nullptr;
}

void OrderQueue::enqueue(int orderId, string itemName) {
    // overflow case
    if (isFull()) {
        cout << "Queue Overflow: Cannot add order #" << orderId 
             << " (" << itemName << "). The order queue is full.\n";
        return;
    }
    Order* newnode = new Order(orderId, itemName);
    newnode->next = nullptr;

    // if queue is empty ，set new node as front and rear
    if (front == nullptr) {
        front = rear = newnode;
    } 

    else { // else , add to the back and update rear
        rear->next = newnode;
        rear = newnode;
    }
    
    size++;
    cout << "Order #" << orderId << " (" << itemName << ") added to the queue.\n";
}


Order* OrderQueue::dequeue() {

    // underflow case
    if (front == nullptr) {
        cout << "Queue Underflow: The order queue is empty.\n";
        return nullptr;
    }

    Order* temp = front;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    size--; 
    temp->next = nullptr; // detach from queue
    return temp;
}


Order* OrderQueue::peek() const {
    return front;
}

bool OrderQueue::isEmpty() const {
    return front == nullptr;
}

bool OrderQueue::isFull() const {
    return size >= maxSize;
}

int OrderQueue::getSize() const {
    return size;
}


void OrderQueue::markCompleted(Order* order) {
    if (order == nullptr) return;

    order->status = "completed";

    // Add to completed list
    order->next = completedHead;
    completedHead = order;
    
    cout << "Order #" << order->orderId << " marked as completed.\n";
}

// Function to process dequeue and mark as completed
void OrderQueue::processNextOrder() {

    Order* nextOrder = dequeue();

    // empty queue case
    if (nextOrder == nullptr) {
        cout << "System Status: No orders available in the queue to process.\n";
        return;
    }

    markCompleted(nextOrder);
}


// Print all pending orders in the queue
void OrderQueue::displayPending() const {
    cout << "\n--- Pending Orders ---\n";
    
    if (isEmpty()) {
        cout << "No pending orders.\n";
        return;
    }

    // Traverse and print from front to rear
    Order* temp = front;
    while (temp != nullptr) {
        cout << "ID: " << temp->orderId 
             << " | Item: " << temp->itemName 
             << " | Status: " << temp->status << "\n";
        temp = temp->next;
    }
}

// Print all completed orders
void OrderQueue::displayCompleted() const {
    cout << "\n--- Completed Orders ---\n";

    if (completedHead == nullptr) {
        cout << "No completed orders yet.\n";
        return;
    }

    // Traverse and print from completedHead to end
    Order* temp = completedHead;
    while (temp != nullptr) {
        cout << "ID: " << temp->orderId 
             << " | Item: " << temp->itemName 
             << " | Status: " << temp->status << "\n";
        temp = temp->next;
    }
}

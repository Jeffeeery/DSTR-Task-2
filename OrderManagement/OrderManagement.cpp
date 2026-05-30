/*
 * Task 1 — Order Management Module Implementation
 * Member: LAI KAH FON
 * Student ID: TP077207
 * Data Structure: Queue (self-implemented, FIFO)
 */

#include "OrderManagement.hpp"
#include <iostream>

using namespace std;



// ---------------------------------------------------------------
// Order constructor
// ---------------------------------------------------------------
Order::Order(int id, std::string item) {
    orderId = id;
    itemName = item;
    status = "pending";
    next = nullptr;
}

// ---------------------------------------------------------------
// OrderQueue constructor
// ---------------------------------------------------------------
OrderQueue::OrderQueue() {
    front = nullptr;
    rear = nullptr;
    size = 0;
    completedHead = nullptr;
}

// destructor 
OrderQueue::~OrderQueue() {
    // Delete all nodes in the pending queue
    Order* temp = front;
    while (temp != nullptr) {
        Order* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    front = nullptr;
    rear = nullptr;

    // Delete all nodes in the completed history list
    temp = completedHead;
    while (temp != nullptr) {
        Order* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    completedHead = nullptr;
}

// ---------------------------------------------------------------
// enqueue — add new order to rear of queue
// ---------------------------------------------------------------
void OrderQueue::enqueue(int orderId, string itemName) {
    Order* newnode = new Order(orderId, itemName);
    newnode->next = nullptr;

    // If queue is empty, set both front and rear to the new node
    if (front == nullptr) {
        front = rear = newnode;
    } 
    // Otherwise, append to the back and update rear
    else {
        rear->next = newnode;
        rear = newnode;
    }
    
    size++;
    cout << "Order #" << orderId << " (" << itemName << ") added to the queue.\n";
}

// ---------------------------------------------------------------
// dequeue — remove and return front order
// ---------------------------------------------------------------
Order* OrderQueue::dequeue() {
    // Check for queue underflow
    if (front == nullptr) {
        cout << "Queue Underflow: The order queue is empty.\n";
        return nullptr;
    }

    // Disconnect the front node
    Order* temp = front;
    front = front->next;

    // If queue becomes empty, reset rear to nullptr
    if (front == nullptr) {
        rear = nullptr;
    }

    size--; 
    temp->next = nullptr; // Detach node link cleanly before returning
    return temp;
}

// ---------------------------------------------------------------
// peek — view front order without removing
// ---------------------------------------------------------------
Order* OrderQueue::peek() const {
    return front;
}

bool OrderQueue::isEmpty() const {
    return front == nullptr;
}

int OrderQueue::getSize() const {
    return size;
}

// ---------------------------------------------------------------
// markCompleted — move a processed order to the completed list
// ---------------------------------------------------------------
void OrderQueue::markCompleted(Order* order) {
    if (order == nullptr) return;

    order->status = "completed";

    // Prepend the order to the completed head list
    order->next = completedHead;
    completedHead = order;
    
    cout << "Order #" << order->orderId << " marked as completed.\n";
}

// ---------------------------------------------------------------
// displayPending — print all orders currently in the queue
// ---------------------------------------------------------------
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

// ---------------------------------------------------------------
// displayCompleted — print all completed orders
// ---------------------------------------------------------------
void OrderQueue::displayCompleted() const {
    cout << "\n--- Completed Orders ---\n";

    if (completedHead == nullptr) {
        cout << "No completed orders yet.\n";
        return;
    }

    // Traverse and print from completedHead to the end
    Order* temp = completedHead;
    while (temp != nullptr) {
        cout << "ID: " << temp->orderId 
             << " | Item: " << temp->itemName 
             << " | Status: " << temp->status << "\n";
        temp = temp->next;
    }
}

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
    maxSize = maxCapacity;
    completedHead = nullptr;
}


OrderQueue::~OrderQueue() {

    Order* temp = front;
    while (temp != nullptr) {
        Order* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    front = nullptr;
    rear = nullptr;

    temp = completedHead;
    while (temp != nullptr) {
        Order* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    completedHead = nullptr;
}

void OrderQueue::enqueue(int orderId, string itemName) {

    if (isFull()) {
        cout << "Queue Overflow: Cannot add order #" << orderId 
             << " (" << itemName << "). The order queue is full.\n";
        return;
    }
    Order* newnode = new Order(orderId, itemName);
    newnode->next = nullptr;

    if (front == nullptr) {
        front = rear = newnode;
    } 

    else {
        rear->next = newnode;
        rear = newnode;
    }
    
    size++;
    cout << "Order #" << orderId << " (" << itemName << ") added to the queue.\n";
}


Order* OrderQueue::dequeue() {

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
    temp->next = nullptr; 
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

    order->next = completedHead;
    completedHead = order;
    
    cout << "Order #" << order->orderId << " marked as completed.\n";
}

void OrderQueue::processNextOrder() {

    Order* nextOrder = dequeue();

    if (nextOrder == nullptr) {
        cout << "System Status: No orders available in the queue to process.\n";
        return;
    }

    markCompleted(nextOrder);
}



void OrderQueue::displayPending() const {
    cout << "\n--- Pending Orders ---\n";
    
    if (isEmpty()) {
        cout << "No pending orders.\n";
        return;
    }

    Order* temp = front;
    while (temp != nullptr) {
        cout << "ID: " << temp->orderId 
             << " | Item: " << temp->itemName 
             << " | Status: " << temp->status << "\n";
        temp = temp->next;
    }
}


void OrderQueue::displayCompleted() const {
    cout << "\n--- Completed Orders ---\n";

    if (completedHead == nullptr) {
        cout << "No completed orders yet.\n";
        return;
    }

    Order* temp = completedHead;
    while (temp != nullptr) {
        cout << "ID: " << temp->orderId 
             << " | Item: " << temp->itemName 
             << " | Status: " << temp->status << "\n";
        temp = temp->next;
    }
}

/*
 * Task 1 — Order Management Module Implementation
 * Member: [Your Name]
 * Student ID: [Your ID]
 * Data Structure: Queue (self-implemented, FIFO)
 */

#include "OrderManagement.hpp"

using namespace std;

// ---------------------------------------------------------------
// Order constructor
// ---------------------------------------------------------------
Order::Order(int id, string item) {
    // TODO: Initialize orderId = id, itemName = item
    // TODO: Set status = "pending", next = nullptr
}

// ---------------------------------------------------------------
// OrderQueue constructor
// ---------------------------------------------------------------
OrderQueue::OrderQueue() {
    // TODO: Initialize front = nullptr, rear = nullptr
    // TODO: Initialize size = 0, completedHead = nullptr
}

// ---------------------------------------------------------------
// OrderQueue destructor — free all allocated memory
// ---------------------------------------------------------------
OrderQueue::~OrderQueue() {
    // TODO: Traverse pending queue and delete each Order node
    // TODO: Traverse completedHead list and delete each Order node
}

// ---------------------------------------------------------------
// enqueue — add new order to rear of queue
// ---------------------------------------------------------------
void OrderQueue::enqueue(int orderId, string itemName) {
    // TODO: Create new Order node
    // TODO: If queue empty (front == nullptr): set front = rear = new node
    // TODO: Otherwise: rear->next = new node, then rear = new node
    // TODO: Increment size
    // TODO: Print confirmation message
}

// ---------------------------------------------------------------
// dequeue — remove and return front order
// ---------------------------------------------------------------
Order* OrderQueue::dequeue() {
    // TODO: If empty, print error message and return nullptr
    // TODO: Save current front node
    // TODO: Move front = front->next
    // TODO: If front is now nullptr, also set rear = nullptr (queue empty)
    // TODO: Decrement size
    // TODO: Set saved node's next = nullptr before returning
    // TODO: Return the saved node (caller must handle memory)
    return nullptr;
}

// ---------------------------------------------------------------
// peek — view front order without removing
// ---------------------------------------------------------------
Order* OrderQueue::peek() const {
    // TODO: Return front (nullptr if empty)
    return nullptr;
}

bool OrderQueue::isEmpty() const {
    // TODO: Return true if front == nullptr
    return true;
}

int OrderQueue::getSize() const {
    // TODO: Return size
    return 0;
}

// ---------------------------------------------------------------
// markCompleted — move a processed order to the completed list
// ---------------------------------------------------------------
void OrderQueue::markCompleted(Order* order) {
    // TODO: Set order->status = "completed"
    // TODO: Prepend to completedHead: order->next = completedHead, completedHead = order
}

// ---------------------------------------------------------------
// displayPending — print all orders currently in the queue
// ---------------------------------------------------------------
void OrderQueue::displayPending() const {
    // TODO: Print header
    // TODO: If empty, print "No pending orders."
    // TODO: Traverse front to rear, print orderId, itemName, status
}

// ---------------------------------------------------------------
// displayCompleted — print all completed orders
// ---------------------------------------------------------------
void OrderQueue::displayCompleted() const {
    // TODO: Print header
    // TODO: If completedHead == nullptr, print "No completed orders yet."
    // TODO: Traverse completedHead list, print each order
}

/*
 * Task 1 — Order Management Module
 * Member: LAI KAH FON
 * Student ID: TP077207
 * Data Structure: Queue (self-implemented, FIFO — linked-list based)
 *
 * Responsibility:
 *   - Accept and record incoming customer orders
 *   - Process orders sequentially by arrival time (first in, first out)
 *   - Remove orders once assigned to a robot
 *   - Display pending and completed orders
 *   - Handle edge cases: empty queue, system overload
 *
 * Why Queue?
 *   Orders must be processed in the exact order they arrive — FIFO.
 *   A queue enforces this naturally: enqueue at rear, dequeue from front.
 */

#ifndef ORDER_MANAGEMENT_HPP
#define ORDER_MANAGEMENT_HPP

#include <iostream>
#include <string>

// Represents a single customer order (linked-list node)
struct Order {
    int orderId;
    std::string itemName;
    std::string status;   // "pending" or "completed"
    Order* next;          // pointer to next node in the queue

    Order(int id, std::string item);
};

// Self-implemented Queue — DO NOT use STL <queue> or any built-in container
class OrderQueue {
private:
    Order* front;       // points to the first (oldest) order — next to be processed
    Order* rear;        // points to the last (newest) order added
    int size;           // number of pending orders currently in the queue
    Order* completedHead; // head of completed orders list

public:
    OrderQueue();
    ~OrderQueue();

    // Add a new order to the rear of the queue
    void enqueue(int orderId, std::string itemName);

    // Remove and return the front order (next to be processed)
    // Returns nullptr if queue is empty
    Order* dequeue();

    // View the front order without removing it
    Order* peek() const;

    bool isEmpty() const;
    int getSize() const;

    // Move a dequeued order to the completed list
    void markCompleted(Order* order);

    // Print all pending orders (front to rear)
    void displayPending() const;

    // Print all completed orders
    void displayCompleted() const;

    // TODO: Add any additional helper methods you need
};

#endif // ORDER_MANAGEMENT_HPP

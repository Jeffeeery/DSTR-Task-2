/*
 * Task 3 — Robot Navigation & Path Tracking Implementation
 * Member: Eee Kong Siong
 * Student ID: TP076904
 * Data Structure: Stack (self-implemented, LIFO)
 */
#ifndef ROBOT_NAVIGATION_HPP
#define ROBOT_NAVIGATION_HPP

#include <iostream>
#include <string>

using namespace std;

// Stack node — one movement step
struct Step {
    string direction;  // "forward", "left", "right", "backward"
    string location;   // location label reached after this step
    Step* next;        // pointer to step below in the stack
};

// Self-implemented linked-list stack
class PathStack {
private:
    Step* top;  // pointer to most recently recorded step
    int size;

    // prints path in chronological order (bottom to top)
    void displayForwardRecursive(Step* current, int& stepNum) const;

public:
    PathStack();
    ~PathStack();

    void push(string direction, string location);
    void pop();

    Step* peek() const;
    bool isEmpty() const;
    int getSize() const;

    // Display stack top to bottom
    void display() const;

    // Display path in chronological order
    void displayForwardPath() const;

    // Simulate full return via reversed path
    void returnPath();

    // Undo last step when obstacle encountered
    void backtrack();

    // Maps a direction to its opposite
    string reverseDirection(string dir) const;
};

#endif // ROBOT_NAVIGATION_HPP

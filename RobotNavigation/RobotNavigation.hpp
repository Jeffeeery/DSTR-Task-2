/*
 * Task 3 — Robot Navigation & Path Tracking Module
 * Member: [Your Name]
 * Student ID: [Your ID]
 * Data Structure: Stack (self-implemented, LIFO — linked-list based)
 *
 * Responsibility:
 *   - Record each movement step: forward, left, right, backward
 *   - Store the full path from start to destination
 *   - Reverse path step-by-step for the return journey (pop stack)
 *   - Handle obstacles via backtracking (pop last step)
 *   - Simulate robot movement via step-by-step logs
 *
 * Why Stack?
 *   The return journey is the exact reverse of the forward path.
 *   A stack stores steps LIFO — the last step pushed is the first popped,
 *   naturally producing the reverse route without extra computation.
 */

#ifndef ROBOT_NAVIGATION_HPP
#define ROBOT_NAVIGATION_HPP

#include <iostream>
#include <string>

using namespace std;

// Represents a single movement step (stack node)
struct Step {
    string direction;  // "forward", "left", "right", "backward"
    string location;   // label of location reached after this step
    Step* next;             // pointer to the step below in the stack

    Step(string dir, string loc);
};

// Self-implemented Stack — DO NOT use STL <stack> or any built-in container
class PathStack {
private:
    Step* top;  // most recently recorded step
    int size;

public:
    PathStack();
    ~PathStack();

    // Push a new movement step (record one move forward)
    void push(string direction, string location);

    // Pop and return top step (retrace path); returns nullptr if empty
    Step* pop();

    Step* peek() const;
    bool isEmpty() const;
    int getSize() const;

    // Display full path in forward order (first step first)
    void displayForwardPath() const;

    // Simulate full return: pop each step and print reverse direction
    void returnPath();

    // Undo last step (obstacle encountered)
    void backtrack();

    // Returns the opposite direction: "forward"<->"backward", "left"<->"right"
    string reverseDirection(string dir) const;

    // TODO: Add any additional helper methods
};

#endif // ROBOT_NAVIGATION_HPP

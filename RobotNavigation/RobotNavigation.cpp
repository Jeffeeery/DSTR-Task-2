/*
 * Task 3 — Robot Navigation & Path Tracking Implementation
 * Member: [Your Name]
 * Student ID: [Your ID]
 * Data Structure: Stack (self-implemented, LIFO)
 */

#include "RobotNavigation.hpp"

using namespace std;

// ---------------------------------------------------------------
// Step constructor
// ---------------------------------------------------------------
Step::Step(string dir, string loc) {
    direction = dir;
    location  = loc;
    next      = nullptr;
}

// ---------------------------------------------------------------
// PathStack constructor
// ---------------------------------------------------------------
PathStack::PathStack() {
    top  = nullptr;
    size = 0;
}

// ---------------------------------------------------------------
// PathStack destructor — free all step nodes
// ---------------------------------------------------------------
PathStack::~PathStack() {
    while (!isEmpty()) {
        Step* temp = pop();
        delete temp;
    }
}

// ---------------------------------------------------------------
// push — record one movement step
// ---------------------------------------------------------------
void PathStack::push(string direction, string location) {
    Step* newStep = new Step(direction, location);
    newStep->next = top;   // link new step above current top
    top = newStep;
    size++;
    cout << "Robot moved " << direction << " -> " << location << endl;
}

// ---------------------------------------------------------------
// pop — remove and return top step (caller must delete)
// ---------------------------------------------------------------
Step* PathStack::pop() {
    if (isEmpty()) {
        cout << "Error: No steps to pop — path is empty." << endl;
        return nullptr;
    }
    Step* saved = top;
    top = top->next;
    saved->next = nullptr;
    size--;
    return saved;
}

// ---------------------------------------------------------------
// peek — view top step without removing
// ---------------------------------------------------------------
Step* PathStack::peek() const {
    return top;
}

// ---------------------------------------------------------------
// isEmpty
// ---------------------------------------------------------------
bool PathStack::isEmpty() const {
    return top == nullptr;
}

// ---------------------------------------------------------------
// getSize
// ---------------------------------------------------------------
int PathStack::getSize() const {
    return size;
}

// ---------------------------------------------------------------
// displayForwardPath — print path in forward order (first step first)
// Stack top = last step pushed, so collect into raw array and
// print from highest index (oldest step) down to 0.
// ---------------------------------------------------------------
void PathStack::displayForwardPath() const {
    cout << "\n=== Forward Path ===" << endl;
    if (isEmpty()) {
        cout << "No path recorded." << endl;
        return;
    }

    // Collect all step pointers into a raw array (no STL allowed)
    Step** steps = new Step*[size];
    Step* curr = top;
    for (int i = 0; i < size; i++) {
        steps[i] = curr;
        curr = curr->next;
    }

    // steps[size-1] = first step pushed, steps[0] = last step pushed
    for (int i = size - 1; i >= 0; i--) {
        cout << "  Step " << (size - i) << ": "
             << steps[i]->direction << " -> " << steps[i]->location << endl;
    }

    delete[] steps;
}

// ---------------------------------------------------------------
// returnPath — simulate robot returning via reversed path
// Pops steps LIFO, prints each with its reversed direction.
// ---------------------------------------------------------------
void PathStack::returnPath() {
    cout << "\n=== Return Path (Reverse) ===" << endl;
    if (isEmpty()) {
        cout << "No path to reverse." << endl;
        return;
    }

    int stepNum = 1;
    while (!isEmpty()) {
        Step* step = pop();
        string rev = reverseDirection(step->direction);
        cout << "  Step " << stepNum++ << ": Robot moves "
             << rev << " <- " << step->location << endl;
        delete step;
    }
}

// ---------------------------------------------------------------
// backtrack — undo last step when obstacle is encountered
// ---------------------------------------------------------------
void PathStack::backtrack() {
    if (isEmpty()) {
        cout << "Cannot backtrack — no steps recorded." << endl;
        return;
    }
    Step* step = pop();
    cout << "Obstacle! Backtracking from " << step->location << "..." << endl;
    delete step;
}

// ---------------------------------------------------------------
// reverseDirection — maps each direction to its opposite
// ---------------------------------------------------------------
string PathStack::reverseDirection(string dir) const {
    if (dir == "forward")  return "backward";
    if (dir == "backward") return "forward";
    if (dir == "left")     return "right";
    if (dir == "right")    return "left";
    return "unknown";
}

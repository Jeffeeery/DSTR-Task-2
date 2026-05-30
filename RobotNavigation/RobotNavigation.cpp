// Task 3 — Robot Navigation & Path Tracking Implementation

#include "RobotNavigation.hpp"

using namespace std;

// PathStack constructor
PathStack::PathStack() {
    top  = nullptr;
    size = 0;
}

// PathStack destructor — free all nodes individually (linked-list standard)
PathStack::~PathStack() {
    while (!isEmpty()) {
        pop();  // pop() handles deletion internally
    }
}

// push — record one movement step and link at head
void PathStack::push(string direction, string location) {
    Step* newStep      = new Step;
    newStep->direction = direction;
    newStep->location  = location;
    newStep->next      = top;

    top = newStep;
    size++;
    cout << "Robot moved " << direction << " -> " << location << " [pushed into stack]" << endl;
}

// pop — underflow check, then delete top node internally
void PathStack::pop() {
    if (isEmpty()) {
        cout << "Stack Underflow. Cannot pop." << endl;
        return;
    }
    Step* temp = top;
    cout << temp->direction << " step from " << temp->location << " popped from stack." << endl;

    top = top->next;
    delete temp;
    size--;
}

// peek — read top without removing
Step* PathStack::peek() const {
    return top;
}

// isEmpty
bool PathStack::isEmpty() const {
    return top == nullptr;
}

// getSize
int PathStack::getSize() const {
    return size;
}

// display — lecturer-style top-to-bottom output with required header
void PathStack::display() const {
    cout << "\nStack contents (Top to Bottom):" << endl;
    if (isEmpty()) {
        cout << "  (empty)" << endl;
        return;
    }
    Step* curr  = top;
    int stepNum = 1;
    while (curr != nullptr) {
        cout << "  Step " << stepNum++ << ": " << curr->direction
             << " -> " << curr->location << endl;
        curr = curr->next;
    }
}

// Recursive helper — recurses to bottom first, then prints on the way back
// Uses the call stack itself as the reversal mechanism (no heap array needed)
void PathStack::displayForwardRecursive(Step* current, int& stepNum) const {
    if (current == nullptr) return;
    displayForwardRecursive(current->next, stepNum);  // go to oldest step first
    cout << "  Step " << stepNum++ << ": "
         << current->direction << " -> " << current->location << endl;
}

// displayForwardPath — chronological order via recursion, zero array allocation
void PathStack::displayForwardPath() const {
    cout << "\n=== Forward Path ===" << endl;
    if (isEmpty()) {
        cout << "No path recorded." << endl;
        return;
    }
    int startNum = 1;
    displayForwardRecursive(top, startNum);
}

// returnPath — capture top data, then pop; prints reversed direction per step
void PathStack::returnPath() {
    cout << "\n=== Return Path (Reverse) ===" << endl;
    if (isEmpty()) {
        cout << "No path to reverse." << endl;
        return;
    }

    int stepNum = 1;
    while (!isEmpty()) {
        string originalDir = top->direction;
        string loc         = top->location;
        string rev         = reverseDirection(originalDir);

        cout << "  Step " << stepNum++ << ": Robot moves "
             << rev << " <- " << loc << endl;

        pop();  // pop() prints confirmation and frees memory
    }
}

// backtrack — undo last step when obstacle encountered
void PathStack::backtrack() {
    if (isEmpty()) {
        cout << "Cannot backtrack — no steps recorded." << endl;
        return;
    }
    cout << "Obstacle encountered! Backtracking from " << top->location << "..." << endl;
    pop();
}

// reverseDirection — maps each direction to its opposite
string PathStack::reverseDirection(string dir) const {
    if (dir == "forward")  return "backward";
    if (dir == "backward") return "forward";
    if (dir == "left")     return "right";
    if (dir == "right")    return "left";
    return "unknown";
}

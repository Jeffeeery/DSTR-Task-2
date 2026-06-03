/*
 * Task 2 — Robot Assignment Module Implementation
 * Member: Ban Cong Yin Brosnan
 * Student ID: TP076560
 * Data Structure: Circular Queue (self-implemented, circular linked-list)
 */

#include "RobotAssignment.hpp"

using namespace std;

Robot::Robot(int id) {
    robotId       = id;
    status        = "available";
    tasksAssigned = 0;
    next          = nullptr;
}

RobotCircularQueue::RobotCircularQueue() {
    current = nullptr;
    count   = 0;
}

RobotCircularQueue::~RobotCircularQueue() {
    if (current == nullptr) return;

    // Break the circular link before deleting to avoid infinite traversal
    Robot* tail = current;
    while (tail->next != current) {
        tail = tail->next;
    }
    tail->next = nullptr;

    Robot* ptr = current;
    while (ptr != nullptr) {
        Robot* temp = ptr;
        ptr = ptr->next;
        delete temp;
    }
    current = nullptr;
}

void RobotCircularQueue::addRobot(int robotId) {
    Robot* newRobot = new Robot(robotId);

    if (current == nullptr) {
        newRobot->next = newRobot; // First node points to itself
        current = newRobot;
    } else {
        // Find tail (node whose next == current) and insert before current
        Robot* tail = current;
        while (tail->next != current) {
            tail = tail->next;
        }
        tail->next     = newRobot;
        newRobot->next = current;
    }

    count++;
    cout << "[RobotAssignment] Robot " << robotId << " registered." << endl;
}

Robot* RobotCircularQueue::assignNext() {
    if (isEmpty()) {
        cout << "[RobotAssignment] ERROR: No robots registered." << endl;
        return nullptr;
    }

    // Try at most `count` robots to avoid infinite loop when all are busy
    int tried = 0;
    while (tried < count) {
        if (current->status == "available") {
            Robot* assigned  = current;
            assigned->status = "busy";
            assigned->tasksAssigned++;
            current = current->next; // Advance rotation pointer

            cout << "[RobotAssignment] Robot " << assigned->robotId
                 << " assigned. (Total tasks: " << assigned->tasksAssigned << ")" << endl;
            return assigned;
        }
        current = current->next;
        tried++;
    }

    cout << "[RobotAssignment] No available robots at the moment." << endl;
    return nullptr;
}

void RobotCircularQueue::markAvailable(int robotId) {
    if (isEmpty()) return;

    Robot* ptr = current;
    for (int i = 0; i < count; i++) {
        if (ptr->robotId == robotId) {
            ptr->status = "available";
            cout << "[RobotAssignment] Robot " << robotId << " is now available." << endl;
            return;
        }
        ptr = ptr->next;
    }
    cout << "[RobotAssignment] Robot " << robotId << " not found." << endl;
}

void RobotCircularQueue::markMaintenance(int robotId) {
    if (isEmpty()) return;

    Robot* ptr = current;
    for (int i = 0; i < count; i++) {
        if (ptr->robotId == robotId) {
            ptr->status = "maintenance";
            cout << "[RobotAssignment] Robot " << robotId << " set to maintenance." << endl;
            return;
        }
        ptr = ptr->next;
    }
    cout << "[RobotAssignment] Robot " << robotId << " not found." << endl;
}

void RobotCircularQueue::displayStatus() const {
    cout << "\n--- Robot Status Overview ---" << endl;
    if (isEmpty()) {
        cout << "  No robots registered." << endl;
        return;
    }

    Robot* ptr = current;
    for (int i = 0; i < count; i++) {
        cout << "  Robot " << ptr->robotId
             << " | Status: " << ptr->status << endl;
        ptr = ptr->next;
    }
    cout << "-----------------------------" << endl;
}

void RobotCircularQueue::displayAssignments() const {
    cout << "\n--- Robot Assignment Summary ---" << endl;
    if (isEmpty()) {
        cout << "  No robots registered." << endl;
        return;
    }

    Robot* ptr = current;
    for (int i = 0; i < count; i++) {
        cout << "  Robot " << ptr->robotId
             << " | Tasks Assigned: " << ptr->tasksAssigned << endl;
        ptr = ptr->next;
    }
    cout << "--------------------------------" << endl;
}

bool RobotCircularQueue::isEmpty() const {
    return current == nullptr;
}

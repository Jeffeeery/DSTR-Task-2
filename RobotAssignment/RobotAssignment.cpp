/*
 * Task 2 — Robot Assignment Module Implementation
 * Member: [Your Name]
 * Student ID: [Your ID]
 * Data Structure: Circular Queue (self-implemented)
 */

#include "RobotAssignment.hpp"

using namespace std;

// ---------------------------------------------------------------
// Robot constructor
// ---------------------------------------------------------------
Robot::Robot(int id) {
    // TODO: Initialize robotId = id, status = "available"
    // TODO: tasksAssigned = 0, next = nullptr
}

// ---------------------------------------------------------------
// RobotCircularQueue constructor
// ---------------------------------------------------------------
RobotCircularQueue::RobotCircularQueue() {
    // TODO: Initialize current = nullptr, count = 0
}

// ---------------------------------------------------------------
// Destructor — free all robot nodes
// ---------------------------------------------------------------
RobotCircularQueue::~RobotCircularQueue() {
    // TODO: Break the circular link first (find tail, set tail->next = nullptr)
    // TODO: Traverse and delete each Robot node
    // TODO: Set current = nullptr
}

// ---------------------------------------------------------------
// addRobot — insert robot into circular queue
// ---------------------------------------------------------------
void RobotCircularQueue::addRobot(int robotId) {
    // TODO: Create new Robot node
    // TODO: If empty (current == nullptr):
    //         new->next = new (points to itself), current = new
    // TODO: Otherwise:
    //         Find tail (node whose next == current)
    //         tail->next = new, new->next = current
    //         (insert before current to preserve rotation order)
    // TODO: Increment count
}

// ---------------------------------------------------------------
// assignNext — rotate and assign next available robot
// ---------------------------------------------------------------
Robot* RobotCircularQueue::assignNext() {
    // TODO: If empty, print error and return nullptr
    // TODO: Traverse up to `count` robots from current:
    //         If status == "available":
    //           set status = "busy", increment tasksAssigned
    //           advance current to next robot
    //           print assignment message, return robot
    //         Else: move to next and continue
    // TODO: If no available robot found, print message and return nullptr
    return nullptr;
}

// ---------------------------------------------------------------
// markAvailable
// ---------------------------------------------------------------
void RobotCircularQueue::markAvailable(int robotId) {
    // TODO: Traverse circular list (count steps)
    // TODO: Find robot by robotId, set status = "available"
    // TODO: Print confirmation
}

// ---------------------------------------------------------------
// markMaintenance
// ---------------------------------------------------------------
void RobotCircularQueue::markMaintenance(int robotId) {
    // TODO: Traverse circular list (count steps)
    // TODO: Find robot by robotId, set status = "maintenance"
    // TODO: Print confirmation
}

// ---------------------------------------------------------------
// displayStatus
// ---------------------------------------------------------------
void RobotCircularQueue::displayStatus() const {
    // TODO: Print header
    // TODO: If empty, print "No robots registered."
    // TODO: Traverse count steps, print robotId and status for each
}

// ---------------------------------------------------------------
// displayAssignments
// ---------------------------------------------------------------
void RobotCircularQueue::displayAssignments() const {
    // TODO: Print header
    // TODO: Traverse count steps, print robotId and tasksAssigned
}

bool RobotCircularQueue::isEmpty() const {
    // TODO: Return true if current == nullptr
    return true;
}

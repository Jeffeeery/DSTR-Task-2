/*
 * Task 2 — Robot Assignment Module
 * Member: [Your Name]
 * Student ID: [Your ID]
 * Data Structure: Circular Queue (self-implemented, circular linked-list)
 *
 * Responsibility:
 *   - Maintain list of robots with status: available / busy / maintenance
 *   - Assign tasks in continuous rotation — no cycle restart
 *   - Skip robots that are unavailable or under maintenance
 *   - Track task count per robot
 *   - Ensure uninterrupted assignment cycle
 *
 * Why Circular Queue?
 *   Robots are assigned in round-robin rotation. A circular structure
 *   wraps the pointer naturally from the last robot back to the first —
 *   no reset needed, and no robot is permanently skipped.
 */

#ifndef ROBOT_ASSIGNMENT_HPP
#define ROBOT_ASSIGNMENT_HPP

#include <iostream>
#include <string>

using namespace std;

// Represents a single robot (circular linked-list node)
struct Robot {
    int robotId;
    string status;     // "available", "busy", or "maintenance"
    int tasksAssigned;      // total tasks assigned to this robot
    Robot* next;            // last robot's next points back to first

    Robot(int id);
};

// Self-implemented Circular Queue — DO NOT use STL containers
class RobotCircularQueue {
private:
    Robot* current;     // rotating pointer — always points to next candidate
    int count;          // total number of robots

public:
    RobotCircularQueue();
    ~RobotCircularQueue();

    void addRobot(int robotId);

    // Assign next available robot; skips busy/maintenance
    // Returns assigned Robot, or nullptr if none available
    Robot* assignNext();

    void markAvailable(int robotId);
    void markMaintenance(int robotId);

    void displayStatus() const;
    void displayAssignments() const;

    bool isEmpty() const;

    // TODO: Add any additional helper methods
};

#endif // ROBOT_ASSIGNMENT_HPP

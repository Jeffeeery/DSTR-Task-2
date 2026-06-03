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

// Self-implemented Circular Queue
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
};

#endif // ROBOT_ASSIGNMENT_HPP

/*
 * DSTR Lab Evaluation Work #2 — Warehouse Robot Navigation System
 * CT077-3-2-DSTR | Asia Pacific University | 2026
 *
 * Full system entry point — integrates all 5 modules:
 *   1. OrderManagement    (Queue)          — Task 1
 *   2. RobotAssignment    (Circular Queue) — Task 2
 *   3. RobotNavigation    (Stack)          — Task 3
 *   4. ItemSearch         (BST)            — Task 4
 *   5. WarehouseLayout    (Tree)           — Task 5
 *
 */

#include <iostream>
#include "OrderManagement/OrderManagement.hpp"
#include "RobotAssignment/RobotAssignment.hpp"
#include "RobotNavigation/RobotNavigation.hpp"
#include "ItemSearch/ItemSearch.hpp"
#include "WarehouseLayout/WarehouseLayout.hpp"

using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "  Warehouse Robot Navigation System     " << endl;
    cout << "========================================" << endl;

    // ----------------------------------------------------------
    // STEP 1: Initialize warehouse layout (Task 5)
    // ----------------------------------------------------------
    // TODO: Create WarehouseTree, call buildLayout()
    // TODO: Display the layout with displayLayout()

    // ----------------------------------------------------------
    // STEP 2: Load item database (Task 4)
    // ----------------------------------------------------------
    // TODO: Create ItemBST, insert sample items with ID, name, location
    // TODO: Display all items with displayAll()

    // ----------------------------------------------------------
    // STEP 3: Receive and queue incoming orders (Task 1)
    // ----------------------------------------------------------
    OrderQueue orderQueue;
    orderQueue.enqueue(1001, "Motor Part A");
    orderQueue.enqueue(1002, "Sensor Unit B");
    orderQueue.enqueue(1003, "Battery Pack C");
    orderQueue.displayPending();

    // ----------------------------------------------------------
    // STEP 4: Register robots and assign the first order (Task 2)
    // ----------------------------------------------------------
    RobotCircularQueue robotQueue;
    robotQueue.addRobot(1);
    robotQueue.addRobot(2);
    robotQueue.addRobot(3);
    robotQueue.addRobot(4);
    robotQueue.addRobot(5);

    // Simulate Robot 2 being under maintenance
    robotQueue.markMaintenance(2);

    // Dequeue first order and assign a robot to it
    Order* firstOrder = orderQueue.dequeue();
    if (firstOrder != nullptr) {
        Robot* assignedRobot = robotQueue.assignNext();
        if (assignedRobot != nullptr) {
            cout << "[System] Order " << firstOrder->orderId
                 << " assigned to Robot " << assignedRobot->robotId << endl;
        }
    }

    robotQueue.displayStatus();
    robotQueue.displayAssignments();

    // ----------------------------------------------------------
    // STEP 5: Search for item location (Task 4)
    // ----------------------------------------------------------
    // TODO: Use ItemBST::searchById() or searchByName() to find item
    // TODO: Print item location (e.g., "Zone-A/Aisle-2/Shelf-3")

    // ----------------------------------------------------------
    // STEP 6: Generate route to item via warehouse layout (Task 5)
    // ----------------------------------------------------------
    // TODO: Use WarehouseTree::getPathToLocation() to get path array
    // TODO: Print the generated route

    // ----------------------------------------------------------
    // STEP 7: Navigate robot — push each step onto stack (Task 3)
    // ----------------------------------------------------------
    PathStack robotPath;
    robotPath.push("forward", "Zone-A");
    robotPath.push("left",    "Aisle-2");
    robotPath.push("forward", "Shelf-3");
    robotPath.display();
    robotPath.displayForwardPath();

    // ----------------------------------------------------------
    // STEP 8: Robot completes task — return via reverse path (Task 3)
    // ----------------------------------------------------------
    robotPath.returnPath();
    // Mark the assigned robot available again after task completion
    if (firstOrder != nullptr) {
        robotQueue.markAvailable(1); // Robot 1 was assigned; free it up
    }

    // ----------------------------------------------------------
    // STEP 9: Mark order as completed (Task 1)
    // ----------------------------------------------------------
    Order* processedOrder = orderQueue.dequeue();
    if (processedOrder != nullptr) {
        orderQueue.markCompleted(processedOrder);
    }
    orderQueue.displayCompleted();
    orderQueue.displayPending();

    cout << "\n========================================" << endl;
    cout << "  System simulation complete.           " << endl;
    cout << "========================================" << endl;

    return 0;
}

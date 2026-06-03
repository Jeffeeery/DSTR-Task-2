#include <iostream>
#include <string>
#include "OrderManagement/OrderManagement.hpp"
#include "RobotAssignment/RobotAssignment.hpp"
#include "RobotNavigation/RobotNavigation.hpp"
#include "ItemSearch/ItemSearch.hpp"
#include "WarehouseLayout/WarehouseLayout.hpp"

using namespace std;

// ---------------------------------------------------------------
// Interactive demo
// ---------------------------------------------------------------
void runInteractiveMenu(WarehouseTree& warehouse, ItemBST& itemDatabase,
                        OrderQueue& orderQueue, RobotCircularQueue& robotQueue) {
    int choice = -1;

    while (choice != 0) {
        cout << "\n========================================" << endl;
        cout << "        Interactive Demo Menu           " << endl;
        cout << "========================================" << endl;
        cout << "1. List Available Items" << endl;
        cout << "2. Process Next Order (Assign Robot + Navigate)" << endl;
        cout << "3. Display Pending Orders" << endl;
        cout << "4. Display Completed Orders" << endl;
        cout << "5. Display Robot Status" << endl;
        cout << "6. Display Warehouse Layout" << endl;
        cout << "0. Exit Interactive Mode" << endl;
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
        } else {
            cin.ignore();
        }

        if (choice == 1) {
            itemDatabase.displayAll();

        } else if (choice == 2) {
            Order* order = orderQueue.peek();
            if (order == nullptr) {
                cout << "[System] No pending orders to process." << endl;
                continue;
            }

            cout << "\n[System] Processing Order #" << order->orderId
                 << " - Item: " << order->itemName << endl;

            // Locate item in BST
            ItemNode* item = itemDatabase.searchByName(order->itemName);
            if (item == nullptr) {
                cout << "[ItemSearch] Item '" << order->itemName
                     << "' not in database. Cannot navigate." << endl;
                continue;
            }
            string itemLocation = item->location;
            cout << "[ItemSearch] Item found at: " << itemLocation << endl;

            // Get root-to-shelf path from warehouse tree
            string path[20];
            int pathLen = warehouse.getPathToLocation(itemLocation, path, 20);
            if (pathLen == 0) {
                cout << "[System] Location '" << itemLocation
                     << "' not in warehouse layout." << endl;
                continue;
            }

            cout << "\n[Route] Path to " << itemLocation << ": ";
            for (int i = 0; i < pathLen; i++) {
                cout << path[i];
                if (i < pathLen - 1) cout << " -> ";
            }
            cout << endl;

            // Assign next available robot
            Robot* assignedRobot = robotQueue.assignNext();
            if (assignedRobot == nullptr) {
                cout << "[System] No available robots. Cannot process order." << endl;
                continue;
            }
            cout << "[System] Order #" << order->orderId
                 << " assigned to Robot " << assignedRobot->robotId << endl;

            // Push navigation steps — directions follow depth in tree
            PathStack robotPath;
            string directions[] = { "forward", "left", "forward", "forward", "forward" };
            for (int i = 1; i < pathLen; i++) {
                string dir = (i - 1 < 5) ? directions[i - 1] : "forward";
                robotPath.push(dir, path[i]);
            }

            robotPath.display();
            robotPath.displayForwardPath();
            robotPath.returnPath();

            // Release robot then complete order
            robotQueue.markAvailable(assignedRobot->robotId);
            orderQueue.processNextOrder();

        } else if (choice == 3) {
            orderQueue.displayPending();

        } else if (choice == 4) {
            orderQueue.displayCompleted();

        } else if (choice == 5) {
            robotQueue.displayStatus();
            robotQueue.displayAssignments();

        } else if (choice == 6) {
            warehouse.displayLayout();

        } else if (choice != 0) {
            cout << "Invalid choice. Enter 0-6." << endl;
        }
    }

    cout << "[System] Exiting interactive demo." << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "  Warehouse Robot Navigation System     " << endl;
    cout << "========================================" << endl;

    WarehouseTree warehouse;
    warehouse.buildLayout();
    warehouse.displayLayout();
    warehouse.displayPreOrder();

    ItemBST itemDatabase;

    cout << "\n=== Inserting Items into Database ===" << endl;
    itemDatabase.insert(504, "Control Chip D", "Shelf-1");
    itemDatabase.insert(502, "Sensor Unit B", "Shelf-2");
    itemDatabase.insert(506, "Battery Pack C", "Shelf-3");
    itemDatabase.insert(501, "Motor Part A", "Shelf-4");
    itemDatabase.insert(503, "Packing Tape E", "Shelf-5");
    itemDatabase.insert(505, "Robot Wheel F", "Shelf-6");
    itemDatabase.insert(507, "Barcode Scanner G", "Shelf-7");
    itemDatabase.insert(508, "Safety Glove H", "Shelf-8");

    itemDatabase.displayAll();

    cout << "\n=== Search by ID ===" << endl;
    ItemNode* idResult = itemDatabase.searchById(502);

    if (idResult != nullptr) {
        cout << "[ItemSearch] Found by ID: "
             << idResult->itemId << " | "
             << idResult->itemName << " | "
             << idResult->location << endl;
    }

    cout << "\n=== Update Location ===" << endl;
    itemDatabase.updateLocation(501, "Shelf-3");

    cout << "\n=== Delete Item ===" << endl;
    itemDatabase.deleteItem(503);
    itemDatabase.displayAll();

    cout << "\n=== Search Deleted Item ===" << endl;
    ItemNode* deletedItem = itemDatabase.searchByName("Packing Tape E");

    if (deletedItem == nullptr) {
        cout << "[ItemSearch] Item not found: Packing Tape E" << endl;
    }

    cout << "\n=== New Order Simulation ===" << endl;
    OrderQueue orderQueue;
    orderQueue.enqueue(1001, "Motor Part A");
    orderQueue.enqueue(1002, "Sensor Unit B");
    orderQueue.enqueue(1003, "Battery Pack C");
    orderQueue.displayPending();
    cout << endl;

    RobotCircularQueue robotQueue;
    robotQueue.addRobot(1);
    robotQueue.addRobot(2);
    robotQueue.addRobot(3);
    robotQueue.addRobot(4);
    robotQueue.addRobot(5);

    robotQueue.markMaintenance(2);

    Order* firstOrder = orderQueue.peek();
    Robot* assignedRobot = nullptr;

    if (firstOrder != nullptr) {
        assignedRobot = robotQueue.assignNext();

        if (assignedRobot != nullptr) {
            cout << "[System] Order " << firstOrder->orderId
                 << " assigned to Robot "
                 << assignedRobot->robotId << endl;
        }
    }

    robotQueue.displayStatus();
    robotQueue.displayAssignments();

    string itemLocation = "";

    if (firstOrder != nullptr) {
        cout << "\n=== Item Search for Current Order ===" << endl;
        cout << "[System] Searching location for order item: "
             << firstOrder->itemName << endl;

        ItemNode* foundItem = itemDatabase.searchByName(firstOrder->itemName);

        if (foundItem != nullptr) {
            itemLocation = foundItem->location;

            cout << "[ItemSearch] Item found: "
                 << foundItem->itemId << " | "
                 << foundItem->itemName << " | Location: "
                 << itemLocation << endl;
        } 
        else {
            cout << "[ItemSearch] Item not found: "
                 << firstOrder->itemName << endl;
            cout << "[System] Cannot generate route because item location is unavailable." << endl;

            return 0;
        }
    }

    string path[20];
    int pathLen = warehouse.getPathToLocation(itemLocation, path, 20);

    if (pathLen == 0) {
        cout << "[System] Cannot generate route because warehouse location is invalid." << endl;


        return 0;
    }

    cout << "\n[Route] Path to " << itemLocation << ": ";

    for (int i = 0; i < pathLen; i++) {
        cout << path[i];

        if (i < pathLen - 1) {
            cout << " -> ";
        }
    }

    cout << endl;

    warehouse.displayRoute("Shelf-6", itemLocation);

    // === Obstacle Handling Demo (backtrack feature) ===
    cout << "\n=== Obstacle Handling Demo ===" << endl;
    if (pathLen >= 3) {
        // Find a sibling of path[2] under path[1] — use it as the wrong turn
        string wrongStep = "";
        LocationNode* parentNode = warehouse.findLocation(path[1]);
        if (parentNode != nullptr) {
            for (int i = 0; i < parentNode->childCount; i++) {
                if (parentNode->children[i]->name != path[2]) {
                    wrongStep = parentNode->children[i]->name;
                    break;
                }
            }
        }

        if (!wrongStep.empty()) {
            PathStack obstaclePath;
            cout << "[System] Robot attempts wrong turn: "
                 << path[1] << " -> " << wrongStep << " (incorrect)." << endl;
            obstaclePath.push("forward", path[1]);
            obstaclePath.push("right", wrongStep);
            obstaclePath.backtrack();
            cout << "[System] Obstacle cleared. Robot reroutes correctly to "
                 << path[2] << "." << endl;
            obstaclePath.push("left", path[2]);
            for (int i = 3; i < pathLen; i++) {
                obstaclePath.push("forward", path[i]);
            }
        } else {
            cout << "[System] No alternate path available for backtrack demo." << endl;
        }
    } else {
        cout << "[System] Path too short for backtrack demo." << endl;
    }

    PathStack robotPath;
    string directionMap[] = { "forward", "left", "forward", "forward" };

    for (int i = 1; i < pathLen; i++) {
        string direction = "forward";

        if (i - 1 < 4) {
            direction = directionMap[i - 1];
        }

        robotPath.push(direction, path[i]);
    }

    robotPath.display();
    robotPath.displayForwardPath();

    robotPath.returnPath();

    if (assignedRobot != nullptr) {
        robotQueue.markAvailable(assignedRobot->robotId);
    }

    if (firstOrder != nullptr) {
        orderQueue.processNextOrder();
        firstOrder = nullptr;
    }

    cout << "\n=== Final System Status ===" << endl;
    robotQueue.displayStatus();

    orderQueue.displayCompleted();
    orderQueue.displayPending();

    cout << "\n========================================" << endl;
    cout << "  System simulation complete.           " << endl;
    cout << "========================================" << endl;

    cout << "\n========================================" << endl;
    cout << "      Entering Interactive Mode         " << endl;
    cout << "  (Shared state from demo above)        " << endl;
    cout << "========================================" << endl;

    runInteractiveMenu(warehouse, itemDatabase, orderQueue, robotQueue);

    return 0;
}
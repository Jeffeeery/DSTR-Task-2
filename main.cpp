#include <iostream>
#include <string>
#include "OrderManagement/OrderManagement.hpp"
#include "RobotAssignment/RobotAssignment.hpp"
#include "RobotNavigation/RobotNavigation.hpp"
#include "ItemSearch/ItemSearch.hpp"
#include "WarehouseLayout/WarehouseLayout.hpp"

using namespace std;

// ---------------------------------------------------------------
// Interactive demo — shares all live data structures with main
// ---------------------------------------------------------------
void runInteractiveMenu(WarehouseTree& warehouse, ItemBST& itemDatabase,
                        OrderQueue& orderQueue, RobotCircularQueue& robotQueue) {
    int nextOrderId = 2001;
    int choice = -1;

    while (choice != 0) {
        cout << "\n========================================" << endl;
        cout << "        Interactive Demo Menu           " << endl;
        cout << "========================================" << endl;
        cout << "1. Add New Order" << endl;
        cout << "2. Add New Item to Database" << endl;
        cout << "3. Search Item (by ID or Name)" << endl;
        cout << "4. Process Next Order (Assign Robot + Navigate)" << endl;
        cout << "5. Display Pending Orders" << endl;
        cout << "6. Display Completed Orders" << endl;
        cout << "7. Display Robot Status" << endl;
        cout << "8. Display Warehouse Layout" << endl;
        cout << "0. Exit Interactive Mode" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string itemName;
            cout << "Enter item name: ";
            getline(cin, itemName);
            orderQueue.enqueue(nextOrderId++, itemName);

        } else if (choice == 2) {
            int itemId;
            string itemName, location;
            cout << "Enter item ID: ";
            cin >> itemId;
            cin.ignore();
            cout << "Enter item name: ";
            getline(cin, itemName);
            cout << "Enter location (e.g. Shelf-1 to Shelf-8): ";
            getline(cin, location);
            itemDatabase.insert(itemId, itemName, location);

        } else if (choice == 3) {
            cout << "Search by — 1) ID   2) Name: ";
            int searchChoice;
            cin >> searchChoice;
            cin.ignore();

            if (searchChoice == 1) {
                int id;
                cout << "Enter item ID: ";
                cin >> id;
                cin.ignore();
                ItemNode* result = itemDatabase.searchById(id);
                if (result != nullptr)
                    cout << "[ItemSearch] Found: " << result->itemId
                         << " | " << result->itemName
                         << " | " << result->location << endl;
                else
                    cout << "[ItemSearch] Item ID " << id << " not found." << endl;
            } else {
                string name;
                cout << "Enter item name: ";
                getline(cin, name);
                ItemNode* result = itemDatabase.searchByName(name);
                if (result != nullptr)
                    cout << "[ItemSearch] Found: " << result->itemId
                         << " | " << result->itemName
                         << " | " << result->location << endl;
                else
                    cout << "[ItemSearch] Item '" << name << "' not found." << endl;
            }

        } else if (choice == 4) {
            Order* order = orderQueue.peek();
            if (order == nullptr) {
                cout << "[System] No pending orders to process." << endl;
                continue;
            }

            cout << "\n[System] Processing Order #" << order->orderId
                 << " — Item: " << order->itemName << endl;

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

        } else if (choice == 5) {
            orderQueue.displayPending();

        } else if (choice == 6) {
            orderQueue.displayCompleted();

        } else if (choice == 7) {
            robotQueue.displayStatus();
            robotQueue.displayAssignments();

        } else if (choice == 8) {
            warehouse.displayLayout();

        } else if (choice != 0) {
            cout << "Invalid choice. Enter 0-8." << endl;
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

    OrderQueue orderQueue;
    orderQueue.enqueue(1001, "Motor Part A");
    orderQueue.enqueue(1002, "Sensor Unit B");
    orderQueue.enqueue(1003, "Battery Pack C");
    orderQueue.displayPending();

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

            delete firstOrder;
            firstOrder = nullptr;
            return 0;
        }
    }

    string path[20];
    int pathLen = warehouse.getPathToLocation(itemLocation, path, 20);

    if (pathLen == 0) {
        cout << "[System] Cannot generate route because warehouse location is invalid." << endl;

        if (firstOrder != nullptr) {
            delete firstOrder;
            firstOrder = nullptr;
        }

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
    cout << "[System] Robot attempts wrong turn: Zone-A -> Aisle-1 (incorrect aisle)." << endl;
    PathStack obstaclePath;
    obstaclePath.push("forward", "Zone-A");
    obstaclePath.push("right", "Aisle-1");
    obstaclePath.backtrack();
    cout << "[System] Obstacle cleared. Robot reroutes correctly to Aisle-2." << endl;
    obstaclePath.push("left", "Aisle-2");
    obstaclePath.push("forward", "Shelf-3");
    obstaclePath.displayForwardPath();

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
#include <iostream>
#include <string>
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

    return 0;
}
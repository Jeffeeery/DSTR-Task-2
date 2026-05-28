/*
 * Task 5 — Warehouse Layout & Navigation Module (Optional)
 * Member: [Your Name]
 * Student ID: [Your ID]
 * Data Structure: Tree (self-implemented, hierarchical multi-child nodes)
 *
 * Hierarchy: Warehouse --> Zones --> Aisles --> Shelves
 *
 * Responsibility:
 *   - Model physical warehouse structure as a tree
 *   - Define parent-child relationships between locations
 *   - Generate path from root to any target location
 *   - Support full pre-order traversal
 *   - Integrate with Task 3 (Robot Navigation) for path planning
 *
 * Why Tree?
 *   A warehouse has a natural hierarchy: one warehouse contains multiple
 *   zones, each zone has multiple aisles, each aisle has multiple shelves.
 *   A tree mirrors this exactly. Parent-pointer links let us trace any
 *   path back to the root to generate navigation routes.
 */

#ifndef WAREHOUSE_LAYOUT_HPP
#define WAREHOUSE_LAYOUT_HPP

#include <iostream>
#include <string>

#define INITIAL_CAPACITY 4  // initial children array size; doubles when full

using namespace std;

// Represents one location in the warehouse hierarchy (tree node)
struct LocationNode {
    string name;           // e.g., "Zone-A", "Aisle-1", "Shelf-3"
    string type;           // "warehouse", "zone", "aisle", "shelf"
    LocationNode** children;    // dynamic array of child pointers
    int childCount;
    int childCapacity;
    LocationNode* parent;       // back-link to parent (nullptr for root)

    LocationNode(std::string name, std::string type);
    ~LocationNode(); // frees children array only; child nodes freed by WarehouseTree

    void addChild(LocationNode* child);
};

// Self-implemented Tree — DO NOT use STL containers
class WarehouseTree {
private:
    LocationNode* root;

    void displayTree(LocationNode* node, int depth) const;
    LocationNode* findNode(LocationNode* node, std::string name) const;
    void destroyTree(LocationNode* node);
    void traversePreOrder(LocationNode* node) const;
    // Trace parent links from target to root, reverse into pathArr
    int buildPath(LocationNode* target, std::string* pathArr, int maxLen) const;

public:
    WarehouseTree();
    ~WarehouseTree();

    // Build the warehouse tree (call once at startup)
    void buildLayout();

    // Find a location node by name (nullptr if not found)
    LocationNode* findLocation(std::string name) const;

    // Fill pathArr with names from root to targetName
    // Returns path length (0 if not found)
    int getPathToLocation(std::string targetName, std::string* pathArr, int maxLen) const;

    // Print indented hierarchy
    void displayLayout() const;

    // Pre-order traversal of entire tree
    void displayPreOrder() const;

    // TODO: Add any additional helper methods
};

#endif // WAREHOUSE_LAYOUT_HPP

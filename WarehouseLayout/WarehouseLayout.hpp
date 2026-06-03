/*
 * Task 5 — Warehouse Layout & Navigation Module (Optional)
 * Member: Lee Wei Kee
 * Student ID: TP076249
 * Data Structure: Tree (self-implemented, hierarchical multi-child nodes)
 *
 * Hierarchy: Warehouse --> Zones --> Aisles --> Shelves
 */

#ifndef WAREHOUSE_LAYOUT_HPP
#define WAREHOUSE_LAYOUT_HPP

#include <iostream>
#include <string>

#define INITIAL_CAPACITY 4  // initial children array size; doubles when full
#define MAX_PATH_LEN 20

using namespace std;

// Represents one location in the warehouse hierarchy (tree node)
struct LocationNode {
    string name;           
    string type;    
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
    LocationNode* findNode(LocationNode* node, const string& name) const;
    void destroyTree(LocationNode* node);
    void traversePreOrder(LocationNode* node) const;
    // Trace parent links from target to root, reverse into pathArr
    int buildPath(LocationNode* target, std::string* pathArr, int maxLen) const;
    LocationNode* findLCA(LocationNode* a, LocationNode* b) const;
    int depthOf(LocationNode* node) const;

public:
    WarehouseTree();
    ~WarehouseTree();

    // Build the warehouse tree (call once at startup)
    void buildLayout();

    // Find a location node by name (nullptr if not found)
    LocationNode* findLocation(const string& name) const;

    // Fill pathArr with names from root to targetName
    // Returns path length (0 if not found)
    int getPathToLocation(const string& targetName, string* pathArr, int maxLen) const;

    // Print indented hierarchy
    void displayLayout() const;

    // Pre-order traversal of entire tree
    void displayPreOrder() const;
    int getPathBetweenLocations(const string& fromName, const string& toName, string* pathArr, int maxLen) const;
    void displayRoute(const string& fromName, const string& toName) const;
};

#endif 

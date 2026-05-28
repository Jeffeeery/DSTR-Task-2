/*
 * Task 5 — Warehouse Layout & Navigation Module Implementation
 * Member: [Your Name]
 * Student ID: [Your ID]
 * Data Structure: Tree (hierarchical, self-implemented)
 */

#include "WarehouseLayout.hpp"

using namespace std;

// ---------------------------------------------------------------
// LocationNode constructor
// ---------------------------------------------------------------
LocationNode::LocationNode(std::string n, std::string t) {
    // TODO: name = n, type = t
    // TODO: children = new LocationNode*[INITIAL_CAPACITY]
    // TODO: childCount = 0, childCapacity = INITIAL_CAPACITY, parent = nullptr
}

// ---------------------------------------------------------------
// LocationNode destructor — frees only the children pointer array
// (child nodes themselves are freed recursively by WarehouseTree::destroyTree)
// ---------------------------------------------------------------
LocationNode::~LocationNode() {
    // TODO: delete[] children
}

// ---------------------------------------------------------------
// addChild — attach a child location under this node
// ---------------------------------------------------------------
void LocationNode::addChild(LocationNode* child) {
    // TODO: If childCount == childCapacity:
    //         Allocate new array (double capacity)
    //         Copy existing pointers, delete old array, update capacity
    // TODO: children[childCount++] = child
    // TODO: child->parent = this
}

// ---------------------------------------------------------------
// WarehouseTree constructor / destructor
// ---------------------------------------------------------------
WarehouseTree::WarehouseTree() {
    // TODO: root = nullptr
}

WarehouseTree::~WarehouseTree() {
    // TODO: destroyTree(root)
}

void WarehouseTree::destroyTree(LocationNode* node) {
    // TODO: If nullptr, return
    // TODO: Recurse into each child: destroyTree(node->children[i])
    // TODO: delete node (its destructor frees the children array)
}

// ---------------------------------------------------------------
// buildLayout — construct the warehouse hierarchy
// ---------------------------------------------------------------
void WarehouseTree::buildLayout() {
    // TODO: Create root = new LocationNode("Warehouse", "warehouse")
    //
    // TODO: Build the following structure (expand as needed):
    //
    //   Warehouse
    //   +-- Zone-A
    //   |   +-- Aisle-1
    //   |   |   +-- Shelf-1
    //   |   |   +-- Shelf-2
    //   |   +-- Aisle-2
    //   |       +-- Shelf-3
    //   |       +-- Shelf-4
    //   +-- Zone-B
    //       +-- Aisle-3
    //       |   +-- Shelf-5
    //       |   +-- Shelf-6
    //       +-- Aisle-4
    //           +-- Shelf-7
    //
    // Example:
    //   LocationNode* zoneA = new LocationNode("Zone-A", "zone");
    //   root->addChild(zoneA);
    //   LocationNode* aisle1 = new LocationNode("Aisle-1", "aisle");
    //   zoneA->addChild(aisle1);
    //   aisle1->addChild(new LocationNode("Shelf-1", "shelf"));
    //   ... and so on
}

// ---------------------------------------------------------------
// findNode — pre-order recursive search by name
// ---------------------------------------------------------------
LocationNode* WarehouseTree::findNode(LocationNode* node, std::string name) const {
    // TODO: If nullptr, return nullptr
    // TODO: If node->name == name, return node
    // TODO: For each child, result = findNode(child, name); if result != nullptr return it
    // TODO: Return nullptr
    return nullptr;
}

LocationNode* WarehouseTree::findLocation(std::string name) const {
    // TODO: return findNode(root, name)
    return nullptr;
}

// ---------------------------------------------------------------
// buildPath — trace parent links from target to root, then reverse
// ---------------------------------------------------------------
int WarehouseTree::buildPath(LocationNode* target, std::string* pathArr, int maxLen) const {
    // TODO: Walk target->parent->parent... until nullptr, store names in temp array
    // TODO: Reverse temp array into pathArr (path goes root -> target)
    // TODO: Return number of locations in path
    return 0;
}

int WarehouseTree::getPathToLocation(std::string targetName, std::string* pathArr, int maxLen) const {
    // TODO: target = findLocation(targetName)
    // TODO: If nullptr, print "Location not found" and return 0
    // TODO: return buildPath(target, pathArr, maxLen)
    return 0;
}

// ---------------------------------------------------------------
// displayTree — indented hierarchy
// ---------------------------------------------------------------
void WarehouseTree::displayTree(LocationNode* node, int depth) const {
    // TODO: If nullptr, return
    // TODO: Print (depth * 4) spaces, then node->name (type)
    // TODO: Recurse each child with depth + 1
}

void WarehouseTree::displayLayout() const {
    // TODO: Print header "=== Warehouse Layout ==="
    // TODO: If root nullptr, print "Layout not built yet."
    // TODO: Otherwise call displayTree(root, 0)
}

void WarehouseTree::traversePreOrder(LocationNode* node) const {
    // TODO: If nullptr, return
    // TODO: Print node->name
    // TODO: Recurse each child
}

void WarehouseTree::displayPreOrder() const {
    // TODO: Print header "=== Pre-Order Traversal ==="
    // TODO: Call traversePreOrder(root)
}

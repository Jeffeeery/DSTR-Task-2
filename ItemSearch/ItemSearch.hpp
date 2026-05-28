/*
 * Task 4 — Item Search & Management Module (Optional)
 * Member: [Your Name]
 * Student ID: [Your ID]
 * Data Structure: Binary Search Tree (BST, self-implemented)
 *
 * Responsibility:
 *   - Store item details: ID, name, warehouse location
 *   - Insert new items; search by ID or name
 *   - Update and delete item records
 *   - Display all items in sorted order (in-order traversal)
 *
 * Why BST?
 *   Items have a unique integer ID. BST ordered by ID gives O(log n)
 *   search, insert, and delete — far faster than a linear scan,
 *   especially as the warehouse inventory grows.
 */

#ifndef ITEM_SEARCH_HPP
#define ITEM_SEARCH_HPP

#include <iostream>
#include <string>

using namespace std;

// Represents a warehouse item stored as a BST node
struct ItemNode {
    int itemId;             // unique ID — BST is ordered by this
    string itemName;
    string location;   // e.g., "Zone-A/Aisle-2/Shelf-3"
    ItemNode* left;         // left child  (smaller ID)
    ItemNode* right;        // right child (larger ID)

    ItemNode(int id, string name, string loc);
};

// Self-implemented BST — DO NOT use STL containers
class ItemBST {
private:
    ItemNode* root;

    // Private recursive helpers
    ItemNode* insertHelper(ItemNode* node, int id, string name, string loc);
    ItemNode* searchHelper(ItemNode* node, int id) const;
    ItemNode* deleteHelper(ItemNode* node, int id);
    ItemNode* findMin(ItemNode* node) const;
    void inOrderHelper(ItemNode* node) const;
    ItemNode* searchByNameHelper(ItemNode* node, string name) const;
    void destroyTree(ItemNode* node);

public:
    ItemBST();
    ~ItemBST();

    void insert(int itemId, string itemName, string location);
    ItemNode* searchById(int itemId) const;              // O(log n)
    ItemNode* searchByName(string itemName) const;  // O(n) linear scan
    void deleteItem(int itemId);
    void updateLocation(int itemId, string newLocation);
    void displayAll() const; // in-order: sorted by ID

    // TODO: Add any additional helper methods
};

#endif // ITEM_SEARCH_HPP

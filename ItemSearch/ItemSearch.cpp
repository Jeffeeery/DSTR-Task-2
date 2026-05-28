/*
 * Task 4 — Item Search & Management Module Implementation
 * Member: [Your Name]
 * Student ID: [Your ID]
 * Data Structure: Binary Search Tree (BST)
 */

#include "ItemSearch.hpp"

using namespace std;

ItemNode::ItemNode(int id, std::string name, std::string loc) {
    // TODO: Initialize itemId, itemName, location, left = nullptr, right = nullptr
}

ItemBST::ItemBST() {
    // TODO: root = nullptr
}

ItemBST::~ItemBST() {
    // TODO: destroyTree(root)
}

void ItemBST::destroyTree(ItemNode* node) {
    // TODO: Post-order delete: left subtree, right subtree, then node
}

// ---------------------------------------------------------------
// insertHelper — recursive BST insert
// ---------------------------------------------------------------
ItemNode* ItemBST::insertHelper(ItemNode* node, int id, std::string name, std::string loc) {
    // TODO: If node == nullptr, return new ItemNode(id, name, loc)
    // TODO: If id < node->itemId: node->left  = insertHelper(node->left,  id, name, loc)
    // TODO: If id > node->itemId: node->right = insertHelper(node->right, id, name, loc)
    // TODO: If id == node->itemId: overwrite name and location (duplicate handling)
    // TODO: Return node
    return nullptr;
}

void ItemBST::insert(int itemId, std::string itemName, std::string location) {
    // TODO: root = insertHelper(root, itemId, itemName, location)
    // TODO: Print confirmation
}

// ---------------------------------------------------------------
// searchHelper — recursive BST search by ID
// ---------------------------------------------------------------
ItemNode* ItemBST::searchHelper(ItemNode* node, int id) const {
    // TODO: If nullptr or match, return node
    // TODO: Recurse left if id < node->itemId, else right
    return nullptr;
}

ItemNode* ItemBST::searchById(int itemId) const {
    // TODO: return searchHelper(root, itemId)
    return nullptr;
}

// ---------------------------------------------------------------
// searchByNameHelper — in-order traversal, match by name
// ---------------------------------------------------------------
ItemNode* ItemBST::searchByNameHelper(ItemNode* node, std::string name) const {
    // TODO: If nullptr, return nullptr
    // TODO: Check left subtree first
    // TODO: If node->itemName == name, return node
    // TODO: Check right subtree
    return nullptr;
}

ItemNode* ItemBST::searchByName(std::string itemName) const {
    // TODO: return searchByNameHelper(root, itemName)
    return nullptr;
}

ItemNode* ItemBST::findMin(ItemNode* node) const {
    // TODO: Traverse left until node->left == nullptr, return that node
    return nullptr;
}

// ---------------------------------------------------------------
// deleteHelper — recursive BST deletion (3 cases)
// ---------------------------------------------------------------
ItemNode* ItemBST::deleteHelper(ItemNode* node, int id) {
    // TODO: If nullptr, print "Item not found" and return nullptr
    // TODO: Recurse left/right to find node
    // TODO: Case 1 — leaf: delete, return nullptr
    // TODO: Case 2 — one child: replace with child, delete node
    // TODO: Case 3 — two children:
    //         successor = findMin(node->right)
    //         copy successor data into node
    //         node->right = deleteHelper(node->right, successor->itemId)
    // TODO: Return node
    return nullptr;
}

void ItemBST::deleteItem(int itemId) {
    // TODO: root = deleteHelper(root, itemId)
}

void ItemBST::updateLocation(int itemId, std::string newLocation) {
    // TODO: node = searchById(itemId)
    // TODO: If found, update node->location and print confirmation
    // TODO: If not found, print error
}

void ItemBST::inOrderHelper(ItemNode* node) const {
    // TODO: Recurse left, print node (ID | name | location), recurse right
}

void ItemBST::displayAll() const {
    // TODO: Print header "=== Item Database (sorted by ID) ==="
    // TODO: If empty, print "No items in database."
    // TODO: Otherwise call inOrderHelper(root)
}

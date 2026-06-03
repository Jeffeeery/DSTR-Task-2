/*
 * Task 5 — Warehouse Layout & Navigation Module Implementation
 * Member: Lee Wei Kee
 * Student ID: TP076249
 * Data Structure: Tree (hierarchical, self-implemented)
 */

#include "WarehouseLayout.hpp"

using namespace std;

// LocationNode constructor
LocationNode::LocationNode(std::string n, std::string t) {
    name = n;
    type = t;
    children = new LocationNode*[INITIAL_CAPACITY];
    childCount = 0;
    childCapacity = INITIAL_CAPACITY;
    parent = nullptr;
}

// LocationNode destructor — frees only the children pointer array
// (child nodes themselves are freed recursively by WarehouseTree::destroyTree)
LocationNode::~LocationNode() {
    delete[] children;
}

// addChild — attach a child location under this node
void LocationNode::addChild(LocationNode* child) {
    if (childCount == childCapacity) {
        int newCapacity = childCapacity * 2;
        LocationNode** newArr = new LocationNode*[newCapacity];
        for (int i = 0; i < childCount; i++) {
            newArr[i] = children[i];
        }
        delete[] children;
        children = newArr;
        childCapacity = newCapacity;
    }
    children[childCount++] = child;
    child->parent = this;
}

// WarehouseTree constructor / destructor
WarehouseTree::WarehouseTree() {
    root = nullptr;
}

WarehouseTree::~WarehouseTree() {
    destroyTree(root);
}

void WarehouseTree::destroyTree(LocationNode* node) {
    if (node == nullptr) return;
    for (int i = 0; i < node->childCount; i++) {
        destroyTree(node->children[i]);
    }
    delete node;
}

int WarehouseTree::depthOf(LocationNode* node) const {
    int depth = 0;
    while (node->parent != nullptr) {
        node = node->parent;
        depth++;
    }
    return depth;
}

LocationNode* WarehouseTree::findLCA(LocationNode* a, LocationNode* b) const {
    if (a == nullptr || b == nullptr) return nullptr;

    int da = depthOf(a);
    int db = depthOf(b);

    while (da > db) { a = a->parent; da--; }
    while (db > da) { b = b->parent; db--; }

    while (a != b) {
        a = a->parent;
        b = b->parent;
    }
    return a;
}

int WarehouseTree::getPathBetweenLocations(const string& fromName,
                                            const string& toName,
                                            string* pathArr, int maxLen) const {
    LocationNode* fromNode = findLocation(fromName);
    LocationNode* toNode   = findLocation(toName);

    if (fromNode == nullptr) {
        cout << "[WarehouseLayout] Source location not found: " << fromName << endl;
        return 0;
    }
    if (toNode == nullptr) {
        cout << "[WarehouseLayout] Destination location not found: " << toName << endl;
        return 0;
    }

    LocationNode* lca = findLCA(fromNode, toNode);

    string fromPath[MAX_PATH_LEN];
    string toPath[MAX_PATH_LEN];
    int fromLen = buildPath(fromNode, fromPath, MAX_PATH_LEN);
    int toLen   = buildPath(toNode,   toPath,   MAX_PATH_LEN);

    int lcaIdxFrom = -1, lcaIdxTo = -1;
    for (int i = 0; i < fromLen; i++) {
        if (fromPath[i] == lca->name) { lcaIdxFrom = i; break; }
    }
    for (int i = 0; i < toLen; i++) {
        if (toPath[i] == lca->name) { lcaIdxTo = i; break; }
    }

    int idx = 0;
    for (int i = fromLen - 1; i >= lcaIdxFrom && idx < maxLen; i--) {
        pathArr[idx++] = fromPath[i];
    }
    for (int i = lcaIdxTo + 1; i < toLen && idx < maxLen; i++) {
        pathArr[idx++] = toPath[i];
    }
    return idx;
}

void WarehouseTree::displayRoute(const string& fromName, const string& toName) const {
    string path[MAX_PATH_LEN];
    int len = getPathBetweenLocations(fromName, toName, path, MAX_PATH_LEN);

    if (len == 0) return;

    cout << "\n=== Route: " << fromName << " --> " << toName << " ===" << endl;
    for (int i = 0; i < len; i++) {
        cout << "  Step " << (i + 1) << ": " << path[i];
        if (i < len - 1) cout << " -> " << path[i + 1];
        cout << endl;
    }
    cout << "Total steps: " << (len - 1) << endl;
}

// buildLayout — construct the warehouse hierarchy
void WarehouseTree::buildLayout() {
    root = new LocationNode("Warehouse", "warehouse");

    // --- Zone A ---
    LocationNode* zoneA = new LocationNode("Zone-A", "zone");
    root->addChild(zoneA);

    LocationNode* aisle1 = new LocationNode("Aisle-1", "aisle");
    zoneA->addChild(aisle1);
    aisle1->addChild(new LocationNode("Shelf-1", "shelf"));
    aisle1->addChild(new LocationNode("Shelf-2", "shelf"));

    LocationNode* aisle2 = new LocationNode("Aisle-2", "aisle");
    zoneA->addChild(aisle2);
    aisle2->addChild(new LocationNode("Shelf-3", "shelf"));
    aisle2->addChild(new LocationNode("Shelf-4", "shelf"));

    // --- Zone B ---
    LocationNode* zoneB = new LocationNode("Zone-B", "zone");
    root->addChild(zoneB);

    LocationNode* aisle3 = new LocationNode("Aisle-3", "aisle");
    zoneB->addChild(aisle3);
    aisle3->addChild(new LocationNode("Shelf-5", "shelf"));
    aisle3->addChild(new LocationNode("Shelf-6", "shelf"));

    LocationNode* aisle4 = new LocationNode("Aisle-4", "aisle");
    zoneB->addChild(aisle4);
    aisle4->addChild(new LocationNode("Shelf-7", "shelf"));
    aisle4->addChild(new LocationNode("Shelf-8", "shelf"));
}

// findNode — pre-order recursive search by name
LocationNode* WarehouseTree::findNode(LocationNode* node, const string& name) const {
    if (node == nullptr) return nullptr;
    if (node->name == name) return node;
    for (int i = 0; i < node->childCount; i++) {
        LocationNode* result = findNode(node->children[i], name);
        if (result != nullptr) return result;
    }
    return nullptr;
}

LocationNode* WarehouseTree::findLocation(const string& name) const {
    return findNode(root, name);
}

// buildPath — trace parent links from target to root, then reverse
int WarehouseTree::buildPath(LocationNode* target, std::string* pathArr, int maxLen) const {
    string temp[MAX_PATH_LEN];
    int len = 0;
    LocationNode* current = target;
    while (current != nullptr && len < MAX_PATH_LEN) {
        temp[len++] = current->name;
        current = current->parent;
    }
    // Reverse into pathArr so order is root -> target
    // copyLen respects caller's maxLen to avoid writing past their array
    int copyLen = (len < maxLen) ? len : maxLen;
    for (int i = 0; i < copyLen; i++) {
        pathArr[i] = temp[len - 1 - i];
    }
    return copyLen;
}

int WarehouseTree::getPathToLocation(const string& targetName, string* pathArr, int maxLen) const {
    LocationNode* target = findLocation(targetName);
    if (target == nullptr) {
        cout << "Location not found: " << targetName << endl;
        return 0;
    }
    return buildPath(target, pathArr, maxLen);
}

// displayTree — indented hierarchy
void WarehouseTree::displayTree(LocationNode* node, int depth) const {
    if (node == nullptr) return;
    for (int i = 0; i < depth * 4; i++) cout << " ";
    cout << node->name << " (" << node->type << ")" << endl;
    for (int i = 0; i < node->childCount; i++) {
        displayTree(node->children[i], depth + 1);
    }
}

void WarehouseTree::displayLayout() const {
    cout << "\n=== Warehouse Layout ===" << endl;
    if (root == nullptr) {
        cout << "Layout not built yet." << endl;
        return;
    }
    displayTree(root, 0);
}

void WarehouseTree::traversePreOrder(LocationNode* node) const {
    if (node == nullptr) return;
    cout << node->name << endl;
    for (int i = 0; i < node->childCount; i++) {
        traversePreOrder(node->children[i]);
    }
}

void WarehouseTree::displayPreOrder() const {
    cout << "\n=== Pre-Order Traversal ===" << endl;
    traversePreOrder(root);
}

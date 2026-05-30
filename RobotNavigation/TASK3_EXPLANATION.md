# Task 3 — Robot Navigation & Path Tracking Module

## Data Structure Used
**Stack (self-implemented, LIFO — linked-list based)**

The return journey is the exact reverse of the forward path.
A stack's LIFO property pops steps in reverse order naturally — no extra computation needed.

---

## Task Requirement → Function Mapping

| Task Requirement | Function | What It Does |
|---|---|---|
| Record each movement step | `push()` | Creates new `Step` node, links at head of list, prints confirmation |
| Store full path start → destination | `PathStack` (the stack itself) | Linked list of `Step` nodes; each push grows the path |
| Display forward path | `displayForwardPath()` | Recurses to bottom node first, prints on the way back up → chronological order |
| Simulate step-by-step movement log | `display()` | Traverses top → bottom, prints current stack state |
| Reverse path step-by-step after task | `returnPath()` | Reads top direction, flips it via `reverseDirection()`, then pops — LIFO gives reverse order naturally |
| Handle obstacles / incorrect paths | `backtrack()` | Pops one step = undo last move |
| Free memory on exit | `~PathStack()` | While loop calls `pop()` until stack is empty |

---

## Data Flow — One Full Trip

```
push("forward", "Zone-A")   →  stack: [Zone-A]
push("left",    "Aisle-2")  →  stack: [Aisle-2] → [Zone-A]
push("forward", "Shelf-3")  →  stack: [Shelf-3] → [Aisle-2] → [Zone-A]

display()            → top-to-bottom:  Shelf-3, Aisle-2, Zone-A
displayForwardPath() → chronological:  Zone-A,  Aisle-2, Shelf-3

returnPath()         → pops LIFO:
                          backward  ←  Shelf-3
                          right     ←  Aisle-2
                          backward  ←  Zone-A
                          (stack empty = robot back at start)
```

---

## Helper Functions

| Function | Role |
|---|---|
| `displayForwardRecursive()` | Private. Recurses to bottom node, prints on unwind — uses call stack as reversal mechanism, no array needed |
| `reverseDirection()` | Pure mapping: forward ↔ backward, left ↔ right |
| `peek()` | Returns top node pointer without removing it |
| `isEmpty()` | Returns true if `top == nullptr` |
| `getSize()` | Returns current number of steps in stack |
| `pop()` | Core workhorse — handles underflow check, prints confirmation, deletes node. Used by `returnPath()`, `backtrack()`, and `~PathStack()` |

---

## Why Not Array-Based Stack?

A linked-list stack was chosen over array-based because:
- No fixed size limit — path length is unpredictable in a real warehouse
- No need to pre-allocate memory
- Each node is allocated exactly when needed and freed immediately when popped

---

## Lecturer's Coding Style Compliance

| Rule | Status |
|---|---|
| `using namespace std;` | ✅ |
| `struct` outside class, explicit `private:` / `public:` | ✅ |
| Linked-list: `top = nullptr`, push/pop at head | ✅ |
| Underflow check prints `"Stack Underflow. Cannot pop."` | ✅ |
| Confirmation message in both `push()` and `pop()` | ✅ |
| `void display()` with exact header `"\nStack contents (Top to Bottom):"` | ✅ |
| Concise `++` / `--` operators used | ✅ |

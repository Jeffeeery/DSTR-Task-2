# DSTR Task 2 — Warehouse Robot Navigation System

**CT077-3-2-DSTR | Lab Evaluation Work #2 | 30 Marks**  
Working Duration: Week 10 – Week 14

---

## Overview

A warehouse robot navigation system built in **C++** using fundamental data structures.  
The system handles order management, robot assignment, navigation, item search, and warehouse layout — all integrated into **one single prototype**.

### System Workflow

1. A new order is received → **Order Management (Queue)**
2. A robot is assigned to the task → **Robot Assignment (Circular Queue)**
3. The system identifies the item location → **Item Search (BST)**
4. A route is generated → **Warehouse Layout (Tree)**
5. The robot moves step-by-step → **Robot Navigation (Stack)**
6. After completing the task, the robot returns via reverse path → **Robot Navigation (Stack — pop)**

---

## Team Modules

| Task | Module | Data Structure | Member |
|------|--------|----------------|--------|
| 1 | Order Management | Queue | Lai Kah Fon (TP077207) |
| 2 | Robot Assignment | Circular Queue | Ban Cong Yin Brosnan (TP076560) |
| 3 | Robot Navigation & Path Tracking | Stack | EEE |
| 4 | Item Search & Management *(Optional)* | BST | Ng Wan Teng (TP076289) |
| 5 | Warehouse Layout & Navigation *(Optional)* | Tree | Lee Wei Kee (TP076249) |

---

## Module Details

### Task 1 — Order Management (`OrderManagement/`)
EV
- Accept and record incoming customer orders
- Process orders sequentially — **first in, first out (FIFO)**
- Remove orders once assigned to a robot
- Display pending and completed orders
- Handle edge cases: empty queue, overflow

**Data Structure:** Self-implemented Queue (linked-list based)  
**Output:** Pending order list, current order being processed, completed order history

---

### Task 2 — Robot Assignment (`RobotAssignment/`)
BAN
- Maintain robot list with status: `available` / `busy` / `maintenance`
- Assign tasks in **continuous rotation** — no cycle restart
- Skip unavailable or under-maintenance robots
- Track task count per robot

**Data Structure:** Self-implemented Circular Queue  
**Output:** Assignment list, current robot per task, robot status overview

---

### Task 3 — Robot Navigation & Path Tracking (`RobotNavigation/`)
EEE
- Record each movement step: `forward`, `left`, `right`, `backward`
- Store the full path from start to destination
- **Reverse path** step-by-step for the return journey (pop stack)
- Handle obstacles via backtracking (pop last step)
- Simulate robot movement via step-by-step logs

**Data Structure:** Self-implemented Stack (LIFO)  
**Output:** Forward movement path, reverse return path, complete navigation log

---

### Task 4 — Item Search & Management (`ItemSearch/`) *(Optional)*
WT
- Store item details: ID, name, warehouse location
- Insert, search (by ID or name), update, delete records
- Display items in sorted order via **in-order traversal**

**Data Structure:** Self-implemented Binary Search Tree (BST), ordered by Item ID  
**Output:** Search results, updated item database, sorted item listing

---

### Task 5 — Warehouse Layout & Navigation (`WarehouseLayout/`) *(Optional)*
WK
- Model warehouse hierarchy: `Warehouse → Zones → Aisles → Shelves`
- Define connections between locations
- Generate routes from one point to another
- Support full traversal (pre-order)
- Integrates with Task 3 for path planning

**Data Structure:** Self-implemented Tree (hierarchical, multi-child nodes)  
**Output:** Visual/textual warehouse layout, path between locations, traversal results

---

## How to Compile & Run

```bash
g++ main.cpp OrderManagement/OrderManagement.cpp RobotAssignment/RobotAssignment.cpp RobotNavigation/RobotNavigation.cpp ItemSearch/ItemSearch.cpp WarehouseLayout/WarehouseLayout.cpp -o main.exe
```

```bash
.\main.exe
```

---

## Rules

| Rule | Detail |
|------|--------|
| Language | **C++ only** |
| Prototype | **ONE** combined system |
| STL containers | **NOT allowed** — `<list>`, `<vector>`, `<queue>`, `<stack>`, etc. All containers must be **self-implemented** |
| Per member | At least **1 data structure + algorithm**, entirely self-coded |
| Code quality | Proper indentation, meaningful identifier names, comments |

---

## Submission

| Item | Detail |
|------|--------|
| Files | Upload `.cpp`, `.hpp`, CSV/text files **individually** to Moodle — **NOT as ZIP** |
| Deadline | **Monday Week 14, 5:00 PM** |
| ZIP name (backup) | `<GroupNo>_<leaderID>_<member1ID>_<member2ID>_<member3ID>.zip` |
| Live presentation | Week 14 Tue – Week 16 Fri, **30 minutes** per team |
| Miss presentation | **0 marks**, no exceptions |

---

## Marking Criteria (30 Marks — Individual)

| Component | Marks |
|-----------|-------|
| Problem-solving ability, data structure use, code quality, feature implementation, creativity | 15 |
| Live Q&A: justify data structure choice, explain code, present individual contribution clearly | 15 |

---

## AI Usage Policy

- AI tools **cannot** generate code, algorithms, or program logic for this assignment
- AI is **only permitted** for: understanding concepts, identifying keywords, clarifying error messages
- All submitted code must be **your own original work**
- You must **explain and justify every part** of your code during live Q&A
- AI-generated code (modified or not) = **academic integrity violation**
- Penalty: **0 marks** or disciplinary action

---

## Project Structure

```
DSTR-Task-2/
├── main.cpp                        # System entry point — integrates all modules
├── OrderManagement/
│   ├── OrderManagement.hpp         # Task 1: Queue declaration
│   └── OrderManagement.cpp         # Task 1: Queue implementation
├── RobotAssignment/
│   ├── RobotAssignment.hpp         # Task 2: Circular Queue declaration
│   └── RobotAssignment.cpp         # Task 2: Circular Queue implementation
├── RobotNavigation/
│   ├── RobotNavigation.hpp         # Task 3: Stack declaration
│   └── RobotNavigation.cpp         # Task 3: Stack implementation
├── ItemSearch/
│   ├── ItemSearch.hpp              # Task 4: BST declaration
│   └── ItemSearch.cpp              # Task 4: BST implementation
└── WarehouseLayout/
    ├── WarehouseLayout.hpp         # Task 5: Tree declaration
    └── WarehouseLayout.cpp         # Task 5: Tree implementation
```

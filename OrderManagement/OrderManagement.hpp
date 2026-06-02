
#ifndef ORDER_MANAGEMENT_HPP
#define ORDER_MANAGEMENT_HPP

#include <iostream>
#include <string>

struct Order {
    int orderId;
    std::string itemName;
    std::string status;   
    Order* next;          

    Order(int id, std::string item);
   
};

class OrderQueue {
private:
    Order* front;       
    Order* rear;        
    int size;           
    int maxSize;        
    Order* completedHead;   

    Order* dequeue();
    void markCompleted(Order* order);

public:
    OrderQueue(int maxCapacity = 20);
    ~OrderQueue();

    void enqueue(int orderId, std::string itemName);

    void processNextOrder();

    Order* peek() const;

    bool isEmpty() const;
    bool isFull() const;
    int getSize() const;

    void displayPending() const;

    void displayCompleted() const;

    
};

#endif 
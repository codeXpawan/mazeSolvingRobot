#ifndef STACK_H
#define STACK_H

// Define the default size for the stack
#define MAX_STACK_SIZE 100

class Stack {
private:
    char items[MAX_STACK_SIZE]; // Array to store stack elements
    int top; // Points to the top of the stack

public:
    Stack(); // Constructor to initialize the stack

    bool isEmpty(); // Check if the stack is empty
    bool isFull(); // Check if the stack is full
    void push(char item); // Push an element onto the stack
    char pop(); // Pop an element from the stack
    char peek(); // Peek at the top element of the stack
    int size(); // Get the current size of the stack
    void clear(); // Clear the stack
};

#endif

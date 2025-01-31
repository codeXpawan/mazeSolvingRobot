#include "Stack.h"

// Constructor: Initializes the stack
Stack::Stack() {
    top = -1; // Stack starts as empty
}

// Check if the stack is empty
bool Stack::isEmpty() {
    return top == -1;
}

// Check if the stack is full
bool Stack::isFull() {
    return top == MAX_STACK_SIZE - 1;
}

// Push an element onto the stack
void Stack::push(char item) {
    if (isFull()) {
        // Handle stack overflow
        return;
    }
    items[++top] = item; // Increment top and add item
}

// Pop an element from the stack
char Stack::pop() {
    if (isEmpty()) {
        // Handle stack underflow
        return '\0'; // Return null character if stack is empty
    }
    return items[top--]; // Return top item and decrement top
}

// Peek at the top element of the stack
char Stack::peek() {
    if (isEmpty()) {
        // Handle empty stack
        return '\0';
    }
    return items[top];
}

// Get the current size of the stack
int Stack::size() {
    return top + 1;
}

// Clear the stack
void Stack::clear() {
    top = -1; // Reset top to indicate empty stack
}

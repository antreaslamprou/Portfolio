#pragma once

//Include library and namespace
#include <iostream>
using std::cout;

//Create a structure (Stack) of general type
template <typename T>
struct Stack {

    T _data[MAX_SIZE]; //Sets max size of the Stack
    unsigned int _top = 0; //Create the top index

    //Checks if Stack is empty
    bool isEmpty() {
        return _top == 0;
    }

    //Checks if Stack is full
    bool isFull() {
        return _top == MAX_SIZE;
    }

    //Adds a new element to the top of the Stack
    void push(T newVal) {
        if (!isFull()) {
            _data[_top++] = newVal;
        }
    }

    //Deletes the top element of the Stack
    void pop() {
        if (!isEmpty()) {
            _top--;
        }
    }

    //Returns the top element of the Stack
    T top() {
        if (!isEmpty()) {
            return _data[_top - 1];
        }
    }

    //Outputs the Stack to the console
    void print() {
        if (!isEmpty()) {
            cout << "Printing stack from the top\n";
            for (int i = _top - 1; i >= 0; i--) {
                cout << _data[i] << "\n";
            }
            cout << "-----------\n\n";
        }
        else cout << "Stack is empty\n\n";
    }

};
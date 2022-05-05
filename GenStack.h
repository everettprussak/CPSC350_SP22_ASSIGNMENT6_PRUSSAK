#ifndef GENSTACK_H
#define GENSTACK_H
#include <iostream>
#include "rollback.h"

using namespace std;

/*
Basic stack that is used only for the Rollback feature.
*/

template <class T>
class GenStack{
  public:
    GenStack(); //default
    GenStack(int maxSize); //overloaded constructor
    ~GenStack();  //destructor

    //core functions
    void push(T data);
    T pop();
    T peek(); //aka top();

    //aux functions
    bool isEmpty();
    bool isFull();
    int getSize();

  private:
    T *myArray;
    int top;
    int mSize;
};


#endif

template <class T>
GenStack<T>::GenStack(){
  mSize = 64;
  top = -1;
  myArray = new T[mSize];
}

template <class T>
GenStack<T>::GenStack(int maxSize){
  mSize = maxSize;
  top = -1;
  myArray = new T[mSize];
}

template <class T>
GenStack<T>::~GenStack(){
  delete[] myArray;
}

template <class T>
void GenStack<T>::push(T data){
  //check if stack is full
  if(isFull()){
    throw runtime_error("Stack is full");
  }

  top++;
  myArray[top] = data;

}

template <class T>
T GenStack<T>::pop(){
  //make sure stack is not empty before proceeding

  if(isEmpty()){
    throw runtime_error("stack is empty");
  }

  T temp = myArray[top];
  top--;
  return temp; //myArray[top--] also works here instead of this line and two above
}

template <class T>
T GenStack<T>::peek(){
  //make sure the stack is not empty before proceeding

  if(isEmpty()){
    throw runtime_error("stack is empty");
  }

  return myArray[top];
}

template <class T>
bool GenStack<T>::isEmpty(){
  return (top == -1);  //returns true if empty
}

template <class T>
bool GenStack<T>::isFull(){
  return (top == mSize-1); //if they are the same, we are full
}

template <class T>
int GenStack<T>::getSize(){
  return top + 1; //represents the index of an array
}

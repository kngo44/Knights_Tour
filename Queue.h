#pragma once
#include <iostream>
using namespace std;

struct node{
    int row, col;
    node* next;
};


class Queue{
public:
    Queue();
    void Push(int row, int col);
    void Pop();
    node* Peek();
    bool IsEmpty();

private:
    node* head;
    node* tail;
};

Queue::Queue(){
    head = nullptr;
    tail = nullptr;
}

void Queue::Push(int row, int col){
    node* temp = new node;
    temp->row = row;
    temp->col = col;
    temp->next = nullptr;
    if(IsEmpty()){
        head = temp;
    }
    else {
        tail->next = temp;
    }
    tail = temp;
}


void Queue::Pop(){
    if(head == nullptr){
        return;
    }

    if(head == tail){
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }
    node* temp = head;
    head = head->next;
    delete temp;
}

node* Queue::Peek(){
  if(!IsEmpty()){
    return head;
  }
  return nullptr;
}

bool Queue::IsEmpty(){
    return head == nullptr && tail == nullptr;
}



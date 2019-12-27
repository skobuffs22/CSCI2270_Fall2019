#include <iostream>

struct Node{
    int key;
    Node *next;
};

class LinkedList
{
private:
   Node *head;

public:
    LinkedList();
    bool lengthIsEven ();

};

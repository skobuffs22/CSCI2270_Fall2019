#include <iostream>
#include "QueueLL.hpp"

using namespace std;

QueueLL::QueueLL()
{
    queueFront = nullptr;
    queueEnd = nullptr;
}

QueueLL::~QueueLL()
{
    while( !isEmpty() )
        dequeue();
}

bool QueueLL::isEmpty()
{
    /*if(queueFront == nullptr || queueEnd == nullptr)
        return true;
    return false;*/
    return (!queueFront || !queueEnd);
}

// TODO
void QueueLL::enqueue(int key)
{
    Node *nn = new Node;
    nn->key = key;
    nn ->next = nullptr;
    if(isEmpty())
    {
      queueFront = nn;
      queueEnd = nn;
    }
    else{
      queueEnd -> next = nn;
      //queueEnd = nn;
    }


    // TODO Complete this function, handle the case when you're enqueuing in an empty queue
}

//TODO
void QueueLL::dequeue()
{
    Node *temp = new Node;
    if(!isEmpty())
    {
        temp = queueFront;
        queueFront = queueFront -> next;
        delete temp;
        if (queueFront == NULL){
          queueEnd = NULL;
        }
    }
    else{
        cout<<"queue is empty. can not deque"<<endl;
    }
}

int QueueLL::peek()
{
    if( !isEmpty() )
        return queueFront->key;
    else
    {
        cout<< " queue is empty. can not peek"<<endl;
        return -1;
    }
    return 0;
}

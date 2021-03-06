#include "LinkedList.hpp"

using namespace std;

LinkedList::LinkedList(){
        head = NULL;
    }

LinkedList::~LinkedList(){
	Node* crawler;
	while(head!=nullptr){
		crawler = head->next;
		delete head;
		head = crawler;
	}
}

// Add a new Node to the list
void LinkedList::insert(Node* prev, int newKey){

    //Check if head is Null i.e list is empty
    if(head == NULL){
        head = new Node;
        head->key = newKey;
        head->next = NULL;
    }

        // if list is not empty, look for prev and append our Node there
    else if(prev == NULL)
    {
        Node* newNode = new Node;
        newNode->key = newKey;
        newNode->next = head;
        head = newNode;
    }

    else{

        Node* newNode = new Node;
        newNode->key = newKey;
        newNode->next = prev->next;
        prev->next = newNode;

    }
}



// Building list
void LinkedList::loadList(int* keys , int length) {

    insert(NULL, keys[0]);

    Node* prev = head;

    for(int i = 1; i < length; i++)
    {
        insert(prev, keys[i]);
        prev = prev->next;
    }

}

// Print the keys in your list
void LinkedList::printList(){
    Node* temp = head;

    while(temp->next != NULL){
        cout<< temp->key <<" -> ";
        temp = temp->next;
    }

    cout<<temp->key<<" -> NULL"<<endl;
}

///////////////////////////////////////////////////////////////
// TODO : Complete the following function
void LinkedList::removeNthFromEnd(int n){
  Node* temp = head;
  Node* prev;
  int numFromBeg;
  int count = 1;
  int i = 0;
  while (temp -> next!=NULL){
    temp = temp -> next;
     count++;
   }
  temp = head;
  // Gets the number of elements it is from the beginning
  numFromBeg = count - n;
  // Moves temp to location
  while (i != numFromBeg){
    prev = temp;
    temp = temp-> next;
    i++;
  }
  while (temp != NULL){
    // If the tail is being deleted
    if (n == 1){
      prev -> next = NULL;
      delete temp;
      break;
    }
    // if the head is being deleted
    if (count == n){
      head = temp-> next;
      delete temp;
      break;
    }
    // If an element in the middle is being deleted
    if (n != 1){
      prev -> next = temp -> next;
      delete temp;
      break;
    }
    // If n is an invalid number
    if (numFromBeg < 0 || n > count){
      cout << "This is not a valid number" << endl;
    }
  }
}

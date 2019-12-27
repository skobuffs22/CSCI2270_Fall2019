#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct item{
	int data;
	item* next;
};

class HashTableLL{
	private:
		int M;
		int* table;
		int count = 0;
		int LLhash1(int k);
		int LLhash2(int k);
	  item* root;

	public:
		HashTableLL();
		~HashTableLL();
	  void deleteLL(int k);
		void Hash1LL(int k);
		void Hash2LL(int k);
	  void addLLNode(int k);
		int LLsearchHT(int k);
		bool searchLL(int k);
		double lf();
		double countFilled();
	  void printTable();
		int returnLLCount();
	};

// Constructor
HashTableLL::HashTableLL(){
	M = 10009;
	table = new int[M];
	for (int i=0; i<M; i++)
	{
		table[i] = -1;
    root = NULL;
  }
}

// Destructor
HashTableLL::~HashTableLL(){
	item* current = root;
	while(current != 0){
    item* next = current->next;
    delete current;
    current = next;
	}
	root = 0;
}

// First hash function (gets hash key)
int HashTableLL::LLhash1(int k){
	return k % M;
}

// Second hash function (gets hash key)
int HashTableLL::LLhash2(int k){
	int temp = floor(k / M);
	return temp % M;
}

// Function call to hash using first hash function
void HashTableLL::Hash1LL(int k){
	int index = LLhash1(k);
	if (table[index] == -1){
		table[index] = k;
	}
	else{
    addLLNode(k);
		count++;
  }
}

// Function call to hash using second hash function
void HashTableLL::Hash2LL(int k){
	int index = LLhash2(k);
	if (table[index] == -1){
		table[index] = k;
	}
	else{
    addLLNode(k);
		count++;
  }
}

// Addes a node to the linked list
void HashTableLL::addLLNode(int k){
  if (root == NULL){
    item* newRoot = new item;
    newRoot->data = k;
    newRoot->next = NULL;
    root = newRoot;
  }
  else{
    item* temp = root;
    item* node = new item;
    node->data = k;
    node->next = NULL;
     while(temp->next != NULL){
       temp = temp->next;
     }
   temp->next = node;
  }
}

// Searches through the hash table for an element
int HashTableLL::LLsearchHT(int k){
  int i = LLhash1(k);
  if (table[i] == -1){
    return -1;
  }
  else if (table[i] == k){
    return i;
  }
  else {
    bool flag = searchLL(k);
    return 0;
  }
}

// Searches through the linked list
bool HashTableLL::searchLL(int k){
	int index = LLhash1(k);
  if (table[index] == -1){
    return false;
  }
	else{
		if (table[index] == k){
			return true;
    }
    else{
			item* temp = root;
			while(temp != NULL){
				if (temp->data == k){
					return true;
				}
				temp = temp->next;
			}
		return false;
		}
	}
}

// Deletes a node from the linked list
void HashTableLL::deleteLL(int k){
	int index = LLhash1(k);
  if (table[index] != -1){
		if (table[index] == k){
      table[index] = -1;
    }
    else{
      item* temp = root;
      item* deleteNode = NULL;
      while(temp->next->data != k && temp != NULL){
        temp = temp->next;
      }
      if(temp->next->data == k){
      	deleteNode = temp->next;
      	temp->next = temp->next->next;
      	delete deleteNode;
      }
    }
  }
}

// Calculating load factor
double HashTableLL::lf(){
	double filled = countFilled();
	double temp = (filled / M);
	return temp;
}

// Couting up the number of times the hash function was used
double HashTableLL::countFilled(){
	double count = 0;
	for (int i = 0; i < M; i++){
		if (table[i] > 0){
			count++;
		}
	}
	item* temp = root;
	while (temp!= NULL){
		count++;
		temp = temp -> next;
	}
	return count;
}

// Prints table (if needed)
void HashTableLL::printTable(){
	cout << "| ";
	for (int i=0; i<M; i++)
		cout << table[i] << " | ";
	cout << endl;
}

// Returns number of times linear probe was used
int HashTableLL::returnLLCount(){
	return count;
}

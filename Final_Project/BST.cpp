#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct BSTNode {
	int key;
	BSTNode* left;
  BSTNode* right;
};

class BinarySearchTreeHT{
	private:
		int M;
		int* table;
		int count = 0;
	  BSTNode* root;
		int BSThash1(int k);
	  int BSThash2(int k);
	  BSTNode* BSTinsertNodeHelper(BSTNode* r, int k);
	  BSTNode* minNode(BSTNode* r);
	  BSTNode* searchTreeHelper(BSTNode* curr, int num);
		unsigned int binarytreeCountHelper(const BSTNode *root);
		void destroyNode(BSTNode *root);
		BSTNode* deleteNode(BSTNode *currNode, int value);
	  void printTreeHelper(BSTNode* currNode);

	public:
	  BinarySearchTreeHT();
		~BinarySearchTreeHT();
	  void Hash1BST(int k);
	  void Hash2BST(int k);
	  BSTNode* createNode(int k);
	  void BSTinsertNode(int k);
	  int searchHT(int k);
	  void searchTree (BSTNode* root, int num);
	  void deleteNum (int k);
	  void printTable();
		unsigned int binarytreeCount(const BSTNode *tree);
		int returnLPCount();
		double lf();
		double countFilled();
	  void printTree(int k);
};

// Constructor
BinarySearchTreeHT::BinarySearchTreeHT() {
	root = NULL;
  M =  10009;
	table = new int[M];
	for (int i=0; i<M; i++)
		table[i] = -1;
}

// Destructor
BinarySearchTreeHT::~BinarySearchTreeHT(){
     destroyNode(root);
}

// Destructor helper for the tree
void BinarySearchTreeHT::destroyNode(BSTNode *currNode){
     if(currNode!=NULL)
     {
         destroyNode(currNode->left);
         destroyNode(currNode->right);

         delete currNode;
         currNode = NULL;
     }
 }

// Creates a node to add to the tree
BSTNode* BinarySearchTreeHT::createNode(int k){
	BSTNode* newNode = new BSTNode;
	newNode->key = k;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

// Inserts a node into the tree
void BinarySearchTreeHT::BSTinsertNode(int k){
	root = BSTinsertNodeHelper(root, k);
}

// Insert node helper
BSTNode* BinarySearchTreeHT::BSTinsertNodeHelper(BSTNode* r, int k){
	if (r == NULL){ // At root
		r = createNode(k);
	}
	else if (r->key < k){ // To the right
		r->right = BSTinsertNodeHelper(r->right, k);
	}
	else{ // To the left
		r->left = BSTinsertNodeHelper(r->left, k);
	}
	return r;
}

// Searches the hash table
int BinarySearchTreeHT::searchHT(int k){
  int i = BSThash1(k);
  if (table[i] == -1){
    return -1;
  }
  else if (table[i] == k){
    return i;
  }
  else {
    searchTree(root, k);
    return 0;
  }
}
 // Helper function to search the tree
BSTNode* BinarySearchTreeHT::searchTreeHelper(BSTNode* curr, int num){
    if (curr){
        if (curr -> key == num){
					//cout << "Found " << num << " in the tree" << endl;
            return curr;
        }
        else if (curr -> key < num){
            return searchTreeHelper (curr -> right, num);
        }
        else if (curr -> key > num) {
            return  searchTreeHelper (curr -> left, num);
        }
    }
    else {
        return NULL;
    }
  return NULL;
}

// Search function for the tree
void BinarySearchTreeHT::searchTree (BSTNode* root, int num){
  BSTNode* tree = searchTreeHelper(root, num);
}

// Main delete function
void BinarySearchTreeHT::deleteNum(int k){
  int i = searchHT(k);
  if (i > 0){
    table[i] = -1;
  }
  else{
    deleteNode(root, k);
  }
}

// Finds the smallest node to the left (for replacing a parent)
BSTNode* BinarySearchTreeHT::minNode(BSTNode* r) {
	if (r->left){
		return minNode(r->left);
  }
	if (!r->left){
    return r;
  }
  return r;
}

// Deletes a node in the tree
BSTNode* BinarySearchTreeHT::deleteNode(BSTNode *currNode, int value){
  if(currNode == NULL){
    return NULL;
  }
  else if(value < currNode->key){
    currNode->left = deleteNode(currNode->left, value);
  }
  else if(value > currNode->key){
    currNode->right = deleteNode(currNode->right, value);
  }
  else{
    //No child
    if(currNode->left == NULL && currNode->right == NULL){
      delete currNode;
      currNode = NULL;
    }
    //Only right child
    else if(currNode->left == NULL){
      BSTNode* temp = new BSTNode;
      temp = currNode;
      currNode = currNode -> right;
      delete temp;
    }
    //Only left child
    else if(currNode->right == NULL){
      BSTNode* temp = new BSTNode;
      temp = currNode;
      currNode = currNode -> left;
      delete temp;
    }
    //Both left and right child
    else{
      currNode -> key = minNode(currNode->left) -> key;
      currNode->left = deleteNode(currNode->left, currNode -> key);
    }
  }
return currNode;
}

// First hash function (gets hash key)
int BinarySearchTreeHT::BSThash1(int k) {
	return k % M;
}

// Second hash function (gets hash key)
int BinarySearchTreeHT::BSThash2(int k) {
  int temp = floor(k / M);
  return temp % M;
}

// Function call to hash using first hash function
void BinarySearchTreeHT::Hash1BST(int k){
	int index = BSThash1(k);
	if (table[index] >= 0){
    BSTinsertNode(k);
		count++;
  }
	else{
    table[index] = k;
  }
}

// Function call to hash using second hash function
void BinarySearchTreeHT::Hash2BST(int k){
	int index = BSThash2(k);
	if (table[index] >= 0){
    BSTinsertNode(k);
		count++;
  }
	else{
    table[index] = k;
  }
}

// Prints the table (if needed)
void BinarySearchTreeHT::printTable() {
  cout << "| ";
	for (int i=0; i<M; i++)
		cout << table[i] << " | ";
	cout << endl;
}

// Prints the tree (if needed)
void BinarySearchTreeHT:: printTree(int k){
  printTreeHelper(root);
  cout<<endl;
}

// Print tree helper
void BinarySearchTreeHT:: printTreeHelper(BSTNode* currNode){
     if(currNode){
        printTreeHelper( currNode->left);
        cout << " " << currNode->key;
        printTreeHelper( currNode->right);
     }
 }
// Count helper
unsigned int BinarySearchTreeHT::binarytreeCountHelper(const BSTNode *root){
	unsigned int count = 1;
  if (root->left != NULL) {
     count += binarytreeCountHelper(root->left);
  }
  if (root->right != NULL) {
      count += binarytreeCountHelper(root->right);
  }
  return count;
}

// Counts the number of nodes in the tree
unsigned int BinarySearchTreeHT::binarytreeCount(const BSTNode *tree){
	unsigned int count = 0;
  if (root != NULL) {
      count = binarytreeCountHelper(root);
  }
  return count;
}

// Calculating load factor
double BinarySearchTreeHT::lf(){
	double filled = countFilled();
 	double temp = (filled / M);
 	return temp;
}

// Couting up the number of times the hash function was used
double BinarySearchTreeHT::countFilled(){
 	double count = 0;
	double temp;
 	for (int i = 0; i < M; i++){
 		if (table[i] > 0){
 			count++;
 		}
 	}
	count += binarytreeCount(root);
 	return count;
}

// Returns number of times linear probe was used
int BinarySearchTreeHT::returnLPCount(){
	return count;
}

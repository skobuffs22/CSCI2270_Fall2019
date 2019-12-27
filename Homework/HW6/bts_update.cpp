#include <iostream>

using namespace std;

struct Node {
	int key;
	Node *left, *right;
};

class BinarySearchTree {
private:
	Node* root;
	void printTreeHelper(Node* root);
	Node* searchKeyHelper(Node* root, int k);
	void printRecursiveCallsHelper(Node* root, int count);
	Node* insertNodeHelper(Node* r, int k);
	Node* createNode(int k);
	Node* deleteNodeHelper(Node* r, int k);
	Node* minNode(Node* r);
public:
	BinarySearchTree();
	void printTree();
	void searchKey(int k);
	void printRecursiveCalls();
	void insertNode(int k);
	void deleteNode(int k);
};

BinarySearchTree::BinarySearchTree() {
	root = NULL; // 'nullptr' is not an int, 'NULL' can be
}

void BinarySearchTree::printTree() {
	printTreeHelper(root);
	cout << endl;
}
void BinarySearchTree::printTreeHelper(Node* root) {
	if (root) {
		// Left subtree
		printTreeHelper(root->left);
		// middle node (parent)
		cout << root->key << " ";
		// Right subtree
		printTreeHelper(root->right);
	}
}

// NEW METHOD FOR DISPLAYING RECURSIVE DEPTH
void BinarySearchTree::printRecursiveCalls() {
	printRecursiveCallsHelper(root, 0);
	cout << endl;
}
void BinarySearchTree::printRecursiveCallsHelper(Node* root, int count) {
	if (root) {
		for(int i=0; i<count; i++)
			cout << "\t";
		cout << "printTree(" << root->key << ", " << count <<  ")"<< endl;

		// Left subtree
		printRecursiveCallsHelper(root->left, ++count); // In class this was 'count++', that's POST-decrementing, we need it PRE-incremented!
		// middle node (parent)
		//cout << root->key << " ";
		// Right subtree
		printRecursiveCallsHelper(root->right, ++count);
	}
}

Node* BinarySearchTree::createNode(int k) {
	Node* newNode = new Node;
	newNode->key = k;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

void BinarySearchTree::insertNode(int k) {
	root = insertNodeHelper(root, k);
}
Node* BinarySearchTree::insertNodeHelper(Node* r, int k) {
	// Insert at the head
	if (r == NULL)
		r = createNode(k);
	else if (r->key < k) // insert to the RIGHT
		r->right = insertNodeHelper(r->right, k);
	else
		r->left = insertNodeHelper(r->left, k);

	return r;
}


void BinarySearchTree::searchKey(int k) {
	Node* ret = searchKeyHelper(root, k);
	if (ret) // ret is not NULL
		cout << ret->key << " has been found!" << endl;
	else
		cout << "Key is not in tree :(" << endl;
}
Node* BinarySearchTree::searchKeyHelper(Node* root, int k) {
	if (root) {
		if (root->key == k)
			return root;
		else if (root->key < k) // Look to the right
			return searchKeyHelper(root->right, k);
		else if (root->key > k) // Look to the left
			return searchKeyHelper(root->left, k);
	} else {
		return NULL;
	}
}
Node* BinarySearchTree::minNode(Node* r) {
	if (r->left)
		return minNode(r->left);
	if (!r->left)
		return r;

}
void BinarySearchTree::deleteNode(int k) {
	root = deleteNodeHelper(root, k);
}
Node* BinarySearchTree::deleteNodeHelper(Node* r, int k) {
	// Insert at the head
	if (!r) // R is null
		return r;
	else if (r->key < k) // delete from the RIGHT
		r->right = deleteNodeHelper(r->right, k);
	else if (r->key > k) // delete from the LEFT
		r->left = deleteNodeHelper(r->left, k);
	else { // This is our node, we found it!
		// 3 Cases
		Node* toReturn = r;
		if (r->left == r->right) { // both are null -> NO CHILDREN
			delete r;
			r = NULL;
		} else if (r->left == NULL) { //  there is a right child
			toReturn = r->right;
			delete r;
			return toReturn;
		} else if (r->right == NULL) { //  there is a left child
			toReturn = r->left;
			delete r;
			return toReturn;
		} else { // There are two children
			Node* rightMin = minNode(r->right);
			int kay = rightMin->key;
			deleteNodeHelper(root, rightMin->key);

			rightMin->key = kay;
			rightMin->left = r->left;
			rightMin->right = r->right;
			delete r;
			return rightMin;
		}
	}

	return r;
}

int main() {
	BinarySearchTree bst;

	bst.insertNode(10);
	bst.printTree();
	bst.insertNode(12);
	bst.printTree();
	bst.insertNode(5);
	bst.printTree();
	bst.insertNode(4);
	bst.printTree();
	bst.deleteNode(5);
	bst.printTree();
	return 0;

	bst.printRecursiveCalls();
	return -12;
	bst.insertNode(6);
	bst.printTree();
	bst.insertNode(13);
	bst.printTree();
	bst.insertNode(17);
	bst.printTree();

	return 0;
}

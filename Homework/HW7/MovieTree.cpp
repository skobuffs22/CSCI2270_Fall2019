#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

MovieTree::

MovieTree::MovieTree(){
  root = NULL;
}

void destroyLLNode(TreeNode* curr){
  if (curr != NULL){
    destroyLLNode(curr -> leftChild);
    destroyLLNode(curr -> rightChild);
    LLMovieNode* current = curr -> head;
    while(current != 0) {
        LLMovieNode* next = current->next;
        delete current;
        current = next;
    }
    LLMovieNode* head = curr -> head;
    head = 0;
  }
}

void destroyTreeNode(TreeNode* node){
  if (node)
    {
        destroyTreeNode(node->leftChild);
        destroyTreeNode(node->rightChild);
        delete node;
    }
}

MovieTree::~MovieTree(){
  destroyLLNode (root);
  destroyTreeNode (root);
}

void printMovieInventoryHelper (TreeNode* root){
  if (root){
    printMovieInventoryHelper (root -> leftChild);
    cout << "Movies starting with letter: " << root -> titleChar << endl;
    if (root -> head){
      LLMovieNode* temp = root -> head;
      while (temp != NULL){
        cout << " >> " << temp -> title << " " << temp -> rating << endl;
        temp = temp -> next;
      }
    }
    printMovieInventoryHelper(root -> rightChild);
  }
}

void MovieTree::printMovieInventory(){
  if (root){
    printMovieInventoryHelper(root);
  }
  else {

  }
}

TreeNode* searchTreeHelper(TreeNode* curr, char letter){
    if (curr){
        if (curr -> titleChar == letter){
            return curr;
        }
        else if (curr -> titleChar < letter){
            return searchTreeHelper (curr -> rightChild, letter);
        }
        else if (curr -> titleChar > letter) {
            return  searchTreeHelper (curr -> leftChild, letter);
        }
    }
    else {
        return NULL;
    }
}

TreeNode* searchTree (TreeNode* root, char letter){
    TreeNode* tree = searchTreeHelper(root, letter);
    if (tree != NULL){
		return tree;
	}
	else {
		return NULL;
	}
}

TreeNode* createTreeNode(char letter){
    TreeNode* temp = new TreeNode;
    temp -> titleChar = letter;
    temp -> rightChild = NULL;
    temp -> leftChild = NULL;
    return temp;
}

TreeNode* addTreeNodeHelper (TreeNode*& root, char letter){
    if (root == NULL){
        root = createTreeNode(letter);
    }
    else if (root -> titleChar < letter){
        root -> rightChild = addTreeNodeHelper(root -> rightChild, letter);
    }
    else{
        root -> leftChild = addTreeNodeHelper(root -> leftChild, letter);
    }
    return root;
}

LLMovieNode* createLLNode (int ranking, string title, int year, float rating){
    LLMovieNode* temp = new LLMovieNode;
    temp -> ranking = ranking;
    temp -> title = title;
    temp -> year = year;
    temp -> rating = rating;
    return temp;
}

void addTreeNode (TreeNode*& root, char letter){
    root = addTreeNodeHelper (root, letter);
}

LLMovieNode* searchLL(LLMovieNode* head, string title){
    LLMovieNode* temp = head;
    while (temp != NULL){
        if (temp -> title > title){
            return temp;
        }
        else {
            temp = temp -> next;
        }
        return NULL;
    }
}

void addLLMovieNode (TreeNode* letterNode, LLMovieNode* newNode){
    LLMovieNode* temp = letterNode -> head;
    LLMovieNode* prev = NULL;
    if (letterNode -> head == NULL){
        letterNode -> head = newNode;
        return;
    }
    if (letterNode -> head -> title > newNode -> title){
        newNode -> next = letterNode -> head;
        letterNode -> head = newNode;
        return;
    }
    while (temp -> next != NULL){
        if (newNode -> title < temp -> title){
            prev -> next = newNode;
            newNode -> next = temp;
            return;
        }
        prev = temp;
        temp = temp -> next;
    }
    newNode -> next = temp -> next;
    temp -> next = newNode;
    return;
}

void MovieTree::addMovie(int ranking, std::string title, int year, float rating){
    char letter = title.front();
    TreeNode* isLetter = searchTree(root, letter);
    if (isLetter != NULL){

    }
    else {
        addTreeNode (root, letter);
    }
    TreeNode* isLettercheck = searchTree(root, letter);
    LLMovieNode* LLhead = isLettercheck -> head;
    LLMovieNode* isLL = searchLL (LLhead, title);
    LLMovieNode* newNode = createLLNode(ranking, title, year, rating);
    addLLMovieNode (isLettercheck, newNode);
    LLMovieNode* isLLcheck = searchLL (LLhead, title);
}

LLMovieNode* searchLLL(TreeNode* node, string title) {
    LLMovieNode* ptr = node -> head;
    while (ptr != NULL && ptr->title != title)
    {
        ptr = ptr->next;
    }
    return ptr;
}

bool isEmpty (TreeNode* node){
    LLMovieNode* temp = node -> head;
    if (temp == NULL){
        return true;
    }
    return false;
}

void deleteLLNode(TreeNode* curr, string title) {
  LLMovieNode* temp = curr -> head;
  LLMovieNode* prev = NULL;
  while (temp != NULL){
    if (curr -> head -> title == title){
      curr -> head = temp -> next;
      delete temp;
      break;
    }
    if (temp -> title == title){
      prev -> next = temp -> next;
      delete temp;
      break;
    }
    else {
      prev = temp;
      temp = temp -> next;
    }
  }
}

TreeNode* getMaxValueNode(TreeNode* curr){
    if(curr->rightChild == NULL){
        return curr;
    }
    return getMaxValueNode(curr->rightChild);
}

TreeNode* deleteTreeNode(TreeNode*& curr, char letter){

  if(curr == NULL)
  {
    return NULL;
  }
  else if(letter < curr->titleChar)
  {
    curr->leftChild = deleteTreeNode(curr->leftChild, letter);
  }
  else if(letter > curr->titleChar)
  {
    curr->rightChild = deleteTreeNode(curr->rightChild, letter);
  }
  // We found the node with the value
  else
  {
    //TODO Case : No child
    if(curr->leftChild == NULL && curr->rightChild == NULL)
    {
      delete curr;
      curr = NULL;
    }
    //TODO Case : Only right child
    else if(curr->leftChild == NULL)
    {
      TreeNode* temp = new TreeNode;
      temp = curr;
      curr = curr -> rightChild;
      delete temp;
    }
    //TODO Case : Only left child
    else if(curr->rightChild == NULL)
    {
      TreeNode* temp = new TreeNode;
      temp = curr;
      curr = curr -> leftChild;
      delete temp;
    }
    //TODO Case: Both left and right child
    else
    {
      TreeNode* max = getMaxValueNode(curr -> leftChild);
      curr -> titleChar = max -> titleChar;
      curr -> head = max -> head;
      curr -> leftChild = deleteTreeNode(curr -> leftChild, curr -> titleChar);
    }
  }
return curr;
}

void MovieTree::deleteMovie(std::string title){
    char letter = title.front();
    TreeNode* isLetter = searchTree(root, letter);
    if (isLetter != NULL){
        LLMovieNode* LLhead = isLetter -> head;
        LLMovieNode* movieinLL = searchLLL(isLetter, title);
        if (movieinLL != NULL){
            deleteLLNode(isLetter, title);
            bool empty = isEmpty(isLetter);
            if (empty == true){
                TreeNode* notsure = deleteTreeNode(root, letter);
            }
        }
        else {
            cout << "Movie: " << title << " not found, cannot delete." << endl;
        }
    }
    else{
        cout << "Movie: " << title << " not found, cannot delete." << endl;
    }

}

#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

MovieTree::MovieTree() {
  root = NULL;
}

MovieTree::~MovieTree() {
  //write your createNode
}

void printMovieInventoryHelper(MovieNode* root){
  if (root){
    printMovieInventoryHelper(root -> left);
    cout << "Movie: " << root -> title << " " << root -> rating << endl;
    printMovieInventoryHelper(root -> right);
  }
}

void MovieTree::printMovieInventory() {
  if (root){
    printMovieInventoryHelper(root);
  }
  else {
    cout << "Tree is Empty. Cannot print";
  }
}

MovieNode* addMovieNodeHelper (MovieNode* curr, MovieNode* newNode){
  if (curr == NULL){
    return newNode;
  }
  else if (curr -> title < newNode -> title){
    curr -> right = addMovieNodeHelper (curr -> right, newNode);
  }
  else if (curr -> title > newNode -> title){
    curr -> left = addMovieNodeHelper(curr -> left, newNode);
  }
  return curr;
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) {
  MovieNode* newNode = new MovieNode(ranking, title, year, rating);
  root = addMovieNodeHelper(root, newNode);
}

MovieNode* findMovieHelper(MovieNode* root, string title){
  if (root){
    if (title == root -> title){
      return root;
    }
    else if (title > root -> title){
      return findMovieHelper(root -> right, title);
    }
    else if (title < root -> title){
      return findMovieHelper(root -> left, title);
    }
    else {
      return NULL;
    }
  }
  return NULL;
}

void MovieTree::findMovie(string title) {
  MovieNode* temp = findMovieHelper (root, title);
  if (temp){
    cout << "Movie Info:" << endl;
    cout << "==================" << endl;
    cout << "Ranking:" << temp -> ranking << endl;
    cout << "Title  :" << temp -> title << endl;
    cout << "Year   :" << temp -> year << endl;
    cout << "rating :" << temp -> rating << endl;
  }
  else {
    cout << "Movie not found." << endl;
  }
}

void queryMoviesHelper(MovieNode* root, float rating, int year){
  if (root){
    if (root -> rating > rating && root -> year > year){
        cout << root -> title << "(" << root -> year << ") " << root -> rating << endl;
    }
    queryMoviesHelper (root -> left, rating, year);
    queryMoviesHelper (root -> right, rating, year);
  }
}

void MovieTree::queryMovies(float rating, int year) {
  cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
  queryMoviesHelper(root, rating, year);
}

float averageRatingSum(MovieNode* root){
  if (root == NULL){
    return 0.0;
  }
  float rating = root -> rating;
  rating += averageRatingSum(root -> left);
  rating += averageRatingSum(root -> right);
  return rating;
}

float averageRatingCount(MovieNode* root){
  if (root == NULL) {
      return 0;
  }
  int count = 1;
  count += averageRatingCount(root -> left);
  count += averageRatingCount(root -> right);
  return count;
}

void MovieTree::averageRating() {
  if (root){
    float average = averageRatingSum(root)/averageRatingCount(root);
    cout << "Average rating:" << average << endl;
  }
  else {
    cout << "Average rating:0.0" << endl;
  }
}

#include "MovieTree.cpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


void displayMenu();

int main(int argc, char* argv[]){

  ifstream Movies (argv[1]);
  MovieTree mt;

  string line;
  while (getline(Movies, line)){
    string ranking, title, year, rating;
    istringstream iss(line);
    getline(iss, ranking, ',');
    getline(iss, title, ',');
    getline(iss, year, ',');
    getline(iss, rating, ',');
    mt.addMovieNode(stof(ranking), title, stoi(year), stof(rating));
  }

  int numSelect = 0;
  while (numSelect != 5){
    displayMenu();
    cin >> numSelect;
    cin.ignore();


    if (numSelect == 1){
      string title;
      cout << "Enter title:" << endl;
      getline (cin, title);
      mt.findMovie(title);
    }
    if (numSelect == 2){
      float rating;
      int year;
      cout << "Enter minimum rating:" << endl;
      cin >> rating;
      cout << "Enter minimum year:" << endl;
      cin >> year;
      mt.queryMovies(rating, year);
    }
    if (numSelect == 3){
      mt.printMovieInventory();
    }
    if (numSelect == 4){
      mt.averageRating();
    }
  }
  if (numSelect == 5){
    cout << "Goodbye!" << endl;
  }
  return 0;
}

void displayMenu()
{
  cout << "======Main Menu======" << endl;
  cout << "1. Find a movie" << endl;
  cout << "2. Query movies" << endl;
  cout << "3. Print the inventory" << endl;
  cout << "4. Average Rating of movies" << endl;
  cout << "5. Quit" << endl;
}

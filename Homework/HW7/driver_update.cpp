#include "MovieTree.cpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void displayMenu();

int main(int argc, char* argv[]){
    fstream Movies(argv[1]);
    MovieTree mt;
    string line;
    while (getline(Movies, line)){
      string ranking, title, year, rating;
      istringstream ss(line);
      getline(ss, ranking, ',');
      getline(ss, title, ',');
      getline(ss, year, ',');
      getline(ss, rating, ',');
      mt.addMovie(stof(ranking), title, stoi(year), stof(rating));
    }
    int numSelect = 0;

    while (numSelect != 3){
      displayMenu();
      cin >> numSelect;
      cin.ignore();
      if (numSelect > 3 || numSelect < 1){
        cout << "This number is not an option!" << endl;
      }


      if (numSelect == 1){
        mt.printMovieInventory ();
      }

      if (numSelect == 2){
        string movieTitle;
        cout << "Enter a movie title: " << endl;
        cin >> movieTitle;
        deleteMovie(movieTitle);
      }

      if (numSelect == 3){
        cout << "Goodbye!" << endl;
      }
    }
    return 0;
}


 void displayMenu(){
   cout << "======Main Menu======" << endl;
   cout << "1. Print the inventory" << endl;
   cout << "2. Delete a movie" << endl;
   cout << "3. Quit" << endl;
   cout << "4. Add Movie" << endl;
 }

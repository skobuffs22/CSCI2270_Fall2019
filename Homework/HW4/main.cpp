#include <iostream>
#include <list>
#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
  head = NULL;
}

bool CountryNetwork::isEmpty(){
  if (head != NULL){
    return true;
  }
  else {
    return false;
  }
}

void CountryNetwork::insertCountry(Country* previous, string countryName)
{
  if (previous == NULL){
    Country* temp = new Country();
    temp -> name = countryName;
    temp -> next = head;
    head = temp;
    cout << "adding: " << countryName << " (HEAD)" << endl;

  }
  else{
    Country* temp = new Country();
    cout << "adding: " << countryName << " (prev: "<< previous->name << ")" << endl;
    temp -> name = countryName;
    temp -> next = previous -> next;
    previous -> next = temp;
  }
}

void CountryNetwork::deleteCountry(string countryName) {
  Country* temp = head;
  Country* prev = NULL;
  while (temp != NULL){
    if (head -> name == countryName){
      head = temp -> next;
      delete temp;
      break;
    }
    if (temp -> name == countryName){
      prev -> next = temp-> next;
      delete temp;
      break;
    }
    else {
      prev = temp;
      temp = temp -> next;
    }
  }
}

void CountryNetwork::loadDefaultSetup()
{
  string countries [6] = {"United States", "Canada", "Brazil", "India", "China", "Australia"};
  Country *ptr = NULL;
  string countryName = countries [0];
  insertCountry (ptr, countryName);
  ptr = head;
  for (int i = 1; i < 6; i++){
    insertCountry (ptr, countries[i]);
    ptr = ptr->next;
  }
}

Country* CountryNetwork::searchNetwork(string countryName)
{
 Country* temp = head;
 while (temp != NULL){
   if (temp -> name == countryName){
     return temp;
   }
   else {
     temp = temp -> next;
   }
 }
 return NULL;
}

void CountryNetwork::deleteEntireNetwork(){
  Country* temp = head;
  string countryName;
  if (head != NULL){
    while (temp != NULL){
      countryName = temp -> name;
      cout << "deleting: " << countryName << endl;
      deleteCountry(countryName);
      temp = temp -> next;
    }
    cout << "Deleted network" << endl;
  }
  else {
    return;
  }
}


void CountryNetwork :: rotateNetwork(int n) {
  Country* first = head;
  Country* last = head;
  Country* count = head;
  Country* temp;

  int j = 0;
  if (head == NULL){
      cout << "Linked List is Empty" << endl;
      return;
  }
  while (count -> next != NULL) {
        count = count -> next;
        j++;
  }

  if (j >= n){
      for (int i = 0; i < n; i++){
        first = head;
        temp = first;
        while (last -> next != NULL) {
            last = last -> next;
        }
        head = first -> next;
        last -> next = temp;
        temp -> next = NULL;
      }
      cout << "Rotate Complete" << endl;
    }
  if (j < n){
      cout << "Rotate not possible" << endl;
  }
}

void CountryNetwork::reverseEntireNetwork() {
  Country* temp = head;
  Country* prev = NULL;
  Country* next = NULL;
  while (temp != NULL){
    next = temp -> next;
    temp -> next = prev;
    prev = temp;
    temp = next;
  }
  head = prev;
}

void CountryNetwork::printPath(){
  Country* temp = head;
  cout << "== CURRENT PATH ==" << endl;

  if (head == NULL){
    cout << "nothing in path" << endl;
    cout << "===" << endl;
    return;
  }
  while (temp != NULL){
    cout << temp -> name << " -> ";
    temp = temp -> next;
  }
  cout << "NULL" << endl;
  cout << "===" << endl;
}

void displayMenu();







int main(int argc, char* argv[])
{
    int numSelect = 0;
    int i = 0;
    CountryNetwork countryNet;

    while (numSelect != 8){
      displayMenu();
      int list[100];
      cin >> numSelect;
      list [i] = numSelect;
      i++;
      cin.ignore();
      if (numSelect > 8 || numSelect < 1){
        cout << "This number is not an option!" << endl;
      }


      if (numSelect == 1){
        // Build Networt
        countryNet.loadDefaultSetup();
        countryNet.printPath();

      }

      if (numSelect == 2){
        // Print network Path
        countryNet.printPath();

      }

      if (numSelect == 3){
        // Add Country
        Country* temp;

        string countryName, location;
        cout << "Enter a new country name: " << endl;
        cin >> countryName;
        cin.ignore();

        cout << "Enter the previous country name (or First): " << endl;
        cin >> location;
        cin.ignore();

        temp = countryNet.searchNetwork(location);
        while (temp == NULL && location != "First"){
          cout << "INVALID(previous country name)...Please enter a VALID previous country name!" << endl;
          cin >> location;
          cin.ignore();
          temp = countryNet.searchNetwork(location);
        }
        countryNet.insertCountry(temp, countryName);
        countryNet.printPath();
      }

        if (numSelect == 4){
        // Delete country
          Country* exist;
          int val = 0;
          string countryRec;
          cout << "Enter a country name: \n";
          getline(cin, countryRec);
          exist = countryNet.searchNetwork(countryRec);
          cout << "\n";
          if (exist != NULL){
            countryNet.deleteCountry(countryRec);
          }
          if (exist == NULL) {

            for (int j = 0; j < i; j++){
              if (list[j] == 1){
                val = 1;
              }
            }
            if (val == 1){
              cout << "Country not found" << endl;
            }
            if (val == 0){
              cout << "Empty list" << endl;
            }
          }
          countryNet.printPath();
        }

        if (numSelect == 5){
          // Reverse network
          Country* exist;
          countryNet.isEmpty();
          if (countryNet.isEmpty() == true){
            countryNet.reverseEntireNetwork();
          }
          if (countryNet.isEmpty() == false) {
            cout << "Empty list" << endl;
          }
          countryNet.printPath();
        }

        if (numSelect == 6){
          // Rotate newtork
          int val;
          cout << "Enter the count of values to be rotated: " << endl;
          cin >> val;
          countryNet.rotateNetwork(val);
          countryNet.printPath();
        }

        if (numSelect == 7){
          // Clear network
          cout << "Network before deletion" << endl;
          countryNet.printPath();
          countryNet.deleteEntireNetwork();
          cout << "Network after deletion" << endl;
          countryNet.printPath();
        }

        if (numSelect == 8){
          cout << "Quitting... cleaning up path:" << endl;
          countryNet.printPath();
          countryNet.deleteEntireNetwork();
          cout << "Path cleaned" << endl;
          cout << "Goodbye!" << endl;
      }
    }
    return 0;
}

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Add Country " << endl;
    cout << " 4. Delete Country " << endl;
    cout << " 5. Reverse Network" << endl;
    cout << " 6. Rotate Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}

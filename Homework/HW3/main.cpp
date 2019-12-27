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


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
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

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
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

/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 */
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

/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
  Country* temp = head;
  while (receiver != temp -> name){
    temp -> message = message;
    temp -> numberMessages += 1;
    cout << temp -> name << " [# messages received: " << temp -> numberMessages << "] received: " << message << endl;
    temp = temp -> next;
  }
  temp -> numberMessages += 1;
  cout << temp -> name << " [# messages received: " << temp -> numberMessages << "] received: " << message << endl;
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
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


// declarations for main helper-functions
void displayMenu();

int main(int argc, char* argv[])
{
    // Object representing our network of cities.
    // (Linked list representation is in CountryNetwork)
    int numSelect = 0;
    int i = 0;
    CountryNetwork countryNet;

    while (numSelect != 5){
      displayMenu();
      int list[100];
      cin >> numSelect;
      list [i] = numSelect;
      i++;
      cin.ignore();
      if (numSelect > 5 || numSelect < 1){
        cout << "This number is not an option!" << endl;
      }


      if (numSelect == 1){
        // Build Networt
        countryNet.loadDefaultSetup();
        countryNet.printPath();

      }
      if (numSelect == 2){
        // Print network Path
        //cout << head -> name << endl;
        countryNet.printPath();

      }
      if (numSelect == 3){
        // Transmit Message
        Country* exist;
        int val = 0;
        string countryRec,message;
        cout << "Enter name of the country to receive the message: " << endl;
        getline(cin, countryRec);
        cout << "Enter the message to send:"<< endl;
        getline(cin, message);
        exist = countryNet.searchNetwork(countryRec);
        cout << "\n";
        if (exist != NULL){
          countryNet.transmitMsg(countryRec, message);
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
      }


      if (numSelect == 4){
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
    }

    if (numSelect == 5){
      cout << "Quitting..." << endl;
      cout << "Goodbye!" << endl;
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
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";

}

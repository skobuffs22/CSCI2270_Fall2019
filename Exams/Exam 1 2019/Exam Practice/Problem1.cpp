# include <iostream>

# include "LinkedList.hpp"

// # include <fstream>
// # include <string>
// # include <sstream>


using namespace std;


LinkedList::LinkedList()
{
  head = NULL;
}


bool LinkedList::lengthIsEven (){
  int count = 0;
  Node* temp = head;
  while (temp != NULL){
    temp = temp -> next;
    count++;
  }
  cout << count << endl;
  if (count % 2 == 0){
    return true;
  }
  else {
    return false;
  }
}

main (){
  LinkedList a;
  bool exist;
  string yep;
  exist = a.lengthIsEven ();
  if (exist == true){
    yep = "even";
  }
  if (exist == false){
    yep = "odd";
  }

  cout << "This linked list is " << yep << "." << endl;
}

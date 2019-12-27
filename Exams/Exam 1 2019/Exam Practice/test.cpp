# include <iostream>
using namespace std;


main (){
  int v1, p1;
  p1 = &v1;
  *p1 = 42;
  cout << v1 << endl;
  cout << *p1 << endl;
}



void double()

# include <iostream>
using namespace std;
int main ()
{
  int a[] = {1,2,3};
  cout << a << endl;        // Returns an address
  cout << a+2 << endl;      // Returns an address that is 8 higher (fro 4 to c)
  cout << *(a+2) << endl;   // Returns 3 (1+2)
  cout << *a << endl;       // Returns 1 (a[0])
  // cout << *a[0] << endl; Does not work
}

#include<iostream>
#include<string>
using namespace std;

/*
// Split 'arr' into 'even_arr' & 'odd_arr'
//  - 'arr': pointer to original array
//  - 'even_arr': pointer to even array
//  - 'odd_arr': pointer to odd array
*/
void split(int* &arr, int* &even_arr, int* &odd_arr, int size, int &even_size, int &odd_size){
  int i = 0;
  int evensize = 0;
  int oddsize = 0;
  while (i < size){
    int num;
    num = arr[i];
    if (num % 2 == 0){
      even_arr[evensize] = num;
      evensize++;
    }
    if (num % 2 != 0){
      odd_arr[oddsize] = num;
      oddsize++;
    }
    i++;
  }
  even_size = evensize;
  odd_size = oddsize;
}

void printArray(int* arr, int size) {
    for(int i = 0; i<size; i++)
    {
        cout<< arr[i];
        if(i < size-1)
          cout << ", ";
    }
    cout<<endl;
}

int main(int argc, char* argv[])
{
    if(argc<2)
    {
      cout<<"usage: a.out <#>";
      return -1;
    }
    if (argc < 0){
      cout << "invalid number (non-positive integer)" << endl;
      return -1;
    }

	// Create input array:
    int size = stoi(argv[1]);
    int *arr = new int[size];
    // checks if size of array is 0 or a nonpositive integer
    if (size != 0){
      cout<< "original array: ";
      for(int i = 0; i<size; i++)
      {
          arr[i] = rand()%100;
          cout<< arr[i];
          if(i < size-1)
            cout << ", ";
      }
    }
    else {
      cout << "Empty array" << endl;
    }
    cout<<endl;

    // allocating
    int *even_size = new int;
    int *odd_size = new int;
    int *even_arr = new int[*even_size];
    int *odd_arr = new int[*odd_size];
    if(size != 0){
      // calls split function
      split(arr, even_arr, odd_arr, size, *even_size, *odd_size);
      // checks all the different cases of the even and odd arrays
      if (*even_size == 0){
        cout << "no even items in the array" << endl;
        cout << "odd array: ";
        printArray(odd_arr, *odd_size);
      }
      if (*odd_size == 0){
        cout << "no odd items in the array" << endl;
        cout << "\n" << endl;
        cout << "even array: ";
        printArray(even_arr, *even_size);
      }

      if (*even_size !=0 && *odd_size != 0){
        cout << "even array: ";
        printArray(even_arr, *even_size);
        cout << "odd array: ";
        printArray(odd_arr, *odd_size);
      }
    }

	// Clean up (delete)
    delete even_size;
    delete odd_size;
    delete even_arr;
    delete odd_arr;

    return 0;
}

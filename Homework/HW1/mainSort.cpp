# include <iostream>
# include <fstream>
using namespace std;

int insertIntoSortedArray(int myArray[], int numEntries, int newValue){
  if (numEntries == 0) {
    myArray[0] = newValue;
  }
  else{
    for (int i = 0; i<numEntries; i++) {
      if (newValue < myArray[i]) {
        for (int j = numEntries; j > i; j--) {
          myArray[j] = myArray[j-1];
        }

        myArray[i] = newValue;

        break;
      }
      else {
        if (i == numEntries - 1) {
          myArray[numEntries] = newValue;
        }
      }
    }
  }
  numEntries++;
  return numEntries;
}



int main (int argc, char *argv[]) {
  ifstream numFile;
  numFile.open (argv[1], ios::in);


  int myArray[100];
  string newValue_str;

  if (numFile.is_open()){
    int numEntries = 0;
    while (getline (numFile, newValue_str)){

      int newValue = stoi(newValue_str);
      numEntries = insertIntoSortedArray (myArray, numEntries, newValue);
      for (int i = 0; i< numEntries; i++) {
        if (i == numEntries - 1) {
          cout << myArray[i] << endl;
        }
        else {
          cout << myArray[i] << ", ";
        }
      }
    }
  }
  else {
    cout << "File failed to open" << endl;
  }
  numFile.close();
  return 0;
}

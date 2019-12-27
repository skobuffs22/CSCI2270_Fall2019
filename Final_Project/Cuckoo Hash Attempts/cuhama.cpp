#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

class cuckooHash{
private:
  int M;
  int count;
  vector<int> list;
  int* tableOne;
  int* newTableOne;
  int* tableTwo;
  int* newTableTwo;

  int hash1(int k);
  int hash2(int k);
  void HashCuHelper(int k);

public:
  cuckooHash();
  void HashCu(int k);
  void printTables();
};

int main (){
  cuckooHash idk;
  vector<int> ranarr;
  int tempvar = 0;
  for (int i = 0; i < 100; i++){
    tempvar = rand() % 100 + 1;
    ranarr.push_back(tempvar);
  }
  for (int i = 0; i < ranarr.size(); i++){
    int temp = ranarr[i];
    cout << "======== Adding: " << temp << endl;
    idk.HashCu(temp);
    idk.printTables();
  }
}

cuckooHash::cuckooHash(){
  M = 10;
  count = 0;
  tableOne = new int[M];
  tableTwo = new int[M];

  for (int i = 0; i < M; i++){
    tableOne[i] = -1;
    tableTwo[i] = -1;
  }
}

int cuckooHash::hash1(int k){
  return k % M;
}

int cuckooHash::hash2(int k){
  int temp = floor(k / M);
  return temp % M;
}
void cuckooHash::HashCu(int k){
  list.push_back(0);
  list.push_back(0);
  list.push_back(0);
  list.push_back(k);
  // cout << "The size of the list is " << list.size() << endl;
  int loc = (list.size()) - 3;
  cout << "THE LOCATION IS " << loc << endl;
  cout << "THE NUMBER IS " << k << " AND THE REPEAT IS " << list.at(3) << endl;
  if (k == list.at(loc)){
    return;
  }
  if (count >= M){
    M = M*2;
    newTableOne = new int[M];
    newTableTwo = new int[M];
    for (int i = 0; i < M/2; i++){
      newTableOne[i] = tableOne[i];
      newTableTwo[i] = tableTwo[i];
    }
    for (int j = (M/2)+1; j < M; j++){
      newTableOne[j] = -1;
      newTableTwo[j] = -1;
    }

    delete[] tableOne;
    delete[] tableTwo;
    tableOne = newTableOne;
    tableTwo = newTableTwo;
    count = 0;
    cout << "Resizing the table from " << M/2 << " to " << M << endl;
  }
  HashCuHelper(k);
}

void cuckooHash::HashCuHelper(int k){
  int indexOne = hash1(k);
  // cout << "1. Attempting to add " << k << " at " << indexOne << endl;
  if(tableOne[indexOne] == -1){
    tableOne[indexOne] = k;
    // cout << "1. Added " << k << " at " << indexOne << endl;
  }
  else {
    int tempOne = tableOne[indexOne];
    tableOne[indexOne] = k;
    int moveTableTwo = hash2(tempOne);
    // cout << "2. Attempting to add " << tempOne << " at " << moveTableTwo << endl;
    if (tableTwo[moveTableTwo] == -1){
      tableTwo[moveTableTwo] = tempOne;
      // cout << "2. Added " << tempOne << " at " << moveTableTwo << endl;
    }
    else{
      int tempTwo = tableTwo[moveTableTwo];
      tableTwo[moveTableTwo] = tempOne;
      count++;
      // printTables();
      // cout << "The count is " << count << " and M is " << M << endl;
      HashCu(tempTwo);
    }
  }
}


void cuckooHash::printTables() {
  cout << "| ";
	for (int i=0; i<M; i++)
		cout << tableOne[i] << " | ";
	cout << endl;
  cout << "| ";
  for (int i=0; i<M; i++)
    cout << tableTwo[i] << " | ";
  cout << endl;
}

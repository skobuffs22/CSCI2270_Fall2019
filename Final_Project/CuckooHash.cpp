#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class cuckooHash {
	private:
		int M;
	  int* tableOne;
	  int* tableTwo;
		int Cuhash1(int k);
		int Cuhash2(int k);
		int numLoop = 0;

	public:
		cuckooHash();
		~cuckooHash();
		void hash(int k);
		bool lookup(int k);
		void deleteItem(int k);
		void printTables();
		void rehash();
		double lf();
		double countFilled();
};

// Constructor
cuckooHash::cuckooHash(){
	M = 10009;
	tableOne = new int[M];
	tableTwo = new int[M];

	for(int i=0; i<M; i++){
    tableOne[i] = -1;
  }
  for(int i=0; i<M; i++){
    tableTwo[i] = -1;
  }
}

// Destructor
cuckooHash::~cuckooHash(){
	delete[] tableOne;
	delete[] tableTwo;
}

// First hash function (gets hash key)
int cuckooHash::Cuhash1(int k){
	return k % M;
}

// Second hash function (gets hash key)
int cuckooHash::Cuhash2(int k){
  int hash = floor(k / M);
  return hash % M;
}

// Function call to hash an element
void cuckooHash::hash(int k){
  int indexOne = Cuhash1(k);
  int indexTwo = Cuhash2(k);
	int check = indexOne;
	bool success;

  if (tableOne[indexOne] == -1){
    tableOne[indexOne] = k;
		success = true;
  }
  else if(tableTwo[indexTwo] == -1){
  	tableTwo[indexTwo] = k;
		success = true;
  }
  else{
			int replaceOne = Cuhash2(tableOne[indexOne]);
      int replaceTwo = -1;
      int temp = -1;
      int tempTwo = -1;

      temp = tableTwo[replaceOne];
      tableTwo[replaceOne] = tableOne[indexOne];
      tableOne[indexOne] = k;

      if (temp == -1){
        success = true;
      }
			if (success!= true){
      	replaceTwo = Cuhash1(temp);
      	tempTwo = tableOne[replaceTwo];
      	tableOne[replaceTwo] = temp;
			}
			if (tempTwo == -1){
					success == true;
			}
			if(!success){
				numLoop++;
				if (numLoop > M*2){
					rehash();
				}
				hash(tempTwo);
				}
		}
}

// Searches for an element in the hash tables
bool cuckooHash::lookup(int k){
  int indexOne = Cuhash1(k);
  int indexTwo = Cuhash2(k);
  if(tableOne[indexOne] == k){
    return true;
  }
  else if(tableTwo[indexTwo] == k){
    return true;
  }
  else{
  	return false;
	}
}

// Deletes an element from the hash tables
void cuckooHash::deleteItem(int k){
	int indexOne = Cuhash1(k);
  int indexTwo = Cuhash2(k);
  if(tableOne[indexOne] == k){
    tableOne[indexOne] = -1;
  }
  else if(tableTwo[indexTwo] == k){
    tableTwo[indexTwo] == -1;
  }
}

// Prints the tables (if needed)
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

// Rehashes
void cuckooHash::rehash(){
	int orig = M;
	M = M*2;
	int* biggerTableOne = new int[M];
	int* biggerTableTwo = new int[M];
	int* biggerTableOne2 = new int[M];
	int* biggerTableTwo2 = new int[M];

	for(int i=0; i<M; i++){
				biggerTableOne[i] = -1;
				biggerTableOne2[i] = -1;
			}
	for(int i=0; i<M; i++){
				biggerTableTwo[i] = -1;
				biggerTableTwo2[i] = -1;
			}
	for (int i = 0; i<orig; i++)
			{
				biggerTableOne[i] = tableOne[i];
				biggerTableTwo[i] = tableTwo[i];
			}
	delete tableOne;
	delete tableTwo;

	tableOne = biggerTableOne2;
	tableTwo = biggerTableTwo2;

	for (int i = 0; i<orig; i++){
				hash(biggerTableOne[i]);
				hash(biggerTableTwo[i]);
			}
	delete biggerTableOne;
	delete biggerTableTwo;
}

// Calculating load factor
double cuckooHash::lf(){
	double filled = countFilled();
	double temp = (filled / M);
	return temp;
}

// Couting up the number of times the hash function was used
double cuckooHash::countFilled(){
	double count = 0;
	for (int i = 0; i < M; i++){
		if (tableOne[i] > 0){
			count++;
		}
	}
	for (int i = 0; i < M; i++){
		if (tableTwo[i] > 0){
			count++;
		}
	}
	return count;
}

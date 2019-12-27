#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class HashTableLP {
private:
	int M;
	int* table;
	int count = 0;
	int LPhash1(int k);
	int LPhash2(int k);

public:
	HashTableLP();
	~HashTableLP();
	int linearProbe(int k);
	void Hash1LP(int k);
	void Hash2LP(int k);
	int searchLP(int k);
	int deleteLP(int k);
	void printTable();
	double lf();
	double countFilled();
	int returnLPCount();
};

// Constructor
HashTableLP::HashTableLP(){
	M =  10009;
	table = new int[M];
	for (int i=0; i<M; i++)
		table[i] = -1;
}

// Destructor
HashTableLP::~HashTableLP(){
	delete [] table;
}

// First hash function (gets hash key)
int HashTableLP::LPhash1(int k) {
	return k % M;
}

// Second hash function (gets hash key)
int HashTableLP::LPhash2(int k) {
	int temp = floor(k / M);
	return temp % M;
}

// Linear probe collision resolution
int HashTableLP::linearProbe(int index){
	for (int i = index + 1; i != index; i++) {
		if (i >= M) {
			i = -1;
			continue;
		}
		if (table[i] == -1) return i;
	}
	return -1;
}

// Function call to hash using first hash function
void HashTableLP::Hash1LP(int k){
	int index = LPhash1(k);
	if (table[index] >= 0){
		index = linearProbe(index);
		count++;
	}
	if (index >= 0)	{
		table[index] = k;
	}
}

// Function call to hash using second hash function
void HashTableLP::Hash2LP(int k){
	int index = LPhash2(k);
	if (table[index] >= 0){
		index = linearProbe(index);
	}
	if (index >= 0)	{
		table[index] = k;
	}
}

// Searching hash table
int HashTableLP::searchLP(int k){
	for (int i = 0; i < M; i++){
		if (table[i] == k){
			return i;
		}
	}
	return 0;
}

// Deleting an element from the hash function
int HashTableLP::deleteLP(int k){
	int index = searchLP(k);
	table [index] = -1;
	return 0;
}

// Calculating load factor
double HashTableLP::lf(){
	double filled = countFilled();
	double temp = (filled / M);
	return temp;
}

// Couting up the number of times the hash function was used
double HashTableLP::countFilled(){
	double count = 0;
	for (int i = 0; i < M; i++){
		if (table[i] > 0){
			count++;
		}
	}
	return count;
}

// Prints table (if needed)
void HashTableLP::printTable() {
  cout << "| ";
	for (int i=0; i<M; i++)
		cout << table[i] << " | ";
	cout << endl;
}

// Returns number of times linear probe was used
int HashTableLP::returnLPCount(){
	return count;
}

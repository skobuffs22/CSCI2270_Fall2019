/* =====================  CSCI 2270 - DATA STRUCTURES PROJECT  ===================== */
/* Written by:  Madisen Purifoy-Frie (SID: 107833596)
                Trevor Green         (SID: 106079583)                                */

/* This code implements different collision resolutions with hash tables to assess
                  the time-efficency and what they can be used for.                  */

/* ================================================================================= */

// Including all of the files needed for implementing the methods
#include "LinearProbe.cpp"
#include "BST.cpp"
#include "LinkedList.cpp"
#include "CuckooHash.cpp"

// Importing different toolboxes
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

// Calling the menues
void displayMainMenu();
void displayMenu1();


int main(int argc, char* argv[]){
  // Accessing the files
	HashTableLP LProbe;
	HashTableLL LinkedL;
	BinarySearchTreeHT BiST;
  cuckooHash CuckooH;

  // Creating a vector of random numbers to insert, search, and delete
  vector<int> ranarr;
  int tempvar = 0;
  for (int i = 0; i < 100; i++){
    tempvar = rand() % 10000 + 1000;
    ranarr.push_back(tempvar);
  }

	int mainNumSel = 0;
	int numSelect = 0;
  // Allowing the user to choose which data set to use
	while (mainNumSel != 3){
		displayMainMenu();
		numSelect = 0;
		cout << "# ";
		cin >> mainNumSel;
		if (mainNumSel == 1 || mainNumSel == 2){
      ifstream datafile;
      string numarr;
      vector<int> arr;
      // If the user chooses 1, dataSetA is opened and processed
      if (mainNumSel == 1){
        datafile.open("dataSetA.csv");
        while (getline(datafile, numarr, ',')){
          int temp = stoi(numarr);
          arr.push_back(temp);
        }
      }
      // If the user chooses 2, dataSetB is opened and processed
      if (mainNumSel == 2){
        datafile.open("dataSetC.csv");
        while (getline(datafile, numarr, ',')){
          int temp = stoi(numarr);
          arr.push_back(temp);
        }
      }
      datafile.close();

      // Allowing the user to choose which collision method
			while (numSelect != 5){
				displayMenu1();
				cout << "# ";
				cin >> numSelect;
        // Establishing the load factors to perform tasks at
        double lfarr[6] = {0.1, 0.2, 0.5, 0.7, 0.9, 1.0};

        // If the user chooses 1, the linear probe file is used
				if (numSelect == 1){
          // Prealocatting variables
          int tempins, intoarr;
          double execTime, startTime, endTime, lftemp;
          double timemat[3];
          int count = 0;
          double loadf = 0;
          for (int i = 0; i < 6; i++){
            lftemp = lfarr[i];
            // Running until the different load factors are met
            while (loadf < lftemp){
                loadf = LProbe.lf();
                intoarr = arr[count];
                LProbe.Hash1LP(intoarr);
                count++;
            }
            // Insert 100 elements using Hash1
            startTime = clock();
            for (int j = 0; j < ranarr.size(); j++){
              tempins = ranarr[j];
              LProbe.Hash1LP(tempins);
            }
            endTime = clock();
            execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
            timemat[0] = execTime/100;

            // Insert 100 elements using Hash2
            startTime = clock();
            for (int j = 0; j < ranarr.size(); j++){
              tempins = ranarr[j];
              LProbe.Hash2LP(tempins);
            }
            endTime = clock();
            execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
            timemat[1] = execTime/100;

            // Search for 100 elements
            startTime = clock();
            for (int j = 0; j < ranarr.size(); j++){
              tempins = ranarr[j];
              LProbe.searchLP(tempins);
            }
            endTime = clock();
            execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
            timemat[2] = execTime/100;

            // Delete 100 elements
            startTime = clock();
            for (int j = 0; j < ranarr.size(); j++){
              tempins = ranarr[j];
              LProbe.deleteLP(tempins);
            }
            endTime = clock();
            execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
            timemat[3] = execTime/100;

            // Printing out the results for the time
            cout << "=======================Using a load factor of "<< lfarr[i] << "=========================" << endl;
            cout << "The average time for inserting 100 elements (w/ Hash1) is : " << timemat[0] << " seconds" << endl;
            cout << "The average time for inserting 100 elements (w/ Hash2) is : " << timemat[1] << " seconds" << endl;
            cout << "The average time for search 100 elements is               : " << timemat[2] << " seconds" << endl;
            cout << "The average time for delete 100 elements is               : " << timemat[3] << " seconds" << endl;
            cout << endl;
          }
          // Returning the amount of times the linear probe function was utilized
          int numberLP = LProbe.returnLPCount();
          cout << "The collision mechanism was used " << numberLP << " times" << endl;

        }

        // If the user chooses 2, the linked list file is used
				if (numSelect == 2){
          // Prealocatting variables
          int tempins, intoarr;
          double execTime, startTime, endTime, lftemp;
          double timemat[4];
          int count = 0;
          double loadf = 0;
          for (int i = 0; i < 6; i++){
            lftemp = lfarr[i];
            // Running until the different load factors are met
            while (loadf < lftemp){
                loadf = LinkedL.lf();
                intoarr = arr[count];
                LinkedL.Hash1LL(intoarr);
                count++;
            }

            // Insert 100 elements using Hash1
            startTime = clock();
            for (int j = 0; j < ranarr.size(); j++){
              tempins = ranarr[j];
              LinkedL.Hash1LL(tempins);
            }
            endTime = clock();
            execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
            timemat[0] = execTime/100;

            // Insert 100 elements using Hash2
            startTime = clock();
            for (int j = 0; j < ranarr.size(); j++){
              tempins = ranarr[j];
              LinkedL.Hash2LL(tempins);
            }
            endTime = clock();
            execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
            timemat[1] = execTime/100;

            // Search for 100 elements
            startTime = clock();
            for (int j = 0; j < ranarr.size(); j++){
              tempins = ranarr[j];
              LinkedL.LLsearchHT(tempins);
            }
            endTime = clock();
            execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
            timemat[2] = execTime/100;

            // Delete 100 elements
            startTime = clock();
            for (int j = 0; j < ranarr.size(); j++){
              tempins = ranarr[j];
              LinkedL.deleteLL(tempins);
            }
            endTime = clock();
            execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
            timemat[3] = execTime/100;

            // Printing out the results for the time
            cout << "=======================Using a load factor of "<< lfarr[i] << "=========================" << endl;
            cout << "The average time for inserting 100 elements (w/ Hash1) is : " << timemat[0] << " seconds" << endl;
            cout << "The average time for inserting 100 elements (w/ Hash2) is : " << timemat[1] << " seconds" << endl;
            cout << "The average time for search 100 elements is               : " << timemat[2] << " seconds" << endl;
            cout << "The average time for delete 100 elements is               : " << timemat[3] << " seconds" << endl;
            cout << endl;
          }
          // Returning the amount of times the linked list function was utilized
          int numberLL = LinkedL.returnLLCount();
          cout << "The collision mechanism was used " << numberLL << " times" << endl;
				}

        // If the user chooses 3, the binary search tree file is used
				if (numSelect == 3){
          // Prealocatting variables
          int tempins, intoarr;
          double execTime, startTime, endTime, lftemp;
          double timemat[4];
          double count = 0;
          double loadf = 0;
          for (int i = 0; i < 6; i++){
            lftemp = lfarr[i];
            // Running until the different load factors are met
            while (loadf < lftemp){
              loadf = count/10009;
              intoarr = arr[count];
              BiST.Hash1BST(intoarr);
              count++;
            }

            // Insert 100 elements using Hash1
            startTime = clock();
            for (int j = 0; j < ranarr.size(); j++){
              tempins = ranarr[j];
              BiST.Hash1BST(tempins);
            }
            endTime = clock();
            execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
            timemat[0] = execTime/100;

            // Insert 100 elements using Hash2
            startTime = clock();
            for (int j = 0; j < ranarr.size(); j++){
              tempins = ranarr[j];
              BiST.Hash2BST(tempins);
            }
            endTime = clock();
            execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
            timemat[1] = execTime/100;

            // Search for 100 elements
            startTime = clock();
            for (int j = 0; j < ranarr.size(); j++){
              tempins = ranarr[j];
              BiST.searchHT(tempins);
            }
            endTime = clock();
            execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
            timemat[2] = execTime/100;

            // Delete 100 elements
            int idk = 0;
            startTime = clock();
            for (int j = 0; j < ranarr.size(); j++){
              tempins = ranarr[j];
              BiST.deleteNum(tempins);
            }
            endTime = clock();
            execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
            timemat[3] = execTime/100;

            // Printing out the results for the time
            cout << "=======================Using a load factor of "<< lfarr[i] << "=========================" << endl;
            cout << "The average time for inserting 100 elements (w/ Hash1) is : " << timemat[0] << " seconds" << endl;
            cout << "The average time for inserting 100 elements (w/ Hash2) is : " << timemat[1] << " seconds" << endl;
            cout << "The average time for search 100 elements is               : " << timemat[2] << " seconds" << endl;
            cout << "The average time for delete 100 elements is               : " << timemat[3] << " seconds" << endl;
            cout << endl;
          }
          // Returning the amount of times the linked list function was utilized
          int numberBST = BiST.returnLPCount();
          cout << "The collision mechanism was used " << numberBST << " times" << endl;
        }

        // If the user chooses 4, the cuckoo hash file is used
				if (numSelect == 4){
          // Prealocatting variables
          int tempins, intoarr;
          double n, lftemp, execTime, startTime, endTime;
          double timemat[3];
          int count = 0;
          double loadf = 0;
          for (int i = 0; i < 6; i++){
            lftemp = lfarr[i];
            // Running until the different load factors are met
            while (loadf < lftemp){
                loadf = CuckooH.lf();
                intoarr = arr[count];
                CuckooH.hash(intoarr);
                count++;
            }

            // Insert 100 elements using Hash1
            startTime = clock();
            for (int j = 0; j < ranarr.size(); j++){
              tempins = ranarr[j];
              CuckooH.hash(tempins);
            }
            endTime = clock();
            execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
            timemat[0] = execTime/100;

            // Search for 100 elements
            startTime = clock();
            for (int j = 0; j < ranarr.size(); j++){
              tempins = ranarr[j];
              CuckooH.lookup(tempins);
            }
            endTime = clock();
            execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
            timemat[1] = execTime/100;

            // Delete 100 elements
            startTime = clock();
            for (int j = 0; j < ranarr.size(); j++){
              tempins = ranarr[j];
              CuckooH.deleteItem(tempins);
            }
            endTime = clock();
            execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
            timemat[2] = execTime/100;

            // Printing out the results for the time
            cout << "=======================Using a load factor of "<< lfarr[i] << "=========================" << endl;
            cout << "The average time for inserting 100 elements (w/ Hash) is  : " << timemat[0] << " seconds" << endl;
            cout << "The average time for search 100 elements is               : " << timemat[1] << " seconds" << endl;
            cout << "The average time for delete 100 elements is               : " << timemat[2] << " seconds" << endl;
            cout << endl;
          }
          // This is where the code would go to check how many times the cuckoo hash double it's table size
				}

        // If the user chooses 5, the program takes the user back to the previous menu
				if (numSelect == 5){
					break;
				}
			}
		}
    // If the user selects 3, the program quits
		if (mainNumSel == 3){
			cout << "===============================================" << endl;
			cout << endl;
			cout << "Quitting the program...." << endl;
			cout << "Quit!" << endl;
		}
	}
	return 0;
}

// First menu the user sees
void displayMainMenu(){
	cout << "===================Main Menu===================" << endl;
  cout << "1. Data Set A" << endl;
  cout << "2. Data Set B" << endl;
  cout << "3. Quit" << endl;
}

// Second menu the user sees
void displayMenu1(){
  cout << "======Implementing the Hash Table Methods======" << endl;
  cout << "1. Hash Data (Linear Probing)" << endl;
  cout << "2. Hash Data (Linked List)" << endl;
	cout << "3. Hash Data (Binary Search Tree)" << endl;
	cout << "4. Hash Data (Cuckoo Hash)" << endl;
  cout << "5. Go back" << endl;
}

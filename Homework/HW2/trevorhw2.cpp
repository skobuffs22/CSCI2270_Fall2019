#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<math.h>
using namespace std;



struct wordItem{
string word;
int count;
};

void getStopWords(const char *ignoreWordFileName, string ignoreWords[]);
bool isStopWord(string word, string ignoreWords[]);
int getTotalNumberNonStopWords(wordItem uniqueWords[], int length);
void arraySort(wordItem uniqueWords[], int length);
void printNext10(wordItem uniqueWords[], int N, int totalNumWords);

int main(int argc, const char *argv[])
{
	string tomSawyer = "";
	string ignoreWordsFile = "";
    int N;

	// if (argc < 4) {
	// 	cout << "Not enough arguments!\n";
	// }
	// else if (argc > 4) {
	// 	cout << "Too many arguments\n";
	// }
	// else {
	// 	tomSawyer = argv[2];
	// 	ignoreWordsFile = argv[3];
	// 	N = stoi(argv[1]);
  // }
		N = 25;
    ifstream fs;
    fs.open("Tom_Sawyer.txt");

    string stopWordList[50];
    string newWord;
    int timesDoubled = 0;

		char ignoreWordFileName[16] = "ignoreWords.txt";
    getStopWords(ignoreWordFileName,stopWordList);

    int maxEntries = 100;
    int numEntries = 0;
    wordItem* uniqueWords = new wordItem[maxEntries];

while(getline(fs, newWord,' ')){
    if(!(isStopWord(newWord,stopWordList))){
        int word = -1;
        for(int i = 0; i<= numEntries; i++){
            if (newWord == uniqueWords[i].word){
                word = i;
                uniqueWords[i].count++;
                break;
            }
        }
        if (word==-1){
            wordItem newarrayWord;
            newarrayWord.word = newWord;
            newarrayWord.count = 1;
            uniqueWords[numEntries] = newarrayWord;
            numEntries++;
            if (numEntries == maxEntries){
              timesDoubled++;
              maxEntries = numEntries*2;
              wordItem* biggerArray = new wordItem[maxEntries];
              for (int i=0; i<numEntries; i++){
                biggerArray[i] = uniqueWords[i];
              }
              delete[] uniqueWords;
              uniqueWords = biggerArray;
            }
        }
    }
}
cout << "Array doubled: " << timesDoubled << endl;
cout << "#"<< endl;
cout << "Unique non-common words: "<< numEntries << endl;
cout << "#"<< endl;
int totalWords = getTotalNumberNonStopWords(uniqueWords,numEntries);
cout << "Total non-common words: " << totalWords << endl;
cout << "#" << endl;
arraySort(uniqueWords,numEntries);
cout << "Probability of next 10 words from rank " << N << endl;
cout << "---------------------------------------" << endl;
cout << argv[2]<< endl;
if(argv[2] == "Tom_Sawyer.txt"){
    cout << "here" << endl;
    for(int i = 0; i< numEntries;i++)
        cout << uniqueWords[i].word << endl;
}
printNext10(uniqueWords,N,totalWords);

return 0;
}













void getStopWords(const char *ignoreWordFileName, string ignoreWords[]){
  ifstream fs;
  fs.open(ignoreWordFileName);
  if (fs.fail()){
			cout << "Failed to open " << ignoreWordFileName << endl;
		}
  string newWord;
    for (int i = 0; i<=49; i++){
    getline(fs,newWord);
    ignoreWords[i] = newWord;
    }
}


bool isStopWord(string word, string ignoreWords[]){
    for(int i= 0; i<50 ; i++){
    string comp = ignoreWords[i];
    if (word == comp){
            return 1;
        }
    }
   return 0;

}
int getTotalNumberNonStopWords(wordItem uniqueWords[], int length){
    int total = 0;
    for(int i = 0; i<length; i++)
        total += uniqueWords[i].count;
    return total;
}

void arraySort(wordItem uniqueWords[], int length){
for(int i = 0; i<length; i++)
    {
    for(int k = i+1; k<=(length+1); k++)
      {
        if(uniqueWords[i].count < uniqueWords[k].count)
        {
        swap(uniqueWords[k],uniqueWords[i]);
        }
      }
    }
}

void printNext10(wordItem uniqueWords[], int N, int totalNumWords){
    for (int i = N; i<N+10; i++)
    {
    float probabilityOfOccurrence;
    probabilityOfOccurrence = static_cast<float>(uniqueWords[i].count) / static_cast<float>(totalNumWords);


    cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(4);

    cout << probabilityOfOccurrence << " - " << uniqueWords[i].word << endl;

    }
}


// - ------------------------------------ //
while (getline(tomSawyer, line)){
  if (line == ""){
    continue;
  }
  else {
    stringstream ss(line);
    while (getline (ss, words, ' ')){
      if (isStopWord(words, ignoreWords)){

      }
      else{
        match = false;
        for (int i = 0; i < numOfElement; i++){
          if (words == wordarr[i].word){
            wordarr[i].count += 1;
            match = true;
            break;
          }
        }
        if (!match){
          if (numOfElement == capacity){
            capacity = resize(wordarr, capacity);
            doublearr++;
          }
        }
      }
    }
  }
}

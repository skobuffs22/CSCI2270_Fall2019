# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <iomanip>
# include <cstdlib>
# include <array>
# include <algorithm>

using namespace std;

struct wordItem {
  string word;
  int count;
};

int resize(wordItem *& wordarr, int capacity) {
    wordItem *newarr = new wordItem[capacity*2];
    for (int i = 0; i < capacity; i++) {
        newarr[i].word = wordarr[i].word;
        newarr[i].count = wordarr[i].count;
    }
    delete[] wordarr;
    wordarr = newarr;
    return capacity*2;
}

void addWord(wordItem* wordarr, string word, int* numOfElement) {
	for (int i = 0; i < *numOfElement; ++i) {
		if (wordarr[i].word == word) {
			wordarr[i].count++;
			return;
		}
	}
	wordarr[*numOfElement].word = word;
	wordarr[*numOfElement].count = 1;
	(*numOfElement)++;
	return;
}

void getStopWords(const char *ignoreWordFileName, string ignoreWords[]){
  ifstream stopWords;
  stopWords.open(ignoreWordFileName);
  if (stopWords.is_open ()){
    int temp = 0;
    string words;
    while (getline(stopWords, words)){
      ignoreWords[temp] = words;
      temp ++;
    }
  }
  else {
    cout << "Failed to open " << ignoreWordFileName << endl;
  }
}

bool isStopWord(string word, string ignoreWords[]){
  for (int i = 0; i<50; i++){
    string comp = ignoreWords[i];
    if (word == comp){
      return 1;
    }
  }
  return 0;
}

int getTotalNumberNonStopWords(wordItem uniqueWords[], int length){
  int total = 0;
  for (int i = 0; i<length; i++){
    total += uniqueWords[i].count;
  }
  return total;
}

void arraySort(wordItem uniqueWords[], int length){
    bool sort = false;
    int temp1;
    string temp2;
    while (!sort){
        sort = true;
        for (int i = 0;  i < length-1; i++){
            if (uniqueWords[i].count < uniqueWords[i+1].count){
                temp1 = uniqueWords[i].count;
                temp2 = uniqueWords[i].word;
                uniqueWords[i].count = uniqueWords[i+1].count;
                uniqueWords[i].word = uniqueWords[i+1].word;
                uniqueWords[i+1].count = temp1;
                uniqueWords[i+1].word = temp2;
                sort = false;
            }
        }
    }
}

void printNext10(wordItem wordItemList[], int n, int totalWords){
    cout << setprecision (4) << fixed;
    for (int i = n; i < n+10; i++){
        float prob = (float)wordItemList[i].count / (float)totalWords;
        cout << prob << " - " << wordItemList[i].word << endl;
    }
}


main (int argc, char *argv[]){
    ifstream tomSawyer;
    tomSawyer.open(argv[2]);

  if (!tomSawyer){
    cout << "Could not open file." << endl;
    return 0;
  }

  int capacity = 100;
  int numOfElement = 0;
  int doublearr = 0;
  int total = 0;
  int n = stoi(argv[1]);

  string line;
  string words;

  wordItem* wordarr = new wordItem[capacity];
  string* ignoreWords = new string[50];
  wordItem* uniqueWords = new wordItem[capacity];

  getStopWords(argv[3], ignoreWords);

  while (getline(tomSawyer, line)){
    stringstream ss(line);
    while (getline (ss, words, ' ')){
      if (numOfElement >= capacity){
        capacity = resize(wordarr, capacity);
        doublearr ++;
      }
      words.erase(std::remove(words.begin(), words.end(), '\n'), words.end());

      if (isStopWord(words, ignoreWords) || words == ""){
        continue;
      }
      addWord(wordarr, words, &numOfElement);
      total ++;
    }
  }
  arraySort(wordarr, numOfElement);

  cout << "Array doubled: " << doublearr << endl;
  cout << "#" << endl;
  cout << "Unique non-common words: " << numOfElement << endl;
  cout << "#" << endl;
  cout << "Total non-common words: " << total << endl;
  cout << "#" << endl;
  cout << "Probability of next 10 words from rank " <<  n << endl;
  cout << "---------------------------------------" << endl;
  printNext10 (wordarr, n, total);



  return 0;
}

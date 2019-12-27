# include <iostream>
# include <fstream>
# include <string>
# include <sstream>


using namespace std;

struct Park {
    string parkname;
    string state;
    int area;
};

void addPark(Park parks[], string parkname, string state, int area, int
length){
  Park temp;
  temp.parkname = parkname;
  temp.state = state;
  temp.area = area;
  parks [length] = temp;
  }


void printList(const Park parks[], int length){
  for (int i = 0; i<length; i++){
    Park park = parks[i];
    cout << park.parkname <<" [" << park.state << "] area: "<< park.area << endl;
  }
}

int main (int argc, char *argv[]){
  fstream parkFile, outputFile;
  parkFile.open (argv[1], ios::in);
  outputFile.open (argv[2], ios::out);
  int minArea = stoi (argv[3]);

  int count = sizeof (parkFile);
  Park parks[count];
  string park, state, area, line;
  int length = 0;
  while (getline (parkFile, line)){
      stringstream ss (line);
      getline(ss, park, ',');
      getline(ss, state, ',');
      getline(ss, area, ',');
      addPark(parks, park, state, stoi(area), length);
      length ++;
    }
  printList(parks, length);
  parkFile.close();
  for(int i = 0; i<length; i++){
    if (parks[i].area > minArea){
      outputFile <<  parks[i].parkname << "," << parks[i].state << "," << parks[i].area << endl;
    }
  }
  outputFile.close();
}

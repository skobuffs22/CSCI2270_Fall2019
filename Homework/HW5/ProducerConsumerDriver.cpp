#include "ProducerConsumer.hpp"
#include <iostream>
using namespace std;

ProducerConsumer::ProducerConsumer(){
   queueFront = 0;
   queueEnd = 0;
}

bool ProducerConsumer::isEmpty(){
	if (counter == 0){
		return true;
	}
	return false;
}

bool ProducerConsumer::isFull(){
	if (SIZE == counter){
		return true;
	}
	return false;
}
void ProducerConsumer::enqueue(std::string item){
	if (!isFull()){
		queue[queueEnd] = item;
		queueEnd++;
		queueEnd %= SIZE;
		counter++;
	}
	else{
		cout << "Queue full, cannot add new item" << endl;
	}
}

void ProducerConsumer::dequeue(){
	if (!isEmpty()){
		queueFront ++;
		queueFront %= SIZE;
		counter--;
	}
	else{
		cout << "Queue empty, cannot dequeue an item" << endl;
	}
}

string ProducerConsumer::peek(){
	if (!isEmpty()){
		return queue[queueFront];
	}
	cout << "Queue empty, cannot peek" << endl;
	return "";
}

int ProducerConsumer::queueSize(){
	return counter;
}


int ProducerConsumer::getQueueFront() { return queueFront; }
int ProducerConsumer::getQueueEnd() { return queueEnd; }
string* ProducerConsumer::getQueue() { return queue; }

void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
  cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}


int main(int argc, char const *argv[])
{
	int numSelect, num;
	ProducerConsumer pc;
	while (numSelect != 3){
		menu();
		cin >> numSelect;
		if (numSelect < 0 || numSelect > 4){
			cout << "This number is not an option!" << endl;
		}
		if (numSelect == 1) {
			int prod;
			cout << "Enter the number of items to be produced: " << endl;
			cin >> prod;
			for (int i = 1; i<prod+1; i++){
				string userProd;
				cout << "Item" << i << ":" << endl;
				cin >> userProd;
				pc.enqueue(userProd);

			}
		}
		if (numSelect == 2){
			int cons, size;
			string peek;
			cout << "Enter the number of items to be consumed: " << endl;
			cin >> cons;
			size = pc.queueSize();
			if (size < cons){
				for (int j = 0; j<size; j++){
					peek = pc.peek();
					cout << "Consumed: " << peek << endl;
					pc.dequeue();
				}
				cout << "No more items to consume from queue" << endl;
			}
			else {
				for (int j = 0; j<cons; j++){
					peek = pc.peek();
					cout << "Consumed: " << peek << endl;
					pc.dequeue();
				}
			}
		}
	}
	num = pc.queueSize();
	cout << "Number of items in the queue:" << num << endl;
}

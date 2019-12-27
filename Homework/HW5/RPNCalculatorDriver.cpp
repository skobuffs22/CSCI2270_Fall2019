#include "RPNCalculator.hpp"
#include <iostream>

using namespace std;

 RPNCalculator::RPNCalculator()
 {
   stackHead = NULL;
 }

 RPNCalculator::~RPNCalculator(){
   while(!isEmpty()){
       pop();
   }
   stackHead = NULL;
}


bool isNumber(string s)
{
    if(s.size() == 1 && s == "-") return false;
    else if(s.size() > 1 && s[0] == '-') s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++)
    {
      if(!isdigit(s[i]) && s[i] != '.') return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}

bool RPNCalculator::isEmpty(){
  if (stackHead == NULL){
    return true;
  }
  else {
    return false;
  }
}

void RPNCalculator::push(float num){
  Operand* temp = new Operand;
  temp -> number = num;
  if (isEmpty()){
      stackHead = temp;
      temp -> next = NULL;
      return;
  }
  else{
      temp -> next = stackHead;
      stackHead = temp;
  }
}

void RPNCalculator::pop(){
  Operand* temp = stackHead;
  if (isEmpty()){
    cout << "Stack empty, cannot pop an item." << endl;
    return;
  }
  else{
    stackHead = stackHead -> next;
    delete temp;
  }
}

Operand* RPNCalculator::peek(){
  if (isEmpty()){
    cout << "Stack empty, cannot peek." << endl;
    return NULL;
  }
  else{
    return stackHead;
  }
}

bool RPNCalculator::compute(std::string symbol){
  float num1, num2, num3;
  if (isEmpty()){
      cout << "err: not enough operands" << endl;
      return false;
  }
  else if (stackHead -> next == NULL){
      cout << "err: not enough operands" << endl;
  }
  else{
    if (symbol == "+"){
      num1 = peek() -> number;
      pop();
      num2 = peek() -> number;
      pop();
      num3 = num1 + num2;
      push (num3);
      return true;
    }
    else if (symbol == "*"){
      num1 = peek() -> number;
      pop();
      num2 = peek() -> number;
      pop();
      num3 = num1 * num2;
      push (num3);
      return true;
    }
    else{
      cout << "err: invalid operation" << endl;
      return false;
    }
  }
}

Operand* getStackHead() { return stackHead; }


int main(){
  cout << "Enter the operators and operands ('+', '*') in a postfix format" << endl;
  string oper = "0";
  RPNCalculator calc;

  while(oper != "="){
    cout << "#> ";
    cin >> oper;
    if (oper != "="){
      bool tf, var;
      tf = isNumber(oper);
      if (tf == true){
        float operand;
        operand = stof (oper);
        calc.push (operand);
      }
      else if (tf == false){
        var = calc.compute(oper);
      }
    }
  }
  if (calc.isEmpty()){
      cout << "No operands: Nothing to evaluate";
      return 0;
  }
  if (calc.getStackHead()-> next != NULL){
    cout << "Invalid expression";
    return 0;
  }
  else{
    cout << calc.peek()-> number;
    return 0;
  }
}

#ifndef __POSTFIX_H__
#define __POSTFIX_H__
#define SEPARATOR '|'

#include <string>
#include <map>
#include "stack.h"

using namespace std;

class TPostfix
{
  string infix;
  string postfix;
  bool isBreak = false;

  string signs = "()+-/*";

  map <string, int> operations = { { "+",1 },{ "-",2 },{ "*",3 },{ "/",4 },{ "sin",5 },{ "cos",6 } };

  map <string, int> priority = { { "+",1 },{ "-",1 },{ "*",2 },{ "/",2 },{ "(",0 },{ ")",0 },{ "sin",3 },{ "cos",3 } };

  TStack<string> stack = TStack<string>(50);

  bool isSign(char c);

  bool isOperation(string str);

  void preCalculate();

public:

	void addSpaces();

  TPostfix()
  {
    postfix = "";
  }
  void SetInfix(string input) {
	  infix = input;
  }
  string GetInfix() { return infix; }
  string GetPostfix() { return postfix; }
  string ToPostfix();
  double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif

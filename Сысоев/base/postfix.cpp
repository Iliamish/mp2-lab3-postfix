#include "postfix.h"
#include "stack.h"
#include <sstream>
#include <iostream>

bool TPostfix::isSign(char c)
{
	for (int i = 0; i < signs.length(); i++)
	{
		if (signs[i] == c)
			return true;
	}
	return false;
}


bool TPostfix::isOperation(string str)
{
	if (priority.find(str) != priority.end())
		return true;
	return false;
}

void TPostfix::preCalculate()
{
	while (postfix.find(SEPARATOR) != std::string::npos)
	{
		auto iter = postfix.find(SEPARATOR);
		postfix.erase(postfix.find(SEPARATOR),1);
		postfix.insert(iter, " ");
	}
}


void TPostfix::addSpaces()
{
	for (int i = 0; i < infix.length(); i++)
	{
		if (isSign(infix[i])) {
			if (i > 0 && infix[i - 1] != ' ')
				infix.insert(i++, " ");
			if (i < infix.length() - 1 && infix[i + 1] != ' ') {
				infix.insert(i + 1, " ");
				i++;
			}
		}
	}
}

void TPostfix::addNullBeforeMinus()
{
	if(infix[0] == '-')
		infix.insert(0, "0");
	for (int i = 1; i < infix.length(); i++) {
		if (infix[i] == '-' && infix[i-1] == '(') {
			infix.insert(i - 1, "0");
		}
	}
}

void TPostfix::deleteSpaces()
{
	while (postfix.find(' ') != std::string::npos)
	{
		auto iter = postfix.find(' ');
		postfix.erase(postfix.find(' '), 1);
	}
}



string TPostfix::ToPostfix()
{
	string word;
	string lastWord = "";
	for (stringstream is(infix); is >> word;)
	{
		if (!isOperation(word)){
			if (!isOperation(lastWord) && lastWord!="")
				throw 0;
			postfix += word + SEPARATOR;
		}
		else
		{
			if ((isOperation(lastWord) && priority[word] != 0 && priority[lastWord] != 0) || 
				(word != "(" && word != "-" && isSign(word[0]) && lastWord == "" ) ||
				(lastWord == "(" && isOperation(word) && word != "-") ||
				(word == ")" && isOperation(lastWord)))
				throw 0;
			if (postfix != "") {
				if (stack.empty())
					stack.push(word);
				else {
					while (!stack.empty()) {
						if (priority[stack.back()] >= priority[word] && word != "(") {
							if (priority[stack.back()] == 0 && priority[word] == 0) {
								stack.pop();
								break;
							}
							else {
								postfix += stack.back() + SEPARATOR;
								stack.pop();
							}
						}
						else {
							break;
						}
					}
					if (word != ")") {
						stack.push(word);
					}
				}
			}
			else
				if (word == "-")
					postfix += word;
				else
					stack.push(word);
		}
		lastWord = word;
	}
	while (!stack.empty()) {
		postfix += stack.back() + SEPARATOR;
		stack.pop();
	}
	return postfix;
}

double TPostfix::Calculate()
{
	int variable;

	TStack <double> variableStack = TStack<double>(50);
	if (SEPARATOR != " ") {
		preCalculate();
	}
	string word;
	for (stringstream is(postfix); is >> word;)
	{
		if(!isOperation(word))
			try {
				variableStack.push(stoi(word));
			}
			catch (std::invalid_argument& ia) {
				if (variables.find(word) == variables.end()) {
					cout << "Введите значение для переменной " << word << " = ";
					cin >> variable;
					variables.insert({ word, variable });
				}
				else
				{
					variable = variables[word];
				}
				variableStack.push(variable);
			}
		else {
			float back = variableStack.back();
			variableStack.pop();
			float preback;
			if (!variableStack.empty()) {
				preback = variableStack.back();
				variableStack.pop();
			}
			switch (operations[word])
			{
			case 1:
			{
				variableStack.push(back + preback);
				break;
			}
			case 2:
			{
				
				variableStack.push(preback - back);
				break;
			}
			case 3:
			{
				variableStack.push(back * preback);
				break;
			}
			case 4:
			{
				variableStack.push(preback / back);
				break;
			}
			case 5:
			{
				if (!variableStack.empty())
					variableStack.push(preback);
				variableStack.push(sin(back));
				break;
			}
			case 6:
			{
				if (!variableStack.empty()) 
					variableStack.push(preback);
				variableStack.push(cos(back));
				break;
			}
			case 7:
			{
				variableStack.push(pow(preback,back));
				break;
			}
			case 8:
			{
				if (!variableStack.empty())
					variableStack.push(preback);
				variableStack.push(tan(back));
				break;
			}
			case 9:
			{
				if (!variableStack.empty())
					variableStack.push(preback);
				variableStack.push(log(back));
				break;
			}
			}
		}
	}
	return variableStack.back();
}

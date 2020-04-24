#pragma once

#include <string>
#include "Stack.h"

using namespace std;

class Calculator
{
private:
	string infix;
public:
	Calculator();
	Calculator(string s);
	void setExpr(string s) { infix = s; }
	string getExpr() { return infix; }
	string postfix(); //convert infix to postfix
	int eval(string);
};

Calculator::Calculator()
{
	infix = "";
}

Calculator::Calculator(string s)
{
	infix = s;
}

string Calculator::postfix() //convert infix to postfix
{
	Stack<char> myStack;
	string postfix;
	int open = 0; //open parentheses
	if (infix[0] == '(')
	{
		
	}
	else if (infix[0] == '-')
	{

	}
	else if (!(infix[0] > 47 && infix[0] < 58)) // if the first input is not a number
	{
		return "Invalid Expression!";
	}
	
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == ' ' || infix[i] == '	')
		{
			continue;
		}
		if (infix[i] > 47 && infix[i] < 58) //if it is a number
		{
			int j = 0;
			while (infix[i + j] > 47 && infix[i + j] < 58)// check to see how big the number is
			{
				postfix += infix[i + j];
				j++;
			}
			j--;
			i += j;
			postfix += " "; //make a space for cout
		}
		else if (infix[i] == '+' || infix[i] == '-') // plus and minus
		{
			if (myStack.empty() || myStack.top() == '(')
			{
				myStack.push(infix[i]);
			}
			else if (myStack.top() == '+' || myStack.top() == '-' || myStack.top() == '*' || myStack.top() == '/' || myStack.top() == '^')
			{
				postfix += myStack.top();
				postfix += " ";
				myStack.pop();
				myStack.push(infix[i]);
			}
		}
		else if (infix[i] == '*' || infix[i] == '/') // multiply and divide
		{
			if (myStack.empty() || myStack.top() == '(')
			{
				myStack.push(infix[i]);
				continue;
			}
			if (myStack.top() == '+' || myStack.top() == '-')
			{
				myStack.push(infix[i]);
			}
			else if (myStack.top() == '*' || myStack.top() == '/' || myStack.top() == '^')
			{
				postfix += myStack.top();
				postfix += " ";
				myStack.pop();
				myStack.push(infix[i]);
				//if (myStack.top() == '+' || myStack.top() == '-')
				//{
				//	myStack.push(infix[i]);
				//}
				//else if (myStack.top() == '*' || myStack.top() == '/' || myStack.top() == '^')
				//{
				//	postfix += infix[i];
				//	postfix += " ";
				//}
			}
		}
		else if (infix[i] == '(' || infix[i] == ')') // parentheses
		{
			if (infix[i] == '(')
			{
				myStack.push(infix[i]);
				open++;
			}
			else if (infix[i] == ')')
			{
				if (open == 0)
				{
					return "Invalid Expression!";
				}
				while (!myStack.empty())
				{
					if (myStack.top() == '(')
					{
						open--;
						myStack.pop();
						break;
					}
					else
					{
						postfix += myStack.top();
						postfix += " ";
						myStack.pop();
					}
				}
			}
		}
		else if (infix[i] == '^') // to the power
		{
			myStack.push(infix[i]);
		}
		else
		{
			return "Invalid Expression!(not a number or operation)";
		}
	}
	if (open != 0)
	{
		return "Invalid Expression!(expected another parentheses)";
	}
	while (!myStack.empty())
	{
		postfix += myStack.top();
		postfix += " ";
		myStack.pop();
	}
	return postfix;
}

int Calculator::eval(string postfix)
{
	Stack<int> myStack;
	int result = 0;
	for (int i = 0; i < postfix.size(); i++)
	{
		if (postfix[i] == ' ' || postfix[i] == '	')
		{
			continue;
		}
		if (postfix[i] > 47 && postfix[i] < 58) // if it is a number
		{
			if (postfix[i + 1] == ' ' || postfix[i + 1] == '	')
			{
				myStack.push(postfix[i] - 48);
				continue;
			}
			else if (postfix[i + 1] > 47 && postfix[i + 1] < 58) //if it is a number
			{
				int j = 0;
				string temp = "";
				while (postfix[i + j] > 47 && postfix[i + j] < 58)// check to see how big the number is
				{
					temp += postfix[i + j];
					j++;
				}
				myStack.push(stoi(temp));
				j--;
				i += j;
			}
		}
		else if (postfix[i] == '+')
		{
			int total1 = 0;
			total1 += myStack.top();
			myStack.pop();
			if (!myStack.empty())
			{
				total1 += myStack.top();
				myStack.pop();
			}
			myStack.push(total1);
		}
		else if (postfix[i] == '-')
		{
			int total1 = 0;
			total1 -= myStack.top();
			myStack.pop();
			if (!myStack.empty())
			{
				total1 += myStack.top();
				myStack.pop();
			}
			myStack.push(total1);
		}
		else if (postfix[i] == '*')
		{
			int total1 = 0;
			total1 = myStack.top();
			myStack.pop();
			total1 *= myStack.top();
			myStack.pop();
			myStack.push(total1);
		}
		else if (postfix[i] == '/')
		{
			int total1 = 0;
			total1 = myStack.top();
			myStack.pop();
			total1 = myStack.top() / total1;
			myStack.pop();
			myStack.push(total1);
		}
		else if (postfix[i] == '^')
		{
			int total1 = 0;
			int total2 = 0;
			total1 = myStack.top();
			myStack.pop();
			total2 = pow(myStack.top(), total1);
			myStack.pop();
			myStack.push(total2);
		}
	}
	result = myStack.top();
	return result;
}
#include <iostream>
#include "Calculator.h"
#include "Stack.h"
#include <string>

using namespace std;

int main()
{
	cout << "Welcome to JJ's Calculator!" << endl;
	cout << "Enter 0 to exit the program." << endl << endl;
	string inF = "";
	string postF = "";
	int result = 0;
	Calculator expression(inF);

	while (expression.getExpr() != "0")
	{
		//get infix
		cout << "Enter an expression: ";
		getline(cin, inF);
		expression.setExpr(inF);
		if (inF == "0")
		{
			break;
		}

		postF = expression.postfix();
		if (postF[0] == 'I')
		{
			cout << postF << endl << endl;
			continue;
		}
		//output postfix
		cout << "Postfix expression: ";
		cout << postF << endl;

		//output eval
		cout << "Result: ";
		result = expression.eval(postF);
		cout << result << endl << endl;
	}
	
	cout << "Thanks for using my calculator." << endl;
	
	return 0;
}


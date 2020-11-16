#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string>
using namespace std;



class Compiler {
public:
	int Keyword(char buffer[]);
	int Operator(char buffer);
	int Separators(char buffer);
	int isNum(char buffer);
	void lexer(string fileName);
	void outputCode(string filename);

	//stack implementation
	char stack[100];
	int top;
	void initializeStack() {
		stack[0] = '$';
		top = 0;
	}
	bool isEmpty() {
		if (stack[top] == '$') {
			return true;
		}
		else
			return false;
	}
	void push(char a) {
		++top;
		stack[top] = a;
	}
	void display(char stack[]) {
		if (isEmpty()) {
			cout << "Stack is Empty" << endl << endl;
		}
		else
		{
			cout << "Stack Content: ";
			for (int i = top; i >= 0; i--) {
				cout << stack[i];
			}
			cout << endl << endl;
		}
	}
	void pop() {
		int temp;
		if (isEmpty()) {
			cout << "Stack is Empty" << endl << endl;
			return;
		}
		temp = stack[top];
		top--;
		cout << temp << " has been popped" << endl << endl;
		
	}

	void stackParser();
	bool isCorrect = true;
	void setIsCorrect(bool x) {
		isCorrect = x;
	}
	bool getIsCorrect() {
		return isCorrect;
	}
};

void Compiler::stackParser() {
	if (isEmpty()) {
		cout << "Cannot Parse, Stack Empty" << endl << endl;
		return;
	}
	/*
		O - Operator
		I - Identifier
		S - Separator
		N - Number
		K - Keyword

		K -> I,N,S,K
		I -> O,N,S,K
		N -> O,N,K
		S -> I,N,K,S
		O -> N,I
		
	*/
	fstream write;
	write.open("syntaxoutput.txt");

	write << "Stack Content: ";
	for (int i = top; i >= 0; i--) {
		write << stack[i];
	}
	cout << "Abbreviations: " << endl;
	cout << "O - Operator" << endl;
	cout << "I - Identifier" << endl;
	cout << "S - Separator" << endl;
	cout << "N - Number" << endl;
	cout << "K - Keyword" << endl;

	int upper = top;
	while (stack[upper] != '$') {
		if (isEmpty()) {
			break;
		}
		if (stack[upper] == 'K') {
			upper--;
			if (stack[upper] == 'I' || stack[upper] == 'N' || stack[upper] == 'S' || stack[upper] == 'K') {
				upper--;
			}
			else {
				if (stack[upper] == '$') {
					break;
				}
				cout << "Syntactically incorrect: " << stack[upper];
				write << "Syntactically incorrect: " << stack[upper];
				upper++;
				cout << " cannot precede " << stack[upper] << endl;	
				write << " cannot precede " << stack[upper] << endl;
				setIsCorrect(false);
				break;
			}
		}
		if (stack[upper] == 'I') {
			upper--;
			if (stack[upper] == 'O' || stack[upper] == 'N' || stack[upper] == 'S' || stack[upper] == 'K') {
				upper--;
			}
			else {
				if (stack[upper] == '$') {
					break;
				}
				cout << "Syntactically incorrect: " << stack[upper];
				write << "Syntactically incorrect: " << stack[upper];
				upper++;
				cout << " cannot precede " << stack[upper] << endl;
				write << " cannot precede " << stack[upper] << endl;
				setIsCorrect(false);
				break;
			}
		}
		if (stack[upper] == 'N') {
			upper--;
			if (stack[upper] == 'O' || stack[upper] == 'N' || stack[upper] == 'K') {
				upper--;
			}
			else {
				if (stack[upper] == '$') {
					break;
				}
				cout << "Syntactically incorrect: " << stack[upper];
				write << "Syntactically incorrect: " << stack[upper];
				upper++;
				cout << " cannot precede " << stack[upper] << endl;
				write << " cannot precede " << stack[upper] << endl;
				setIsCorrect(false);
				break;
			}
		}
		if (stack[upper] == 'S') {
			upper--;
			if (stack[upper] == 'I' || stack[upper] == 'N' || stack[upper] == 'S' || stack[upper] == 'K') {
				upper--;
			}
			else {
				if (stack[upper] == '$') {
					break;
				}
				cout << "Syntactically incorrect: " << stack[upper];
				write << "Syntactically incorrect: " << stack[upper];
				upper++;
				cout << " cannot precede " << stack[upper] << endl;
				write << " cannot precede " << stack[upper] << endl;
				setIsCorrect(false);
				break;
			}
		}
		if (stack[upper] == 'O') {
			upper--;
			if (stack[upper] == 'N' || stack[upper] == 'I') {
				upper--;
			}
			else {
				if (stack[upper] == '$') {
					break;
				}
				cout << "Syntactically incorrect: " << stack[upper];
				write << "Syntactically incorrect: " << stack[upper];
				upper++;
				cout << " cannot precede " << stack[upper] << endl;
				write << " cannot precede " << stack[upper] << endl;
				setIsCorrect(false);
				break;
			}
		}
	}
	if (isCorrect) {
		cout << "Syntactically Correct!" << endl << endl;
		write << endl <<"Syntactically Correct!" << endl;
	}
	write.close();
}
int Compiler::Keyword(char buffer[])
{
	char keywords[20][10] = { "int", "float", "bool", "true", "false", "if", "else", "then", "endif", "while", "whileend", "do", "doend", "for", "forend", "input", "output","and", "or" , "not"};

	int flag = 0;
	for (int i = 0; i < 20; i++)
	{
		if (strcmp(keywords[i], buffer) == 0)
		{
			flag = 1;
			break;
		}
	}

	return flag;
}



int Compiler::Operator(char buffer) {
	char operators[] = { '+', '=', '-', '/', '*', '%', '<', '>' };

	int flag = 0;

	for (int i = 0; i < 8; i++) {
		if (buffer == operators[i]) {
			flag = 1;
			break;
		}
	}

	return flag;
}

int Compiler::Separators(char buffer) {
	char separators[] = R"((){}[],:;)";

	int flag = 0;

	for (int i = 0; i < sizeof(separators); i++) {
		if (buffer == separators[i]) {
			flag = 1;
		}
	}

	return flag;
}

void Compiler::outputCode(string filename) {
	fstream code;
	char line;
	code.open(filename);
	if (!code.is_open()) {
		cout << "Error reading file. File path entered is likely invalid." << endl;
		system("PAUSE");
		exit(0);
	}

	cout << "CODE INPUTTED" << endl;
	while (!code.eof()) {
		line = code.get();
		cout << line;
	}
	cout << endl << endl;

	code.close();
}

int Compiler::isNum(char buffer) {
	char numbers[10] = { '0','1','2','3','4','5','6','7','8','9' };
	for (int i = 0; i < 10; i++) {
if (buffer == numbers[i]) {
	return 1;
}
	}

	return 0;
}

//THIS PORTION OF CODE (LEXER) WAS WRITTEN WITH INFLUENCE FROM AN ONLINE SOURCE
//SOURCE: https://www.thecrazyprogrammer.com/2017/02/lexical-analyzer-in-c.html
//Lines of code influenced by this website will be marked with a comment '*' above
void Compiler::lexer(string fileName) {
	char ch, buffer[15];
	fstream file;
	fstream write;
	file.open(fileName);
	write.open("output.txt");

	int j = 0;
	//*
	if (!file.is_open())
	{
		cout << "Error, " << fileName << " could not be opened" << endl;
		exit(0);
	}
	cout << "PARSED CODE" << endl;
	cout << "TOKENS" << "       " << "LEXEMES" << endl;

	//*
	while (!file.eof()) {

		ch = file.get();
		if (ch == '!') {
			file.ignore(256, '!');
		}

		//*
		if (isalnum(ch) || ch == '$' || ch == '.') {
			buffer[j++] = ch;
		}
		//*
		if ((ch == ' ' || ch == '\n' || (Operator(ch) == 1) || (Separators(ch) == 1)) && (j != 0))
		{
			int i = 0;
			bool isFloat = false;
			//*
			buffer[j] = '\0';
			//*
			j = 0;

			if (isNum(buffer[0]) == 1) {
				cout << "Number:      ";
				while (buffer[i] != NULL) {
					cout << buffer[i];
					if (buffer[i] == '.') {
						isFloat = true;
					}
					i++;
				}
				if (isFloat == true) {
					cout << "(float)";
				}
				else {
					cout << "(int)";
				}
				cout << endl;

				push('N');
			}

			//*
			if (Keyword(buffer) == 1) {
				cout << "Keyword:     " << buffer << endl;
				write << "Keyword:     " << buffer << endl;

				push('K');
			}//*
			else {
				if (isNum(buffer[0]) == 0) {
					cout << "Identifier:  " << buffer << endl;
					write << "Identifier:  " << buffer << endl;

					push('I');
				}
			}
		}

		if (Separators(ch) == 1) {
			cout << "Separator:   " << ch << endl;
			write << "Separator:   " << ch << endl;

			push('S');
		}

		if (Operator(ch) == 1) {
			cout << "Operator:    " << ch << endl;
			write << "Operator:    " << ch << endl;

			push('O');
		}
	}
	write << "Stack Content: ";
	for (int i = top; i >= 0; i--){
		write << stack[i];
	}

	file.close();
	write.close();
}

int main()
{
	Compiler c;
	char choice = 'f';
	string fileName;


	while (choice == 'f' || choice == 'F') {
		c.initializeStack();

		cout << "Enter file path: ";
		cin >> fileName;
		c.outputCode(fileName);
		c.lexer(fileName);
		c.display(c.stack);
		c.stackParser();
		cout << endl;
		cout << "Enter 'f' or 'F' to run again, anything else to quit: ";
		cin >> choice;
		if (choice != 'f' && choice != 'F') {
			break;
		}

		cout <<"--------------------------------------------------------------------";
		cout << endl << endl;
		cout << "--------------------------------------------------------------------";
		cout << endl;


	}

}

/*		* * * * * O U T P U T * * * * *
Enter file path: input1.txt
CODE INPUTTED
! Find largest value between two numbers!
int num1, num2, large$
if(num1 > num2)
{
		large = num1$;
}
else
{
		large = num2$;
} 

PARSED CODE
TOKENS       LEXEMES
Keyword:     int
Identifier:  num1
Separator:   ,
Identifier:  num2
Separator:   ,
Identifier:  large$
Keyword:     if
Separator:   (
Identifier:  num1
Operator:    >
Identifier:  num2
Separator:   )
Separator:   {
Identifier:  large
Operator:    =
Identifier:  num1$
Separator:   ;
Separator:   }
Keyword:     else
Separator:   {
Identifier:  large
Operator:    =
Identifier:  num2$
Separator:   ;
Separator:   }
Stack Content: SSIOISKSSIOISSIOISKISISIK$

Abbreviations:
O - Operator
I - Identifier
S - Separator
N - Number
K - Keyword
Syntactically Correct!


Enter 'f' or 'F' to run again, anything else to quit: f input2.txt
--------------------------------------------------------------------

--------------------------------------------------------------------
Enter file path: CODE INPUTTED
! Second input file to test lexer !
while (fahr < upper) a = 23.00 whileend 

PARSED CODE
TOKENS       LEXEMES
Keyword:     while
Separator:   (
Identifier:  fahr
Operator:    <
Identifier:  upper
Separator:   )
Identifier:  a
Operator:    =
Number:      23.00(float)
Stack Content: NOISIOISK$

Abbreviations:
O - Operator
I - Identifier
S - Separator
N - Number
K - Keyword
Syntactically Correct!


Enter 'f' or 'F' to run again, anything else to quit: f input3.txt
--------------------------------------------------------------------

--------------------------------------------------------------------
Enter file path: CODE INPUTTED
! Third input file to test lexer !
! return true if one < four and false if one >= four !
int one, two, three, four;
		if(one <= four) then output 100/10.5; endif
		else output false;
 

PARSED CODE
TOKENS       LEXEMES
Keyword:     int
Identifier:  one
Separator:   ,
Identifier:  two
Separator:   ,
Identifier:  three
Separator:   ,
Identifier:  four
Separator:   ;
Keyword:     if
Separator:   (
Identifier:  one
Operator:    <
Operator:    =
Identifier:  four
Separator:   )
Keyword:     then
Keyword:     output
Number:      100(int)
Operator:    /
Number:      10.5(float)
Separator:   ;
Keyword:     endif
Keyword:     else
Keyword:     output
Keyword:     false
Separator:   ;
Stack Content: SKKKKSNONKKSIOOISKSISISISIK$

Abbreviations:
O - Operator
I - Identifier
S - Separator
N - Number
K - Keyword
Syntactically Correct!


Enter 'f' or 'F' to run again, anything else to quit: f input4.txt
--------------------------------------------------------------------

--------------------------------------------------------------------
Enter file path: CODE INPUTTED
! This is to test a case where the syntax fails !

if + 

PARSED CODE
TOKENS       LEXEMES
Keyword:     if
Operator:    +
Stack Content: OK$

Abbreviations:
O - Operator
I - Identifier
S - Separator
N - Number
K - Keyword
Syntactically incorrect: K cannot precede O

Enter 'f' or 'F' to run again, anything else to quit: j

C:\Users\kimbe\OneDrive - Cal State Fullerton\School\Fall 2020\CPSC 323\Compiler_323\Compiler_323\Compiler_323\Debug\Compiler_323.exe (process 21836) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .

*/
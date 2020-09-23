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

};
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
		cout << "Error reading file" << endl;
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
			}

			//*
			if (Keyword(buffer) == 1) {
				cout << "Keyword:     " << buffer << endl;
				write << "Keyword:     " << buffer << endl;
			}//*
			else{
				if (isNum(buffer[0]) == 0) {
					cout << "Identifier:  " << buffer << endl;
					write << "Identifier:  " << buffer << endl;
				}
			}
		}
		
		if (Separators(ch) == 1) {
			cout << "Separator:   " << ch << endl;
			write << "Separator:   " << ch << endl;

		}

		if (Operator(ch) == 1) {
			cout << "Operator:    " << ch << endl;
			write << "Operator:    " << ch << endl;

		}
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
		cout << "Enter file name: ";
		cin >> fileName;
		c.outputCode(fileName);
		c.lexer(fileName);

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
Enter file name: input1.txt
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

Enter 'f' or 'F' to run again, anything else to quit: f
--------------------------------------------------------------------

--------------------------------------------------------------------
Enter file name: input2.txt
CODE INPUTTED
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

Enter 'f' or 'F' to run again, anything else to quit: f
--------------------------------------------------------------------

--------------------------------------------------------------------
Enter file name: input3.txt
CODE INPUTTED
! Third input file to test lexer !
! return true if one < four and false if one >= four !
int one, two, three, four;
		if(one < four) then output 100; endif
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
Identifier:  four
Separator:   )
Keyword:     then
Keyword:     output
Number:      100(int)
Separator:   ;
Keyword:     endif
Keyword:     else
Keyword:     output
Keyword:     false
Separator:   ;

Enter 'f' or 'F' to run again, anything else to quit: j

C:\Users\kimbe\OneDrive - Cal State Fullerton\School\Fall 2020\CPSC 323\Compiler_323\Compiler_323\Compiler_323\Debug\Compiler_323.exe (process 12168) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .

*/
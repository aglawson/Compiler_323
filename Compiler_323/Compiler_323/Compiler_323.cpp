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

	//pushes onto the stack a letter representing a token type
	void push(char a) {
		++top;
		stack[top] = a;
	}

	//displays the contents of the stack
	void display(char stack[]) {
		if (isEmpty()) {
			std::cout << "Stack is Empty" << endl << endl;
		}
		else
		{
			std::cout << "Stack Content: ";
			for (int i = top; i >= 0; i--) {
				std::cout << stack[i];
			}
			std::cout << endl << endl;
		}
	}

	//removes the top-most member of the stack
	void pop() {
		int temp;
		if (isEmpty()) {
			return;
		}
		temp = stack[top];
		top--;
	}

	void stackParser();
	bool isCorrect = true;

	//sets the value representing the correctness of the syntax
	//True = correct, False = incorrect syntax
	void setIsCorrect(bool x) {
		isCorrect = x;
	}

	//outputs the value of the bool representing the correctness of the syntax
	bool getIsCorrect() {
		return isCorrect;
	}

	string Types[100];

	//array of strings to store numbers in the user's code
	string storedNumbers[100];
	//initializes storage location
	int storageLocation = 0;
	//function to store a number in the above array of strings
	void storeNumbers(string input) {
		cout << input << " stored at location: " << storageLocation << endl;
		//increments to the next available storage location
		storageLocation++;
	}

	//outputs the contents of the storage location specified by the user
	void retrieveNumbers() {
		int requestedLocation = 100;
		while (requestedLocation != -1) {
			cout << "Enter location of number to retrieve or -1 to quit: ";
			cin >> requestedLocation;
			//if the user's desired location is greater than or equal to the last
			//value of the storage location, then that location is empty
			
			if (requestedLocation >= storageLocation) {					//I implemented it this way rather than checking the specific memory location and checking if it is null
				cout << "Requested location is empty" << endl;			//because if the user inputs values that are outside the scope of the array, it breaks the program.
																		//This way, it performs the same function without the danger of breaking the program.
			}
			else
			{
				//if a negative number (other than the 'quit' number) is entered.
				if (requestedLocation < -1) {
					cout << "Invalid location entered" << endl;
				}
				else
				{
					cout << storedNumbers[requestedLocation] << endl;	
				}
			}
			
		}
	}

	//function to clear the memory after each iteration
	void clearMemory() {
		for (int i = 0; i < storageLocation; i++) {
			storedNumbers[i] = "";
		}
		storageLocation = 0;
	}
};

void Compiler::stackParser() {
	if (isEmpty()) {
		std::cout << "Cannot Parse, Stack Empty" << endl << endl;
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
	std::cout << "Abbreviations: " << endl;
	std::cout << "O - Operator" << endl;
	std::cout << "I - Identifier" << endl;
	std::cout << "S - Separator" << endl;
	std::cout << "N - Number" << endl;
	std::cout << "K - Keyword" << endl;

	int upper = top;
	//top-down stack parser
	while (stack[upper] != '$') {
		if (stack[upper] == 'K') {
			upper--;
			if (stack[upper] == 'I' || stack[upper] == 'S' || stack[upper] == 'K') {
				upper--;
			}
			else {
				if (stack[upper] == '$' || stack[upper] == ' ') {
					break;
				}
				else {
					write << "Syntactical Error at Significant term #" << upper << endl;
					cout << "Syntactical Error at Significant term #" << upper << endl;
					cout << stack[upper];
					upper++;
					std::cout << " cannot precede " << stack[upper] << endl;
					write << " cannot precede " << stack[upper] << endl;
					setIsCorrect(false);
					break;
				}
			}
		}
		if (stack[upper] == 'I') {
			upper--;
			if (stack[upper] == 'O' || stack[upper] == 'N' || stack[upper] == 'S' || stack[upper] == 'K') {
				upper--;
			}
			else {
				if (stack[upper] == '$' || stack[upper] == ' ') {
					break;
				}
				else {
					write << "Syntactical Error at Significant term #" << upper << endl;
					cout << "Syntactical Error at Significant term #" << upper << endl;
					cout << stack[upper];
					upper++;
					std::cout << " cannot precede " << stack[upper] << endl;
					write << " cannot precede " << stack[upper] << endl;
					setIsCorrect(false);
					break;
				}
			}
		}
		if (stack[upper] == 'N') {
			upper--;
			if (stack[upper] == 'O' || stack[upper] == 'N' || stack[upper] == 'K' || stack[upper] == 'I' || stack[upper] == 'S') {
				upper--;
			}
			else {
				if (stack[upper] == '$' || stack[upper] == ' ') {
					break;
				}
				else {
					write << "Syntactical Error at Significant term #" << upper << endl;
					cout << "Syntactical Error at Significant term #" << upper << endl;
					cout << stack[upper];
					upper++;
					std::cout << " cannot precede " << stack[upper] << endl;
					write << " cannot precede " << stack[upper] << endl;
					setIsCorrect(false);
					break;
				}
			}
		}
		if (stack[upper] == 'S') {
			upper--;
			if (stack[upper] == '$' || stack[upper] == ' ') {
				break;
			}
			else
				if (stack[upper] == 'I' || stack[upper] == 'N' || stack[upper] == 'S' || stack[upper] == 'K') {
					upper--;
				}
				else {
					write << "Syntactical Error at Significant term #" << upper << endl;
					cout << "Syntactical Error at Significant term #" << upper << endl;
					cout << stack[upper];
					upper++;
					std::cout << " cannot precede " << stack[upper] << endl;
					write << " cannot precede " << stack[upper] << endl;
					setIsCorrect(false);
					break;
				}
		}
		if (stack[upper] == 'O') {
			upper--;
			if (stack[upper] == '$') {
				break;
			}
			else
				if (stack[upper] == 'N' || stack[upper] == 'I') {
					upper--;
				}
				else {
					write << "Syntactical Error at Significant term #" << upper << endl;
					cout << "Syntactical Error at Significant term #" << upper << endl;
					cout << stack[upper];
					upper++;
					std::cout << " cannot precede " << stack[upper] << endl;
					write << " cannot precede " << stack[upper] << endl;
					setIsCorrect(false);
					break;
				}
		}
	}
	//if the value representing the syntax correctness has not been set to false
	if (getIsCorrect() == true) {
		cout << "Syntactically Correct!" << endl << endl;
		write << endl << "Syntactically Correct!" << endl;
	}
	write.close();
}

//determines if the lexeme is a keyword
int Compiler::Keyword(char buffer[])
{
	char keywords[20][10] = { "int", "float", "bool", "true", "false", "if", "else", "then", "endif", "while", "whileend", "do", "doend", "for", "forend", "input", "output","and", "or" , "not" };

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


//determines if the lexeme is an operator
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

//determines if the lexeme is a separator
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

//determines if the lexeme is a number
int Compiler::isNum(char buffer) {
	char numbers[10] = { '0','1','2','3','4','5','6','7','8','9' };
	for (int i = 0; i < 10; i++) {
		if (buffer == numbers[i]) {
			return 1;
		}
	}

	return 0;
}

//outputs the code as entered by the user
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
					storedNumbers[storageLocation] += buffer[i];
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
				cout << storedNumbers[storageLocation] << " stored at location " << storageLocation << endl;
				storageLocation++;

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
	for (int i = top; i >= 0; i--) {
		write << stack[i];
	}

	file.close();
	write.close();
}


//This is where the magic happens!
int main()
{
	Compiler c;
	char choice = 'f';
	string fileName;

	//while the user wants to continue to enter files
	while (choice == 'f' || choice == 'F') {
		c.initializeStack();

		cout << "Enter file path: ";
		cin >> fileName;
		c.outputCode(fileName);
		c.lexer(fileName);
		c.display(c.stack);
		c.stackParser();
		cout << endl;
		c.retrieveNumbers();
		c.clearMemory();
		cout << "Enter 'f' or 'F' to run again, anything else to quit: ";
		cin >> choice;
		if (choice != 'f' && choice != 'F') {
			break;
		}

		cout << "--------------------------------------------------------------------";
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


Enter location of number to retrieve or -1 to quit: 0
Requested location is empty
Enter location of number to retrieve or -1 to quit: -1

Enter 'f' or 'F' to run again, anything else to quit: f
--------------------------------------------------------------------

--------------------------------------------------------------------
Enter file path: input2.txt
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
23.00 stored at location 0
Stack Content: NOISIOISK$

Abbreviations:
O - Operator
I - Identifier
S - Separator
N - Number
K - Keyword
Syntactically Correct!


Enter location of number to retrieve or -1 to quit: 0
23.00
Enter location of number to retrieve or -1 to quit: 1
Requested location is empty
Enter location of number to retrieve or -1 to quit: -1

Enter 'f' or 'F' to run again, anything else to quit: f
--------------------------------------------------------------------

--------------------------------------------------------------------
Enter file path: input3.txt
CODE INPUTTED
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
100 stored at location 0
Operator:    /
Number:      10.5(float)
10.5 stored at location 1
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


Enter location of number to retrieve or -1 to quit: 0
100
Enter location of number to retrieve or -1 to quit: 1
10.5
Enter location of number to retrieve or -1 to quit: 2
Requested location is empty
Enter location of number to retrieve or -1 to quit: -1

Enter 'f' or 'F' to run again, anything else to quit: f
--------------------------------------------------------------------

--------------------------------------------------------------------
Enter file path: input4.txt
CODE INPUTTED
! This is to test a case where the syntax fails !

if(3 > 1) {
		4 + 2;
		if +;
		blah = 0;
		no = 1;

} 

PARSED CODE
TOKENS       LEXEMES
Keyword:     if
Separator:   (
Number:      3(int)
3 stored at location 0
Operator:    >
Number:      1(int)
1 stored at location 1
Separator:   )
Separator:   {
Number:      4(int)
4 stored at location 2
Operator:    +
Number:      2(int)
2 stored at location 3
Separator:   ;
Keyword:     if
Operator:    +
Separator:   ;
Identifier:  blah
Operator:    =
Number:      0(int)
0 stored at location 4
Separator:   ;
Identifier:  no
Operator:    =
Number:      1(int)
1 stored at location 5
Separator:   ;
Separator:   }
Stack Content: SSNOISNOISOKSNONSSNONSK$

Abbreviations:
O - Operator
I - Identifier
S - Separator
N - Number
K - Keyword
Syntactical Error at Significant term #12
K cannot precede O

Enter location of number to retrieve or -1 to quit: 0
3
Enter location of number to retrieve or -1 to quit: 1
1
Enter location of number to retrieve or -1 to quit: 2
4
Enter location of number to retrieve or -1 to quit: 3
2
Enter location of number to retrieve or -1 to quit: 4
0
Enter location of number to retrieve or -1 to quit: 5
1
Enter location of number to retrieve or -1 to quit: 6
Requested location is empty
Enter location of number to retrieve or -1 to quit: -1

Enter 'f' or 'F' to run again, anything else to quit: i

C:\Users\kimbe\Desktop\Compiler_323\Compiler_323\Debug\Compiler_323.exe (process 7704) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .


*/

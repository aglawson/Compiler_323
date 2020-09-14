#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string>
using namespace std;

int Keyword(char buffer[])
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

void outputCode(string filename) {
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

int Operator(char buffer) {
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

int Separators(char buffer) {
	char separators[] = R"((){}[],.:;)";

	int flag = 0;

	for (int i = 0; i < sizeof(separators); i++) {
		if (buffer == separators[i]) {
			flag = 1;
		}
	}

	return flag;
}
void readFile(string fileName) {
	char ch, buffer[15], operators[] = "+-*/%=";
	
	fstream file;
	file.open(fileName);
	int j = 0;
	if (!file.is_open())
	{
		cout << "Error, " << fileName << " could not be opened" << endl;
		exit(0);
	}
	cout << "PARSED CODE" << endl;
	cout << "TOKENS" << "       " << "LEXEMES" << endl;

	while (!file.eof()) {

		ch = file.get();
		if (ch == '!') {
			file.ignore(256, '!');
		}
		
		if (Operator(ch) == 1) {
			cout << "Operator:    " << ch << endl;
		}

		if (Separators(ch) == 1) {
			cout << "Separator:   " << ch << endl;
		}

		if (isalnum(ch) || ch == '$') {
			buffer[j++] = ch;
		}

		if ((ch == ' ' || ch == '\n' || (Operator(ch) == 1) || (Separators(ch) == 1)) && (j != 0))
		{
			buffer[j] = '\0';
			j = 0;
			
			if (Keyword(buffer) == 1) {
				cout << "Keyword:     " << buffer << endl;
			}
			else {
				cout << "Identifier:  " << buffer << endl;


			}
		}

	}

	file.close();
}

int main()
{

	char choice;
	string fileName;
	cout << "Enter 'f' to input from a file or 't' to enter from terminal: ";
	cin >> choice;

	switch (choice) {

	// If user wants to enter code from a .txt file
	case 'f': case 'F':
		cout << "Enter file name: ";
		cin >> fileName;
		outputCode(fileName);
		readFile(fileName);
		
		break;
	// If user wants to enter code from the terminal
	case 't': case 'T':
		cout << "Terminal capabilities are not implemented yet." << endl << endl;

		//ofstream file;
		//file.open("newfile.txt");
		//if (!file.is_open()) {
		//	cout << "Error: could not open file" << endl;
		//	exit(0);
		//}
		//string program;
		//cout << "Type program: " << endl;
		//getline(cin, program, '\n');
		//cout << program;
		//file.close();
		//string fileName = "newfile.txt";
		//readFile(fileName);
		break;
	}



	return 0;
}

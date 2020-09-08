#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string>
using namespace std;

int Keyword(char buffer[])
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

void readFile(string fileName) {
	char ch, buffer[15], operators[] = "+-*/%=", symbols[] = R"("()[]{}/\<>'";,.:)";

	fstream file;
	file.open(fileName);
	int j = 0;
	if (!file.is_open())
	{
		cout << "Error, " << fileName << " could not be opened" << endl;
		exit(0);
	}

	while (!file.eof()) {

		ch = file.get();
		if (ch == '!') {
			file.ignore(256, '!');
		}
		for (int i = 0; i < 6; ++i)
		{
			if (ch == operators[i])
				cout << "Operator: " << ch << endl;
		}
		for (int j = 0; j < 12; j++) {
			if (ch == symbols[j]) {
				cout << "Separator: " << ch << endl;
			}
		}
		if (isalnum(ch)) {
			buffer[j++] = ch;
		}
		else if ((ch == ' ' || ch == '\n') && (j != 0))
		{
			buffer[j] = '\0';
			j = 0;
			if (Keyword(buffer) == 1) {
				cout << "Keyword: " << buffer << endl;
			}
			else {
				cout << "Identifier: " << buffer << endl;
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
	case 'f': case 'F':
		cout << "Enter file name: ";
		cin >> fileName;
		readFile(fileName);
		break;
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

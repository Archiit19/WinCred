#include "stdafx.h"
#include <Windows.h>
#include <string>
using namespace std;
#include <iostream>

#include "userIO.h"


userIO::userIO()
{
}


userIO::~userIO()
{
}


void userIO::setUserName()
{
	cout << "\n Enter the User Name : ";
	getline(cin, this->userName);
}

void userIO::setPassword()
{
	cout << "\n Enter the Password : ";
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	BOOL nRet = SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	getline(cin, this->password);
	if (TRUE != nRet)
		cout << "\nError in accepting User Input" << GetLastError();
}

string userIO::getUserName() 
{
	return this->userName;
}

string userIO::getPassword() 
{
	return this->password;
}

// WinCred.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "winCredOps.h"
#include <vector>

using namespace std;



void acceptInput(string &userName, string &password) 
{
	cout << "\n Enter the User Name : ";
	getline(cin, userName);
	cout << "\n Enter the Password : ";
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	BOOL nRet= SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	getline(cin, password);
	if (TRUE != nRet)
		cout << "\nError in accepting User Input" << GetLastError();
}


vector<winCredOps> readUserSpecificCredentials(string userName)
{
	PCREDENTIAL *pCredentialsArray = NULL;
	vector <winCredOps> pCredentialFoundArray;

	DWORD dwCount = 0;
	if (CredEnumerate(NULL, 0, &dwCount, &pCredentialsArray))
	{
		cout << "\nCredentials read successfully.\n" << endl;
		for (DWORD dwIndex = 0; dwIndex < dwCount; dwIndex++)
		{
			//PCREDENTIAL pCredential = pCredentialsArray[dwIndex];	//Commented line.. 

			//Write the existing credential information into the standard output.
			winCredOps winCredOpsObj(pCredentialsArray[dwIndex]);
			if (winCredOpsObj.isUserCredentialFound(userName))
			{
				winCredOpsObj.printCredentialInfo(dwIndex);
				pCredentialFoundArray.push_back(winCredOpsObj);
			}
		}
	}
	else
	{
		if (dwCount == 0)
		{
			printf("\n No Credentials found.");
		}
		else
		{
			printf("\nFailed to fetch the Credentials..!! \n\n");
		}
	}
	return pCredentialFoundArray;
}

int main()
{
	string userName = { 0 };
	string password = { 0 };
	acceptInput(userName, password);

	vector<winCredOps> winCredFoundArray = readUserSpecificCredentials(userName);
	
	if (winCredFoundArray.size() != 0)
	{
		for (int i = 0 ; i < winCredFoundArray.size(); i++)
		{
			cout << "\n Inside Win Cred Found Array Iteration Number : " << i;
			winCredOps winCredFoundObj(winCredFoundArray[i]);
			winCredFoundObj.writeDomainOrGenericCredential(password);
		}
	}
	else
	{
		cout << "\n No Credentials exist with given user Name.. ";
		//cout << "\n Do you want to write new credentials.";
	}

	getchar();
	return 0;

}



/*
else
	cout << "\nUser Name is :  " << userName << " \nPassword is :  " << "********";
*/
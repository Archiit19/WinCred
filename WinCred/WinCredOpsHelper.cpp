#include "stdafx.h"
#include <Windows.h>
#include <vector>
using namespace std;

#include "winCredOps.h"
#include "userIO.h"
#include "WinCredOpsHelper.h"


WinCredOpsHelper::WinCredOpsHelper(userIO userIOobj)
{
	this->userIOobj = userIOobj;
}


WinCredOpsHelper::~WinCredOpsHelper()
{
}


void WinCredOpsHelper::readUserSpecificCredentials()
{
	PCREDENTIAL *pCredentialsArray = NULL;

	DWORD dwCount = 0;
	if (CredEnumerate(NULL, 0, &dwCount, &pCredentialsArray))
	{
		cout << "\nCredentials read successfully.\n" << endl;
		for (DWORD dwIndex = 0; dwIndex < dwCount; dwIndex++)
		{
			//PCREDENTIAL pCredential = pCredentialsArray[dwIndex];	//Commented line.. 

			//Write the existing credential information into the standard output.
			winCredOps winCredOpsObj(pCredentialsArray[dwIndex]);
			if (winCredOpsObj.isUserCredentialFound((this->userIOobj).getPassword()))
			{
				winCredOpsObj.printCredentialInfo(dwIndex);
				this->pCredentialFoundArray.push_back(winCredOpsObj);
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
}

void WinCredOpsHelper::writeCredentials()
{
	if ( ( (this->pCredentialFoundArray).size()) != 0)
	{
		for ( int i = 0; i < ((this->pCredentialFoundArray).size()); i++)
		{
			cout << "\n Inside Win Cred Found Array Iteration Number : " << i;
			winCredOps winCredFoundObj((this->pCredentialFoundArray)[i]);
			winCredFoundObj.writeDomainOrGenericCredential((this->userIOobj).getPassword());
		}
	}
	else
	{
		cout << "\n No Credentials exist with given user Name.. ";
		//cout << "\n Do you want to write new credentials.";
	}
}



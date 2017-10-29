#pragma once

#include <windows.h>
#include <string>
#include "WinCredentials.h"
#include <iostream>

#include "atlstr.h"

using namespace std;

class winCredOps
{
private :
	PCREDENTIAL pCredential = NULL;

public:
	winCredOps(PCREDENTIAL pCredential);

	std::wstring convertS2Ws(const std::string& as);

	void printCredentialBlobPassword();
	void printCredentialInfo(DWORD credIndex);

	BOOL isUserCredentialFound(string userName);
	//PCREDENTIAL readSpecificCredential(string userName);


	BOOL writeDomainPasswordCredential(string password);
	BOOL writeGenericCredential(string password);
	void writeDomainOrGenericCredential(string password);

	~winCredOps();
};


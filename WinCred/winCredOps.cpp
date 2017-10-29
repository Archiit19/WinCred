#include "stdafx.h"
#include "winCredOps.h"


using namespace std;

winCredOps::winCredOps(PCREDENTIAL pCredential)
{
	this->pCredential = pCredential;
}


winCredOps::~winCredOps()
{
	this->pCredential = NULL;
	delete this->pCredential;
}


std::wstring winCredOps::convertS2Ws(const std::string& as)
{
	// deal with trivial case of empty string
	if (as.empty())    return std::wstring();

	// determine required length of new string
	size_t reqLength = ::MultiByteToWideChar(CP_UTF8, 0, as.c_str(), (int)as.length(), 0, 0);

	// construct new string of required length
	std::wstring ret(reqLength, L'\0');

	// convert old string to new string
	::MultiByteToWideChar(CP_UTF8, 0, as.c_str(), (int)as.length(), &ret[0], (int)ret.length());

	// return new string ( compiler should optimize this away )
	return ret;
}

void winCredOps::printCredentialBlobPassword()
{
	printf("\nPassword or BlobData: ");

	char szAsciiBuffer[256] = "";
	char szAscii[2];
	DWORD dwByte;

	//Write the credential's data in PlainText.
	for (dwByte = 0; dwByte < this->pCredential->CredentialBlobSize; dwByte++)
	{
		BYTE byte1 = this->pCredential->CredentialBlob[dwByte];
		szAscii[1] = '\0';

		if (byte1 >= 32 && byte1 < 128)
			szAscii[0] = (UCHAR)byte1;
		else
			szAscii[0] = ' ';
		strcat_s(szAsciiBuffer, szAscii);
		if (dwByte == this->pCredential->CredentialBlobSize - 1 || dwByte % 16 == 15)
		{
			printf("%s\n", szAsciiBuffer);
			szAsciiBuffer[0] = '\0';
		}
	}
}

void winCredOps::printCredentialInfo(DWORD credIndex)
{
	printf("\n\n******************Credential Info : %d *************************\n\n", credIndex + 1);
	printf("\nFlags: %d    Type: %d    Name: %ls    Comment: %ls    Persist: %d    User: %ls \n",
		this->pCredential->Flags, this->pCredential->Type, this->pCredential->TargetName,
		this->pCredential->Comment, this->pCredential->Persist, this->pCredential->UserName);
	printCredentialBlobPassword();
	printf("\n*********************************************\n\n");
}


BOOL winCredOps::isUserCredentialFound(string userName)
{
	string credentialUserName = CW2A(this->pCredential->UserName);
	if (credentialUserName == userName)
	{
		cout << "\n Credential UserName is : " << credentialUserName << "\n UserName received is : " << userName;
		return true;
	}

	return false;
}


BOOL winCredOps::writeDomainPasswordCredential(string password)
{
	CREDENTIAL_TARGET_INFORMATIONW CredTargetInfo = {};
	CredTargetInfo.DnsDomainName = L"COMMUNITY";
	CredTargetInfo.TargetName = this->pCredential->TargetName;

	CREDENTIAL CredToWrite = *(this->pCredential);
	
	wstring wPassword = convertS2Ws(password);
	wcout << "Password in WStirng is  : " << wPassword;
	const wchar_t * PasswordBuff = wPassword.c_str();
	CredToWrite.CredentialBlob = (LPBYTE)PasswordBuff;
	CredToWrite.CredentialBlobSize = sizeof(PasswordBuff) - sizeof(PasswordBuff[0]);
	BOOL bCrDpcFlag = ::CredWriteDomainCredentialsW(&CredTargetInfo, &CredToWrite, 0);
	printf("\n CredWriteDomainCredentials() : Return Value is : %d", bCrDpcFlag);
	return bCrDpcFlag;
}


BOOL winCredOps::writeGenericCredential(string password)
{
	CREDENTIAL CredToWrite = *(this->pCredential);
	const char * newPassword = password.c_str();
	DWORD cbCreds = 1 + strlen(newPassword);
	CredToWrite.CredentialBlob = (LPBYTE)newPassword;
	CredToWrite.CredentialBlobSize = cbCreds;
	cout << "\n\n CredToWrite Password is :  " << CredToWrite.CredentialBlob;
	BOOL bCRDC = ::CredWrite(&CredToWrite, 0);
	printf("\n CredWrite() : Return Value is : %d", bCRDC);
	return bCRDC;
}

void winCredOps::writeDomainOrGenericCredential(string password)
{
	CREDENTIALW CredToWrite = { 0 };
	BOOL bCr = 0;
	if (this->pCredential->Type == CRED_TYPE_DOMAIN_PASSWORD)
	{
		cout << "\n Write Domain Credentials.. ";
		bCr = writeDomainPasswordCredential(password);			// Returns BOOL.
	}
	else if (this->pCredential->Type == CRED_TYPE_GENERIC)
	{
		cout << "\n Write Generic Credentials.. ";
		bCr = writeGenericCredential(password);				// Returns BOOL.
	}
	else
	{
		cout << "\nPassword Change for other types is not supported." << endl;
	}
	if (!bCr)
		printf(" \nPassword write failed with Error  :  %x ", GetLastError());
}






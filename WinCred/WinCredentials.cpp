#include "stdafx.h"
#include "WinCredentials.h"
#include <windows.h>


WinCredentials::WinCredentials()
{
	hAdvApi32 = NULL;
	bLoaded = FALSE;
}

WinCredentials::~WinCredentials()
{
	FreeCredsLibrary();
}

BOOL WinCredentials::IsLoaded()
{
	return bLoaded;
}


BOOL WinCredentials::LoadCredsLibrary()
{
	if (bLoaded) return TRUE;

	hAdvApi32 = LoadLibrary(_T("advapi32.dll"));
	if (hAdvApi32 != NULL)
	{
		//Dynamically load CredRead, CredEnumerate, and CredFree API functions.
		pCredRead = (CredReadFuncType)GetProcAddress(hAdvApi32, "CredReadW");
		pCredWrite = (CredWriteFuncType)GetProcAddress(hAdvApi32, "CredWriteW");
		pCredFree = (CredFreeFuncType)GetProcAddress(hAdvApi32, "CredFree");
		pCredEnumerate = (CredEnumerateType)GetProcAddress(hAdvApi32, "CredEnumerateW");

		//If all 3 functions are available, return TRUE.
		if (pCredRead != NULL && pCredFree != NULL && pCredEnumerate != NULL)
			bLoaded = TRUE;
		else
		{
			//Failed to load the credentials API functions.
			FreeCredsLibrary();
		}
	}

	return bLoaded;
}

void WinCredentials::FreeCredsLibrary()
{
	//Free advapi32 library, if we previously loaded it.
	if (hAdvApi32 != NULL)
	{
		FreeLibrary(hAdvApi32);
		hAdvApi32 = NULL;
	}

	bLoaded = FALSE;

}


BOOL WinCredentials::CredRead(
	LPCTSTR TargetName,
	DWORD Type,
	DWORD Flags,
	PCREDENTIAL *Credential
)
{
	if (bLoaded)
		return pCredRead(TargetName, Type, Flags, Credential);
	else
		return FALSE;
}

BOOL WinCredentials::CredWrite(
	PCREDENTIAL Credential,
	DWORD Flags
)
{
	if (bLoaded)
		return pCredWrite( Credential, Flags);
	else
		return FALSE;
}


BOOL WinCredentials::CredEnumerate(
	LPCTSTR Filter,
	DWORD Flags,
	DWORD *Count,
	PCREDENTIAL **Credentials
)
{
	if (bLoaded)
		return pCredEnumerate(Filter, Flags, Count, Credentials);
	else
		return FALSE;
}

VOID WinCredentials::CredFree(PVOID Buffer)
{
	if (bLoaded)
		pCredFree(Buffer);
}

#include <windows.h>
#include <wincred.h>

class WinCredentials
{
	protected:

	typedef BOOL(WINAPI *CredReadFuncType)(
		LPCTSTR TargetName,
		DWORD Type,
		DWORD Flags,
		PCREDENTIAL *Credential
		);

	typedef BOOL(WINAPI *CredWriteFuncType)(
		PCREDENTIAL Credential,
		DWORD       Flags
		);

	typedef BOOL(WINAPI *CredEnumerateType)(
		LPCTSTR Filter,
		DWORD Flags,
		DWORD *Count,
		PCREDENTIAL **Credentials
		);

	typedef VOID(WINAPI *CredFreeFuncType)(PVOID Buffer);


	HMODULE hAdvApi32;
	BOOL bLoaded;
	CredReadFuncType pCredRead;
	CredWriteFuncType pCredWrite;
	CredFreeFuncType pCredFree;
	CredEnumerateType pCredEnumerate;


public:
	WinCredentials();
	~WinCredentials();
	BOOL LoadCredsLibrary();
	void FreeCredsLibrary();
	BOOL IsLoaded();
	BOOL CredRead(
		LPCTSTR TargetName,
		DWORD Type,
		DWORD Flags,
		PCREDENTIAL *Credential
	);

	BOOL CredWrite(
		PCREDENTIAL Credential,
		DWORD       Flags
	);

	BOOL CredEnumerate(
		LPCTSTR Filter,
		DWORD Flags,
		DWORD *Count,
		PCREDENTIAL **Credentials
	);

	VOID CredFree(PVOID Buffer);
};
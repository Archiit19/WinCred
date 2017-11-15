#pragma once

#include "winCredOps.h"

class WinCredOpsHelper
{
	private:
		vector<winCredOps> pCredentialFoundArray;
		userIO userIOobj;

	public:
		WinCredOpsHelper(userIO userIOobj);
		void readUserSpecificCredentials();
		void writeCredentials();
		~WinCredOpsHelper();
};


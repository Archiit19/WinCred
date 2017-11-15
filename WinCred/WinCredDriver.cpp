// WinCredDriver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <string>

using namespace std;

#include "userIO.h"
#include "WinCredOpsHelper.h"




int main()
{
	userIO userIOobj;
	userIOobj.setUserName();
	userIOobj.setPassword();

	WinCredOpsHelper winCredOpsHelperObj(userIOobj);

	winCredOpsHelperObj.readUserSpecificCredentials();		//returns vector of winCredOps. - winCredFoundArray()
	winCredOpsHelperObj.writeCredentials();

	getchar();
	return 0;

}
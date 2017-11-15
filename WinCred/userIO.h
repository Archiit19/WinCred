#pragma once

class userIO
{
	private:
		string userName;
		string password;

	public:
		userIO();
		void setUserName(void);
		void setPassword(void);
		string getUserName(void);
		string getPassword(void);
		~userIO();
};


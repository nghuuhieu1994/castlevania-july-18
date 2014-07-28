#ifndef __GAME_LOG__
#define __GAME_LOG__
#include <string>

using namespace std;
//Manage log of game, using Singleton Pattern
class CGameLog
{
public:
	//Get Instance of class
	static CGameLog* GetInstance();
	//Get Instance of class and change the module name 
	static CGameLog* GetInstance(string ModuleName);
	//Set Name of Game Log file output
	void SetNameLogFile(string NameLogFile);
	//Save Information in Game Log file
	void SaveInfo(string Information);
	//Save Error in Game log file
	void SaveError(string Error);
	//Get Current Date and Time
	string GetCurrentDate();
private:
	//Constructor
	CGameLog();
	//Destructor
	~CGameLog();
	//Static Instance Of CGameLog class
	static CGameLog* s_Instance;
	//Name of Game Log File
	string m_LogFileName;
	//Name of current working module
	string m_CurrentModuleName;
};

#endif
#pragma once

#include <Always.h>

class CScripttype
{
public:
	static CScripttype Instance;

    void Handle();

private:
	bool IsDialogOpen;
	
};

struct ScriptAction
{
	int Type;
	union 
	{
		int Param;
		struct 
		{
			short ParamNormal;
			short ParamExt;
		};
	};
};

struct ScriptItem
{
    char ID[24];
    char Name[50];
	ScriptAction Actions[50];
	int ActionCount;
};
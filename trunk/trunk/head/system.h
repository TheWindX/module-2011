#pragma once
#include "windows.h"
#include <string>


HMODULE WINAPI ModuleFromAddress(void* pv)
{
	MEMORY_BASIC_INFORMATION mbi;
	if(::VirtualQuery(pv, &mbi, sizeof(mbi)) != 0)
	{
		return (HMODULE)mbi.AllocationBase;
	}
	else
	{
		return NULL;
	}
}



const char*  MakeAPIErrorDesc ()
{
	static std::string ret;
	LPTSTR lpErrDesc = NULL;
	DWORD dwError = ::GetLastError ();

	FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dwError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), lpErrDesc, 0, NULL);
	
	ret = lpErrDesc;
	LocalFree(lpErrDesc);
	return ret.c_str();
}


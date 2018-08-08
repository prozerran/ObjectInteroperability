// ObjectDllTest_Dynamic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"
#include "ObjectDll.h"
#include <crtdbg.h>

using namespace XInterface;

#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "("__STR1__(__LINE__)") : Warning: "

void __stdcall MyCallbackFunc(const char* str)
{
	printf("%s\n", str);
}

void __stdcall MyCallbackMethod(const char* str, void* context)
{
	printf("%s\n", str);
}

int _tmain(int argc, _TCHAR* argv[])
{
#ifdef _DEBUG
#pragma message(__LOC__ "Exception Error popup disabled on Debug.")
	//SetErrorMode(GetErrorMode () | SEM_FAILCRITICALERRORS);
	_CrtSetReportMode(_CRT_ERROR, 0);
#endif

	HMODULE hDll = ::LoadLibrary(_T("ObjectDll.dll"));

	if (hDll)
	{
		char res[MAX_BUFF_STR_SIZE] = {0};

		// access dll function
		LPFUNC ObjectDllFunction = (LPFUNC) GetProcAddress(hDll, "ObjectDllFunction");
	
		ObjectDllMethod();
		ObjectDllFunction("", res, sizeof(res));
		printf("%s\n", res);

		// access dll callback, get address from dumpbin
		// $ dumpbin /exports ObjectDll.dll
		LPCALLBACKFUNC ObjectDllCallback = (LPCALLBACKFUNC) GetProcAddress(hDll, "_ObjectDllCallback@4");
		ObjectDllCallback(MyCallbackFunc);

		// access dll class object
		LPOBJECTCREATE CreateObjectDll = (LPOBJECTCREATE) GetProcAddress(hDll, "ObjectDllCreate");
		LPOBJECTFREE FreeObjectDll = (LPOBJECTFREE) GetProcAddress(hDll, "ObjectDllFree");

		CObjectDll* pObj = (CObjectDll*) CreateObjectDll();

		pObj = dynamic_cast<CObjectDll*>(pObj);
		if (pObj)
		{
			pObj->InvokeMethod("", res, sizeof(res));
			printf("%s\n", res);

			pObj->InvokeCallback(MyCallbackMethod, NULL);
			FreeObjectDll(pObj);
		}
		::FreeLibrary(hDll);
	}
	return 0;
}


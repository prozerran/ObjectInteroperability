// ObjectDllTest_Static.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ObjectDll.h"

using namespace XInterface;

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
	char res[MAX_BUFF_STR_SIZE] = {0};
	ObjectDllMethod();
	ObjectDllFunction("", res, sizeof(res));
	printf("%s\n", res);
	ObjectDllCallback(MyCallbackFunc);

	CObjectDll pObj;
	pObj.InvokeMethod("", res, sizeof(res));
	printf("%s\n", res);
	pObj.InvokeCallback(MyCallbackMethod, NULL);

	return 0;
}


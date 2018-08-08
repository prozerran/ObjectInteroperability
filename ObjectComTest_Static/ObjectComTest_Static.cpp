// ObjectComTest_Static.cpp : Defines the entry point for the console application.
//

#define _WIN32_DCOM
#include "stdafx.h"

// include com headers
#include <objbase.h>
#include <comdef.h>
#include <Wbemidl.h>
#include <comutil.h>

#import "..\\ObjectCom\\_ObjectCom.tlb"

using namespace ObjectCom;    // namespace and interfaces via IDL

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
	// init COM, use [COINIT_MULTITHREADED] if multi-threaded
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	if( SUCCEEDED(hr) )
	{
		IObjectComLib* pIObj = NULL;

		hr = CoCreateInstance( __uuidof(CObjectComLib), NULL, CLSCTX_INPROC_SERVER,
			__uuidof(IObjectComLib), (void**) &pIObj);

		if( SUCCEEDED(hr) )
		{
			if ( pIObj && SUCCEEDED(pIObj->ObjectCreate()) )
			{
				// call some ordinary functions
				if ( SUCCEEDED(pIObj->ObjectDllMethod() ) ) {}
				if ( SUCCEEDED(pIObj->ObjectDllCallback((char*) MyCallbackFunc) ) ) {}

				BSTR bstr;
				if ( SUCCEEDED(pIObj->ObjectDllFunction("", &bstr) ) ) 
				{
					printf("%s\n", _com_util::ConvertBSTRToString(bstr));
				}

				// call member functions
				if ( SUCCEEDED(pIObj->InvokeMethod() ) ) {}
				if ( SUCCEEDED(pIObj->InvokeCallback((char*) MyCallbackMethod, NULL) ) ) {}

				if ( SUCCEEDED(pIObj->InvokeObjectMethod("CObjectComLib::InvokeObjectMethod ", &bstr) ) ) 
				{
					printf("%s\n", _com_util::ConvertBSTRToString(bstr));
				}
				if ( SUCCEEDED(pIObj->ObjectFree()   ) ) {}
			}
		}
	}
	CoUninitialize();

	return 0;
}


// ObjectComTest_Dynamic.cpp : Defines the entry point for the console application.
//

#define _WIN32_DCOM
#include "stdafx.h"

// include com headers
#include <objbase.h>
#include <comdef.h>
#include <Wbemidl.h>
#include <comutil.h>

// import library and type library
#pragma comment(lib, "wbemuuid.lib")
#import "..\\ObjectCom\\_ObjectCom.tlb"

// global function decl
typedef HRESULT ( STDAPICALLTYPE *pDllGetClassObject )(   REFCLSID rclsid, REFIID riid,  LPVOID * ppv );

// ===============================================================
//           SAMPLE CODE USING COM LIBRARY
// ===============================================================

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
	IClassFactory*      pICF = NULL;
	pDllGetClassObject  m_pDllGCO;

	_bstr_t sDLL = _T("ObjectCom.dll");

	// init COM, use [COINIT_MULTITHREADED] if multi-threaded
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	// load COM DLL
	HMODULE hLib = LoadLibrary(sDLL);

	if( hLib == NULL )
	{
		_ftprintf( stderr, _T("Loading DLL Unsuccessful.\n") );
		goto end;
	}

	// load class factory
	if( ( m_pDllGCO = ( pDllGetClassObject ) GetProcAddress( hLib, "DllGetClassObject" ) ) == NULL )
	{
		_ftprintf( stderr, _T("Failed to resolve function addresses: DllGetClassObject.\n") );
		goto end;
	}

	// loadings successful, instantiate objects
	if ( SUCCEEDED( m_pDllGCO(__uuidof(CObjectComLib), __uuidof(IClassFactory),(void**) &pICF) ) )
	{
		IObjectComLib* pIObj = NULL;

		if ( SUCCEEDED( pICF->CreateInstance(NULL, __uuidof(IObjectComLib), (void**) &pIObj) ) )
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

end:

	// free ObjectCOM
	if( hLib )
		FreeLibrary(hLib);

	// release COM
	CoUninitialize();
		
	return 0;
}


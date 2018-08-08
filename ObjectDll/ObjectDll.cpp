// ObjectDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "stdio.h"
#include "ObjectDll.h"

namespace XInterface
{
	// This is an example of an exported variable
	OBJECTDLL_API int nObjectDll=0;

	// This is an example of an exported function.
	OBJECTDLL_API int ObjectDllMethod()
	{
		printf("%s\n", __FUNCTION__);
		return 0;
	}

	OBJECTDLL_API int ObjectDllFunction(const char* str, char* res, int size)
	{
		memset(res, 0, size);
		_snprintf(res, size, "%s%s", str, __FUNCTION__);
		return 0;
	}

	OBJECTDLL_API void __stdcall ObjectDllCallback( CallbackFunc funcname )
	{
		CallbackFunc callbackfunc = funcname;

		if (callbackfunc)
		{
			// ... some work here... then lets call our function
			callbackfunc(__FUNCTION__);
		}
	}

	OBJECTDLL_API void* ObjectDllCreate()
	{
		return new CObjectDll();
	}

	OBJECTDLL_API void ObjectDllFree( void* pObj )
	{
		CObjectDll* pObjDll = static_cast<CObjectDll*>(pObj);
		if (pObjDll)
		{
			delete pObjDll;
			pObjDll = NULL;
		}
	}

	OBJECTDLL_API void ObjectDllInvokeMethod( void* pObj )
	{
		CObjectDll* pObjDll = static_cast<CObjectDll*>(pObj);
		if (pObjDll)
		{
			pObjDll->InvokeMethod();
		}
	}

	/*
	OBJECTDLL_API void __stdcall ObjectDllInvokeCallback( void* pObj, CallbackMethod funcname, void* context )
	{
		CObjectDll* pObjDll = static_cast<CObjectDll*>(pObj);
		if (pObjDll)
		{
			pObjDll->InvokeCallback(funcname, context);
		}
	}
	*/

	// This is the constructor of a class that has been exported.
	// see ObjectDll.h for the class definition
	CObjectDll::CObjectDll()
	{}

	int CObjectDll::InvokeMethod() const
	{
		printf("%s\n", __FUNCTION__);
		return 0;
	}

	int CObjectDll::InvokeMethod(const char* str, char* res, int size) const
	{
		memset(res, 0, size);
		_snprintf(res, size, "%s%s", str, __FUNCTION__);
		return 0;
	}

	void CObjectDll::InvokeCallback( CallbackMethod funcname = NULL, void* context = NULL)
	{
		m_callback = funcname;

		if (m_callback)
		{
			// ... some work here... then lets call our function
			m_callback(__FUNCTION__, context);
		}
	}
}

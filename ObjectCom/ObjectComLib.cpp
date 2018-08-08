// ObjectComLib.cpp : Implementation of CObjectComLib

#include "stdafx.h"
#include "ObjectComLib.h"
#include ".\objectcomlib.h"

// CObjectComLib

namespace XInterface
{
	STDMETHODIMP CObjectComLib::ObjectCreate(void)
	{
		if (!m_pObj)
		{
			m_pObj = (CObjectDll*) ObjectDllCreate();
		}
		return S_OK;
	}

	STDMETHODIMP CObjectComLib::ObjectFree(void)
	{
		if (m_pObj)
		{
			ObjectDllFree(m_pObj);
			m_pObj = NULL;
		}
		return S_OK;
	}

	STDMETHODIMP CObjectComLib::InvokeMethod(void)
	{
		if (m_pObj)
		{
			m_pObj->InvokeMethod();
		}
		return S_OK;
	}

	STDMETHODIMP CObjectComLib::InvokeCallback(CHAR* funcname, CHAR* context)
	{
		if (m_pObj)
		{
			m_pObj->InvokeCallback((CallbackMethod) funcname, context);
		}
		return S_OK;
	}

	STDMETHODIMP CObjectComLib::InvokeObjectMethod(BSTR str, BSTR* res)
	{
		_ATLTRY
		{
			ATLENSURE_THROW(res, E_POINTER);		// Parameter validation
			*res = NULL;							// We're responsible to initialize this no matter what

			char szStr[MAX_BUFF_STR_SIZE] = {0};
			char* p = _com_util::ConvertBSTRToString(str);

			if (m_pObj)
			{
				m_pObj->InvokeMethod(p, szStr, sizeof(szStr));
				CString sValue(szStr);

				// Doing our stuff to get the string value into variable
				*res = CComBSTR(sValue).Detach();
			}
		}
		_ATLCATCH(Exception)
		{
			return Exception;
		}
		return S_OK;
	}

	STDMETHODIMP CObjectComLib::ObjectDllMethod(void)
	{
		XInterface::ObjectDllMethod();
		return S_OK;
	}

	STDMETHODIMP CObjectComLib::ObjectDllFunction(BSTR str, BSTR* res)
	{
		_ATLTRY
		{
			ATLENSURE_THROW(res, E_POINTER);
			*res = NULL;

			char szStr[MAX_BUFF_STR_SIZE] = {0};
			char* p = _com_util::ConvertBSTRToString(str);

			XInterface::ObjectDllFunction(p, szStr, sizeof(szStr));
			CString sValue(szStr);

			*res = CComBSTR(sValue).Detach();
		}
		_ATLCATCH(Exception)
		{
			return Exception;
		}
		return S_OK;
	}

	STDMETHODIMP CObjectComLib::ObjectDllCallback(CHAR* funcname)
	{
		XInterface::ObjectDllCallback((CallbackFunc) funcname);
		return S_OK;
	}

	STDMETHODIMP CObjectComLib::Initialize(VARIANT* funcname)
	{
		// TODO....
		// FIX PARAM
		// Connection Point = callback

		//CObjectComLib* iptr = reinterpret_cast<CObjectComLib*>(funcname);
		//iptr->InvokeMethod();
		//XInterface::ObjectDllCallback((CallbackFunc) &funcname);
		return S_OK;
	}
}
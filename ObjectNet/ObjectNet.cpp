// This is the main DLL file.

#include "stdafx.h"

#include "ObjectNet.h"

namespace ObjectNet
{
	CObjectNet::CObjectNet()
	{
		m_pObj = nullptr;
	}

	void CObjectNet::ObjectCreate()
	{
		if (!m_pObj)
		{
			m_pObj = (CObjectDll*) ObjectDllCreate();
		}
	}

	void CObjectNet::ObjectFree()
	{
		if (m_pObj)
		{
			ObjectDllFree(m_pObj);
			m_pObj = nullptr;
		}
	}

	void CObjectNet::InvokeMethod()
	{
		if (m_pObj)
			m_pObj->InvokeMethod();
	}

	void CObjectNet::InvokeCallback(IntPtr^ cb_ptr, IntPtr^ context)
	{
		if (m_pObj)
		{
			CallbackMethod callback = static_cast<CallbackMethod>(cb_ptr->ToPointer());
			m_pObj->InvokeCallback(callback, context->ToPointer());
		}
	}

	// ordinary functions [static]
	int CObjectNet::ObjectDllMethod()
	{
		return XInterface::ObjectDllMethod();
	}

	void CObjectNet::ObjectDllFunction(String^ str, String^% res)
	{
		IntPtr p = Marshal::StringToHGlobalAnsi(str);
		const char* pstr = static_cast<const char*>(p.ToPointer());

		char cstr[MAX_BUFF_STR_SIZE] = {0};
		XInterface::ObjectDllFunction(pstr, cstr, sizeof(cstr));		
		res = gcnew String(cstr);

		Marshal::FreeHGlobal(p);
	}

	void CObjectNet::ObjectDllCallback(IntPtr^ cb_ptr)
	{		 
		CallbackFunc callback = static_cast<CallbackFunc>(cb_ptr->ToPointer());

		if (callback)
		{
			XInterface::ObjectDllCallback(callback);
		}
	}
}
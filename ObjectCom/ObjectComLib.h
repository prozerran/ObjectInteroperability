// ObjectComLib.h : Declaration of the CObjectComLib

#pragma once
#include <comutil.h>
#include "resource.h"       // main symbols
#include "ObjectDll.h"

namespace XInterface
{
	// IObjectComLib
	[
		object,
		uuid("284FEECD-B04F-486F-857B-88A56113309F"),
		dual,
		helpstring("IObjectComLib Interface"),
		pointer_default(unique)
	]
	__interface IObjectComLib : IDispatch
	{
		[id(1), helpstring("method ObjectCreate")] HRESULT ObjectCreate(void);
		[id(2), helpstring("method ObjectFree")] HRESULT ObjectFree(void);
		[id(3), helpstring("method InvokeMethod")] HRESULT InvokeMethod(void);
		[id(4), helpstring("method InvokeObjectMethod")] HRESULT InvokeObjectMethod([in] BSTR str, [in,out] BSTR* res);
		[id(5), helpstring("method InvokeCallback")] HRESULT InvokeCallback([in] CHAR* funcname, [in] CHAR* context);
		[id(6), helpstring("method ObjectDllMethod")] HRESULT ObjectDllMethod(void);
		[id(7), helpstring("method ObjectDllFunction")] HRESULT ObjectDllFunction([in] BSTR str, [in,out] BSTR* res);
		[id(8), helpstring("method ObjectDllCallback")] HRESULT ObjectDllCallback([in] CHAR* funcname);
		[id(9), helpstring("method Initialize")] HRESULT Initialize([in] VARIANT* funcname);
	};

	// CObjectComLib
	[
		coclass,
		threading("apartment"),
		vi_progid("ObjectCom.ObjectComLib"),
		progid("ObjectCom.ObjectComLib.1"),
		version(1.0),
		uuid("308DCA5C-3701-4F99-B85C-B73EBA50A28E"),
		helpstring("ObjectComLib Class")
	]
	class ATL_NO_VTABLE CObjectComLib : public IObjectComLib {
	public:

		CObjectComLib()
			: m_pObj(NULL)
		{}

		DECLARE_PROTECT_FINAL_CONSTRUCT()

		HRESULT FinalConstruct()
		{
			return S_OK;
		}

		void FinalRelease() 
		{
		}

	public:

		STDMETHOD(ObjectCreate)(void);
		STDMETHOD(ObjectFree)(void);
		STDMETHOD(InvokeMethod)(void);
		STDMETHOD(InvokeObjectMethod)(BSTR, BSTR*);
		STDMETHOD(InvokeCallback)(CHAR*, CHAR*);
		STDMETHOD(ObjectDllMethod)(void);
		STDMETHOD(ObjectDllFunction)(BSTR, BSTR*);
		STDMETHOD(ObjectDllCallback)(CHAR*);
		STDMETHOD(Initialize)(VARIANT*);

	private:

		CObjectDll* m_pObj;
	};
}
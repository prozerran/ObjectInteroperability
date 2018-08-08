// ObjectCom.cpp : Implementation of DLL Exports.
/*
Creating a COM Dll
============================================
1. Add -> New Project -> C++/ATL -> Support COM+/Registrar
2. Add -> Class -> ATL Simple Object
3. Class View -> IObjectComLib -> Add Method
4. Keeping doing [3] until all methods added
5. Implement added methods
6. Use COM externally
*/

#include "stdafx.h"
#include "resource.h"

// The module attribute causes DllMain, DllRegisterServer and DllUnregisterServer to be automatically implemented for you
[ module(dll, uuid = "{95E54DE2-9DA6-4D83-8A7A-11683E15E855}", 
		 name = "ObjectCom", 
		 helpstring = "ObjectCom 1.0 Type Library",
		 resource_name = "IDR_OBJECTCOM") ]
class CObjectComModule
{
public:
// Override CAtlDllModuleT members
};
		 

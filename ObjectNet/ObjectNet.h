// ObjectNet.h

#pragma once

#include "ObjectDll.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace XInterface;
using namespace System;

namespace ObjectNet 
{
	public ref class CObjectNet
	{
	public:

		static int  ObjectDllMethod();
		static void ObjectDllFunction(String^ str, String^% res);
		static void ObjectDllCallback(IntPtr^ cb_ptr);

	public:

		CObjectNet();

		void ObjectCreate();
		void ObjectFree();

		void InvokeMethod();
		void InvokeCallback(IntPtr^ cb_ptr, IntPtr^ user_data);

	private:

		CObjectDll*		m_pObj;
	};
}

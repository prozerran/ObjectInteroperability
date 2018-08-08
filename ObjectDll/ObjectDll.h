// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the OBJECTDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// OBJECTDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifdef OBJECTDLL_EXPORTS
#define OBJECTDLL_API __declspec(dllexport)
#else
#define OBJECTDLL_API __declspec(dllimport)
#endif

#define MAX_BUFF_STR_SIZE 256

namespace XInterface
{
	// exported global var
	extern OBJECTDLL_API int nObjectDll;

	// Object Base class
	class CObjectDllBase {
	public:

		// TODO: add your pure virtual methods here.
		virtual int InvokeMethod() const = 0;
		virtual int InvokeMethod(const char*, char*, int) const = 0;

		// object callback interface
		typedef void (__stdcall* CallbackMethod)(const char*, void*);
		virtual void InvokeCallback(CallbackMethod, void*) = 0;
	};

	// This class is exported from the ObjectDll.dll
	class OBJECTDLL_API CObjectDll : public CObjectDllBase {
	public:

		CObjectDll();

		// TODO: add your methods here.
		int InvokeMethod() const;
		int InvokeMethod(const char* str, char* res, int size) const;

		// demonstrate object callback
		void InvokeCallback(CallbackMethod funcname, void* context);

	private:

		CallbackMethod m_callback;
	};

	// exported functions to be accessed externally
	extern "C"
	{
		// ordinary functions
		OBJECTDLL_API int	ObjectDllMethod();
		OBJECTDLL_API int	ObjectDllFunction(const char* str, char* res, int size);

		// demonstrate callback
		typedef void  (__stdcall* CallbackFunc)(const char*);
		OBJECTDLL_API void  __stdcall ObjectDllCallback(CallbackFunc funcname);

		// virtual class object./
		OBJECTDLL_API void* ObjectDllCreate();
		OBJECTDLL_API void	ObjectDllFree(void* pObj);
		OBJECTDLL_API void	ObjectDllInvokeMethod(void* pObj);

		// wrapper for class callback
		typedef void (__stdcall* CallbackMethod)(const char*, void*);
		OBJECTDLL_API void	__stdcall ObjectDllInvokeCallback(void* pObj, CallbackMethod funcname, void* context);
	};

	// exported typedefs to be accessed externally [one defined for each exported declaration]
	typedef int	  (*LPFUNC)(const char*, char*, int);
	typedef void  (*LPCALLBACKFUNC)(CallbackFunc);
	typedef void  (*LPCALLBACKMETHOD)(CallbackMethod);

	typedef void* (*LPOBJECTCREATE)(void);
	typedef void  (*LPOBJECTFREE)(void*);
};

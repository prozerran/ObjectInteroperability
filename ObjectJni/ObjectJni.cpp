// ObjectJni.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ObjectDll.h"
#include "ObjectJni.h"
#include <stdlib.h>

using namespace XInterface;

/* Global Variables */
CObjectDll* g_pObj = NULL;
char* g_Str = NULL;

struct MyCallbackObj
{
	jclass		m_cls;
	jmethodID	m_mid;
	JNIEnv*		m_env;
	jobject		m_obj;
	jobject		m_context;
};

void __stdcall MyCallbackFunc(const char* str)
{
	g_Str = (char*) str;
}

void __stdcall MyCallbackMethod(const char* str, void* context)
{
	MyCallbackObj* pCallObj = static_cast<MyCallbackObj*>(context);

	if (pCallObj)
	{
		jstring jStr = pCallObj->m_env->NewStringUTF(str);
		pCallObj->m_env->CallVoidMethod(pCallObj->m_obj, pCallObj->m_mid, jStr);
	}
}

JNIEXPORT jboolean JNICALL Java_ObjectJni_ObjectCreate(JNIEnv *env, jobject obj)
{
	if (!g_pObj)
	{
		g_pObj = (CObjectDll*) ObjectDllCreate();
	}
	return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_ObjectJni_ObjectDllMethod(JNIEnv *env, jobject obj)
{
	ObjectDllMethod();
	return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_ObjectJni_ObjectDllFunction(JNIEnv *env, jobject obj, jstring str, jobject res)
{
	char pRes[MAX_BUFF_STR_SIZE] = {0};
	const char* pStr = env->GetStringUTFChars(str, JNI_FALSE);
	ObjectDllFunction(pStr, pRes, sizeof(pRes));

	jclass jc = env->GetObjectClass(res);
	jmethodID mid = env->GetMethodID(jc, "append", "(Ljava/lang/String;)Ljava/lang/StringBuffer;");
	jstring js = env->NewStringUTF(pRes);

	env->CallObjectMethod(res, mid, js);
	env->ReleaseStringUTFChars(str, pStr);
	return JNI_TRUE;
}

JNIEXPORT jboolean JNICALL Java_ObjectJni_InvokeMethod(JNIEnv *env, jobject obj)
{
	if (g_pObj)
	{
		g_pObj->InvokeMethod();
	}
	return JNI_TRUE;
}

JNIEXPORT jstring JNICALL Java_ObjectJni_InvokeObjectMethod(JNIEnv *env, jobject obj, jstring str)
{
	if (g_pObj)
	{
		char pRes[MAX_BUFF_STR_SIZE] = {0};
		const char *pStr = env->GetStringUTFChars(str, JNI_FALSE);
		g_pObj->InvokeMethod(pStr, pRes, sizeof(pRes));
		env->ReleaseStringUTFChars(str, pStr);

		if (strlen(pRes) > 0)
		{
			return env->NewStringUTF(pRes);		
		}
	}
	return 0;
}

JNIEXPORT jboolean JNICALL Java_ObjectJni_ObjectDllCallback(JNIEnv *env, jobject obj)
{
	jclass jc = env->GetObjectClass(obj);
	jmethodID mid = env->GetMethodID(jc, "MyCallbackMethod", "(Ljava/lang/String;)V");
	ObjectDllCallback(MyCallbackFunc);

	if (g_Str)
	{
		jstring jStr = env->NewStringUTF(g_Str);
		env->CallVoidMethod(obj, mid, jStr);
		return JNI_TRUE;
	}
	return JNI_FALSE;
}

JNIEXPORT jboolean JNICALL Java_ObjectJni_ObjectDllInvokeCallback(JNIEnv *env, jobject obj, jobject user_data)
{
	if (g_pObj)
	{
		MyCallbackObj mObj;

		mObj.m_obj = obj;
		mObj.m_env = env;
		mObj.m_context = user_data;
		mObj.m_cls = env->GetObjectClass(obj);

		// check Java VM Type Signatures for 3rd param ... (Sig)ReturnType
		mObj.m_mid = env->GetMethodID(mObj.m_cls, "MyCallbackMethod", "(Ljava/lang/String;)V");
		g_pObj->InvokeCallback(MyCallbackMethod, &mObj);
		return JNI_TRUE;
	}
	return JNI_FALSE;
}

JNIEXPORT jboolean JNICALL Java_ObjectJni_ObjectFree(JNIEnv *env, jobject obj)
{
	if (g_pObj)
	{
		ObjectDllFree(g_pObj);
		g_pObj = NULL;
	}
	return JNI_TRUE;
}
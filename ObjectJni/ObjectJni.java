 /*
 Steps to make Java JNI execute
 
 - Write the ObjectJni java class [current file]
 - Execute ObjectJni.bat [compile + genereate header file]
	- jvc ObjectJni.java
	- javah -jni ObjectJni
 - Implement the C/C++ ObjectJni.cpp file base on the generated header file
 - Might need to modify <jni.h> to "jni.h" in header file
 - Compile the ObjectJni.dll [use MS Visual Studio]
 - Test run with ObjectJniTest_Java.bat
	- jview TestJNI
 */

 class ObjectJni
 {
     private native boolean ObjectCreate();
     private native boolean InvokeMethod();
	 private native String  InvokeObjectMethod(String str);
     private native boolean ObjectDllMethod();
     private native boolean ObjectDllCallback();
     private native boolean ObjectDllFunction(String str, StringBuffer res);
     private native boolean ObjectDllInvokeCallback(Object obj);
     private native boolean ObjectFree();

     static
     {
         System.loadLibrary("ObjectJni");
     }

	 private void MyCallbackMethod(String str)
	 {
         System.out.println(str);
	 }

     public static void main(String[] args)
     {
         ObjectJni pObj = new ObjectJni();
		 pObj.ObjectCreate();

		 // ordinary methods
		 pObj.ObjectDllMethod();
		 pObj.ObjectDllCallback();

		 StringBuffer res = new StringBuffer();
		 pObj.ObjectDllFunction("", res);
         System.out.println(res);

		 // class objects/methods
		 pObj.InvokeMethod();

		 String str = pObj.InvokeObjectMethod("ObjectJni::InvokeMethod ");
         System.out.println(str);

		 pObj.ObjectDllInvokeCallback(null);
         pObj.ObjectFree();
     }
 }
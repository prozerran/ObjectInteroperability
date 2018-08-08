using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace ObjectDllTest_CSharp
{
    public class Program
    {
        #region PInvokes

        // empty function
        [DllImport("ObjectDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        private static extern int ObjectDllMethod();

        // function params
        [DllImport("ObjectDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.I4)]
        private static extern int ObjectDllFunction(string str, StringBuilder res, int size);

        // test callback
        [DllImport("ObjectDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        private static extern void ObjectDllCallback(Callback funcname);
        private delegate void Callback(string text);

        // test class object
        [DllImport("ObjectDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        private static extern IntPtr ObjectDllCreate();

        [DllImport("ObjectDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        private static extern void ObjectDllFree(IntPtr pObj);

        // Either create C-function accessors or use visual studio dumpbin to get the method entry point
        // $ dumpbin /exports ObjectDll.dll
        [DllImport("ObjectDll.dll", CharSet = CharSet.Ansi, EntryPoint = "?InvokeMethod@CObjectDll@XInterface@@UBEHPBDPADH@Z", CallingConvention = CallingConvention.ThisCall)]
        [return: MarshalAs(UnmanagedType.I4)]
        private static extern int InvokeMethod(IntPtr pObj, string str, StringBuilder res, int size);

        // test object callback
        [DllImport("ObjectDll.dll", CharSet = CharSet.Ansi, EntryPoint = "?InvokeCallback@CObjectDll@XInterface@@UAEXP6GXPBDPAX@Z1@Z", CallingConvention = CallingConvention.ThisCall)]
        private static extern void ObjectDllInvokeCallback(IntPtr pObj, ObjectCallback funcname, object obj);
        private delegate void ObjectCallback(string text, IntPtr pObj);

        #endregion PInvokes

        // Message returned from DLL
        private static void MyCallBackFunc(string text)
        {
            Console.WriteLine(text);
        }

        private static void MyCallbackMethod(string text, IntPtr obj)
        {
            Console.WriteLine(text);
        }

        static void Main(string[] args)
        {
            // empty function
            ObjectDllMethod();

            // ordinary function
            var res = new StringBuilder(256);
            ObjectDllFunction("", res, res.Capacity);
            Console.WriteLine(res.ToString());

            // test callback
            Callback CallbackInstance = new Callback(MyCallBackFunc);
            ObjectDllCallback(CallbackInstance);            

            // test class objects
            IntPtr pObj = ObjectDllCreate();
            if (pObj != IntPtr.Zero)
            {
                InvokeMethod(pObj, "", res, res.Capacity);
                Console.WriteLine(res.ToString());

                ObjectCallback ObjectCallbackInstance = new ObjectCallback(MyCallbackMethod);
                ObjectDllInvokeCallback(pObj, ObjectCallbackInstance, null); 

                ObjectDllFree(pObj);
                pObj = IntPtr.Zero;
            }
        }
    }
}

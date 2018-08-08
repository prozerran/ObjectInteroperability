using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ObjectNet;
using System.Runtime.InteropServices;

namespace ObjectNetTest_CSharp
{
    class Program : IDisposable
    {
        private delegate void CallbackMethod(string text, IntPtr obj);
        private delegate void CallbackFunction(string text);

        private static GCHandle gch_cb_meth;
        private static GCHandle gch_cb_func;

        ~Program()
        {
            CleanUp();
        } 

        public void Dispose()
        {
            CleanUp();
        }

        public void CleanUp()
        {
            if (gch_cb_func.IsAllocated)
                gch_cb_func.Free();

            if (gch_cb_meth.IsAllocated)
                gch_cb_meth.Free();
        }

        private static void MyCallbackFunc(string text)
        {
            Console.WriteLine(text);
        }

        private static void MyCallbackMethod(string text, IntPtr user_data)
        {
            //object pObj = (object) ((GCHandle) user_data).Target;
            Console.WriteLine(text);
        }

        static void Main(string[] args)
        {
            try
            {
                // access ordinary functions
                CObjectNet.ObjectDllMethod();

                string res = string.Empty;
                CObjectNet.ObjectDllFunction("", ref res);
                Console.WriteLine(res);

                // now do the function callback
                CallbackFunction cb_func = MyCallbackFunc;
                IntPtr cb_func_ptr = Marshal.GetFunctionPointerForDelegate(cb_func);
                gch_cb_meth = GCHandle.Alloc(cb_func);
                GC.Collect();
                CObjectNet.ObjectDllCallback(cb_func_ptr);

                // access class/members
                CObjectNet pObj = new CObjectNet();                
                pObj.ObjectCreate();
                pObj.InvokeMethod();

                // now do the method callback
                CallbackMethod cb_meth = MyCallbackMethod;
                IntPtr cb_meth_ptr = Marshal.GetFunctionPointerForDelegate(cb_meth);
                gch_cb_meth = GCHandle.Alloc(cb_meth);
                GC.Collect();

                IntPtr user_data = (IntPtr)GCHandle.Alloc(pObj);
                pObj.InvokeCallback(cb_meth_ptr, user_data);
                pObj.ObjectFree();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);      	
            }
        }
    }
}

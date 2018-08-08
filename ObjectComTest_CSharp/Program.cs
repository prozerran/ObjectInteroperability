using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

using ObjectCom;

namespace ObjectComTest_CSharp
{
    public class Program : IDisposable
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

        private static void MyCallbackMethod(string text, IntPtr user_data)
        {
            //CObjectNet pObj = (CObjectNet)Marshal.PtrToStructure(user_data, typeof(CObjectNet));
            Console.WriteLine(text);
        }

        static void Main(string[] args)
        {
            try
            {
                string res = string.Empty;

                IObjectComLib pObj = new CObjectComLib();
                pObj.ObjectCreate();

                // call some ordinary functions
                pObj.ObjectDllMethod();
                pObj.ObjectDllFunction("", ref res);
                Console.WriteLine(res);

                // call member functions
                pObj.InvokeMethod();
                pObj.InvokeObjectMethod("CObjectComLib::InvokeObjectMethod ", ref res);
                Console.WriteLine(res);

                // now do the method callback
                CallbackMethod cb_meth = MyCallbackMethod;
                IntPtr cb_meth_ptr = Marshal.GetFunctionPointerForDelegate(cb_meth);
                gch_cb_meth = GCHandle.Alloc(cb_meth);
                GC.Collect();

                //IntPtr user_data = (IntPtr) GCHandle.Alloc(pObj);
                //pObj.InvokeCallback(cb_meth_ptr, user_data);  // user_data.ToPointer()                
                // TODO...
                //pObj.Initialize(pObj);

                pObj.ObjectFree();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
        }
    }
}

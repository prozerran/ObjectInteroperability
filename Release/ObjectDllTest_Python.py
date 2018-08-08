from ctypes import *

# Use cdll for functions compiled with __cdecl
#

# Import the DLL library
ObjectDllLibrary  = cdll.LoadLibrary('ObjectDll.dll')

# Load the function from the DLL
ObjectDllMethod = ObjectDllLibrary.ObjectDllMethod
ObjectDllFunction = ObjectDllLibrary.ObjectDllFunction
ObjectDllFunction.res_type = c_int

# Create buffer with size
maxint = 100
retstr = create_string_buffer(maxint)

# Call the DLL external methods
ObjectDllMethod()
ObjectDllFunction('', retstr, maxint)

# print result
print retstr.value

"""
# Function callback
#
# Define a callback function type, as a function that returns
# void and takes a single integer as an argument
#
ObjectDllCallback = ObjectDllLibrary.ObjectDllCallback

CB_FUNC_TYPE = CFUNCTYPE(None)

def MyCallbackFunc(arg):
    print arg

# Wrap foo in CB_FUNC_TYPE to pass it to ctypes
cb_func = CB_FUNC_TYPE(MyCallbackFunc)

# Finally, call test_cb with our callback. Note the printed
# output
#
ObjectDllCallback(cb_func)
"""


# C++ Class object access
#
class CObjectDll(object):
    def __init__(self):
        self.obj = ObjectDllLibrary.ObjectDllCreate()

    def InvokeMethod(self):
        ObjectDllLibrary.ObjectDllInvokeMethod(self.obj)        
        
    def ObjectDllFree(self):
        ObjectDllLibrary.ObjectDllFree(self.obj)          
        
pObj = CObjectDll()
pObj.InvokeMethod()
pObj.ObjectDllFree()
























        
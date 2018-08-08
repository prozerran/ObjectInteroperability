# Object Interoperability
C++ DLL / COM / .NET Interoperability, managed vs unmanaged code, cross library function calling, methods, and function callbacks

This is a sample showing interoperability between C++ Object DLLs, COM objects, and C# .NET methods. This uses advanced techniques, between managed and unmananged code.

At the base, we have a low level windows C++ DLL wraped in a object class, ObjectDLL, and the various examples on how to call the methods within this DLL using C++, both static and dynamic, in COM, both static and dynamic, as well as C# .NET.

The base ObjectDLL C++ class library contains the following 4 sample access functions that will be callable from it's sub-programs (C++/COM/.NET)
- regular ordinary function
- ordinary callback function
- class member method
- class member callback function

With this, we will show several examples how to call these methods...
- externally from a C++ program statically and dynamically
- externally from a C# .NET program using PInvoke
- from an ObjectCOM COM adapter
- externally from COM library statically and dynamically
- externally from C# .NET program that references the ObjectCOM library
- from managed C++ wrapper ObjectNet
- externally from C# .NET program that references the ObjectNet managed library
- from an ObjectJNI JAVA wrapper
- from sample JAVA program
- from sample Python program


# Usability
Due to the complex coding involved, this project was originally written in Visual Studio 2010 and works best under VS2010, I have tried to upgrade this to modern community versions but there seem to have compatability issues. I leave it up to you guys to decide how to manage this. 

# Contributions
For those that want to contribute to the enhancement of the project, please contact me, as there are many things that can be changed/added, such as porting the code to a modern VS version, adding more interopability with other languages, etc.



@echo off

echo.
echo *** Testing [C++ Static]
.\ObjectDllTest_Static.exe

echo.
echo *** Testing [C++ Dynamic]
.\ObjectDllTest_Dynamic.exe

echo.
echo *** Testing [C# P/Invoke]
.\ObjectDllTest_CSharp.exe

echo.
echo *** Testing [C# .NET]
.\ObjectNetTest_CSharp.exe

echo.
echo *** Testing [COM Static]
.\ObjectComTest_Static.exe

echo.
echo *** Testing [COM Dynamic]
.\ObjectComTest_Dynamic.exe

echo.
echo *** Testing [COM CSharp]
.\ObjectComTest_CSharp.exe

echo.
echo *** Testing [Java JNI]
.\ObjectJniTest_Java.bat

echo.
echo *** Testing [Python]
.\ObjectDllTest_Python.bat
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

REM echo.
REM echo *** Testing [COM Static]
REM .\ObjectComTest_Static.exe

REM echo.
REM echo *** Testing [COM Dynamic]
REM .\ObjectComTest_Dynamic.exe

REM echo.
REM echo *** Testing [COM CSharp]
REM .\ObjectComTest_CSharp.exe

REM echo.
REM echo *** Testing [Java JNI]
REM .\ObjectJniTest_Java.bat

REM echo.
REM echo *** Testing [Python]
REM .\ObjectDllTest_Python.bat
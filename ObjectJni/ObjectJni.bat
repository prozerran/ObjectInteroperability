@echo off

Set JPROJ="ObjectJni"
set JPATH="C:\Program Files (x86)\Java\jdk1.8.0_20\bin"

%JPATH%\javac %JPROJ%.java -d ..\Release
%JPATH%\javah -jni %JPROJ%

@echo off
echo =================================
echo = Building RedBoxApp on Windows =
echo =================================

set OPENALDIR=C:\Program  Files\OpenAL 1.1 SDK\

C:\MinGW\msys\1.0\bin\bash --login "%CD:\=\\%\\script\\Windows\\compile-windows.sh" "%CD:\=\\%"

pause

@echo on

@echo off
echo =================================
echo = Cleaning RedBox on Windows    =
echo =================================


C:\MinGW\msys\1.0\bin\bash --login -c "rm -rf '%CD:\=\\%\\build' && echo done..."

pause

@echo on

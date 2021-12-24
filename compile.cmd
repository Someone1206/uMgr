g++ src\*.cpp -o bin\Debug\Win32\_uMgr.exe -w 
@echo off
rem -mwindows

if "%1"=="/r" (
	cd bin\Debug\Win32\
	_uMgr.exe
	cd ..\..\..\
)
@echo off

if (%QTDIR%)==() set QTDIR=C:\Qt\4.7.2
if (%VSCOMNTOOLS%)==() set VSCOMNTOOLS="%VS120COMNTOOLS%"

if (%SIS_ROOT%)==() set SIS_ROOT=%CURRENT_PATH%\..
if (%SRC_RELATIVE_PATH%)==() set SRC_RELATIVE_PATH=src
if (%BUILD_OUTPUT%)==() set BUILD_OUTPUT=build\%SISConfiguration%x%SISPlatformArchitecture%

if (%SISConfiguration%)==(debug) 
(	set SISBuildPostfix=g	) 
else 
(	set SISBuildPostfix=O	)

call "%VSCOMNTOOLS:"=%..\..\VC\vcvarsall.bat" amd64

echo -- QTDIR set to %QTDIR%
echo -- WORKING_ROOT set to %WORKING_ROOT%
echo -- SRC_RELATIVE_PATH set to %SRC_RELATIVE_PATH%
echo -- BUILD_OUTPUT set to %BUILD_OUTPUT%

echo -- SISConfiguration set to %SISConfiguration%
echo -- SISPlatformArchitecture set to %SISPlatformArchitecture%
echo -- SISBuildPostfix set to %SISBuildPostfix%

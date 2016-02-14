set CURRENT_PATH=%cd%
set VSCOMNTOOLS="%VS120COMNTOOLS%"

call SetBuildEnv.bat

call devenv
pause
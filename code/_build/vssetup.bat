:: BATCH doesn't have logical or, otherwise I'd use it
echo Setting up VS environment

SET platform=
IF /I [%PROCESSOR_ARCHITECTURE%]==[amd64] set platform=true
IF /I [%PROCESSOR_ARCHITEW6432%]==[amd64] set platform=true



:: default to VS2012 = 12.0
:: the Environment variable VisualStudioVersion is set by devenv.exe
:: if this batch is a child of devenv.exe external tools, we know which version to look at
if not defined VisualStudioVersion SET VisualStudioVersion=14.0

if defined platform (
set VSREGKEY=HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\VisualStudio\%VisualStudioVersion%
)  ELSE (
set VSREGKEY=HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\VisualStudio\%VisualStudioVersion%
)


for /f "skip=2 tokens=2,*" %%A in ('reg query "%VSREGKEY%" /v InstallDir') do SET VSINSTALLDIR=%%B
	
call "%VSINSTALLDIR%\..\Tools\vsvars32.bat"

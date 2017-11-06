@echo off

call vssetup.bat
SET PREMAKEDIR="..\src\tools\premake"

%PREMAKEDIR%\premake5 vs2015 generate

pause
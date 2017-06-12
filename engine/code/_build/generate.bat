@echo off

SET PREMAKEDIR="..\..\tools\premake\bin\release"

%PREMAKEDIR%\premake5 vs2015 generate

pause
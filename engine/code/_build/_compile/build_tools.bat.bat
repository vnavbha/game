@echo off

SET PREMAKEDIR="../../external/premake/premake-4.4-beta5-src/premake-4.4-beta5"
%PREMAKEDIR%\premake4 --file="../premake4.lua" --vs=120

pause
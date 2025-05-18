@echo off
setlocal enabledelayedexpansion
set BIN_DIR=bin
set SRC_DIR=src
set LIB_DIR=lib

if not exist %BIN_DIR% mkdir %BIN_DIR%

rem Build classpath from all jars in lib
set CP=%LIB_DIR%\*

rem Collect all java files
(for /r %SRC_DIR% %%f in (*.java) do @echo %%f) > sources.txt

rem Compile
javac -d %BIN_DIR% -cp %CP% @sources.txt
if errorlevel 1 exit /b 1

rem Determine test classes
set TESTS=
for /f %%f in ('dir /b /s %SRC_DIR%\test\java\*Test.java') do (
  set file=%%f
  set class=!file:%SRC_DIR%\test\java\=!
  set class=!class:.java=!
  set class=!class:\=.!
  set TESTS=!TESTS! !class!
)

java -cp "%BIN_DIR%;%CP%" org.junit.runner.JUnitCore %TESTS%
if errorlevel 1 exit /b 1

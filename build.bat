@echo off
setlocal

REM === Set GBDK path ===
set GBDK_PATH=F:/retro_dev/gbdk

REM === Source files ===
set SRC=src\main.c src\game\entities\submarine.c src\game\entities\harpoon.c src\tiles\submarine.c

REM === Output ROM ===
set OUT=build\deep2d.gb

echo Compiling %SRC%...
"%GBDK_PATH%\bin\lcc" -o %OUT% %SRC%

if %errorlevel% neq 0 (
    echo.
    echo Compilation failed.
    exit /b %errorlevel%
)

echo.
echo Compilation successful: %OUT%

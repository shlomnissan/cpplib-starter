@echo off

set ERRLEV=0
set BUILD_DIR=%1
if "%BUILD_DIR%"=="" set BUILD_DIR=build
set DOCS_DIR=%BUILD_DIR%\html

echo Generating Doxygen documentation

:: Determine the script's location
set "SCRIPT_DIR=%~dp0"

:: Move to the root directory (parent of the "scripts" folder)
cd /d "%SCRIPT_DIR%.."

:: Ensure build directory exists and CMake is configured
if not exist "%BUILD_DIR%\Makefile" (
    if not exist "%BUILD_DIR%\build.ninja" (
        echo Configuring CMake
        cmake -S . -B "%BUILD_DIR%" || goto :error
    )
)

:: Build the Doxygen target
cmake --build "%BUILD_DIR%" --target doxygen || goto :error

:: Verify output
if exist "%DOCS_DIR%\index.html" (
    echo Documentation generated at: %DOCS_DIR%\index.html
) else (
    echo Documentation generation failed: %DOCS_DIR%\index.html not found.
    exit /b 1
)

exit /b 0

:error
echo An error occurred. Exiting.
exit /b 1
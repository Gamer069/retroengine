@echo off

:setColor
echo %~2%1%~0
exit /b

call :setColor "Generating unix makefile..." 93
cmake . > nul 2>&1
call :check_fail

call :setColor "Making..." 93
make > nul 2>&1
call :check_fail

call :setColor "Installing sandbox to path..." 93
make -f install.mk > nul 2>&1
call :check_fail

exit /b

:check_fail
if %errorlevel% neq 0 (
    call :setColor "FAILED" 91
    exit /b 1
) else (
    call :setColor "SUCCESS" 92
    exit /b 0
)


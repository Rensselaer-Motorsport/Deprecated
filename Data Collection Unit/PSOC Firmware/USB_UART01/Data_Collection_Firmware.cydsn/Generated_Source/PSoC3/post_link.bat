@REM This script allows a 3rd party IDE to use CyHexTool to perform
@REM any post processing that is necessary to convert the raw flash
@REM image into a complete hex file to use in programming the PSoC.
@REM USAGE: post_link.bat
@REM    arg1: Persistant path back to the directory containing the app project.
@REM    arg2: Path (relative to arg1) of the directory where the hex files go.
@REM    arg3: Name of the project.
@REM NOTE: This script is auto generated. Do not modify.

"C:\Program Files (x86)\Cypress\PSoC Creator\3.0\PSoC Creator\bin\cyvalidateide.exe" -dev CY8C3866AXI-040 -ide "%~1\%~3" -flsAddr 0x0 -flsSize 0x10000 -sramAddr 0x0 -sramSize 0x2000
@IF %errorlevel% NEQ 0 EXIT /b %errorlevel% 
move "%~1\%~2\%~n3.hex" "%~1\%~2\%~n3.ihx"
@IF %errorlevel% NEQ 0 EXIT /b %errorlevel% 
"C:\Program Files (x86)\Cypress\PSoC Creator\3.0\PSoC Creator\import\gnu_cs\c8051\1.0\bin\c8051-elf-omf2elf.exe" "%~1\%~2\%~n3" "%~1\%~2\%~n3.elf"
@IF %errorlevel% NEQ 0 EXIT /b %errorlevel% 
"C:\Program Files (x86)\Cypress\PSoC Creator\3.0\PSoC Creator\bin\cyhextool" -o "%~1\%~2\%~n3.hex" -f "%~1\%~2\%~n3.ihx" -prot "%~dp0protect.hex" -id 1E028069 -a EEPROM=90200000:800,PROGRAM=00000000:10000,CONFIG=80000000:2000,PROTECT=90400000:40 -meta 0301 -cunv 0800C005 -wonv BC90ACAF -ecc OFF 
@IF %errorlevel% NEQ 0 EXIT /b %errorlevel% 
CD /D "C:\Keil\UV4"
@IF %errorlevel% NEQ 0 EXIT /b %errorlevel% 
IF NOT EXIST "C:\Users\leulbox\Documents\GitHub\Adaptable-Automotive-Sensor-Logger\Data Collection Unit\PSOC Firmware\USB_UART01\Data_Collection_Firmware.cydsn\Data_Collection_Firmware.svd" rem "C:\Users\leulbox\Documents\GitHub\Adaptable-Automotive-Sensor-Logger\Data Collection Unit\PSOC Firmware\USB_UART01\Data_Collection_Firmware.cydsn\Data_Collection_Firmware.sfr"
@IF %errorlevel% NEQ 0 EXIT /b %errorlevel% 

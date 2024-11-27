@echo off

:repeat
crctest.exe && goto :repeat
echo Failed!

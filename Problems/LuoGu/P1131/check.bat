@echo off
:loop
datamaker > data
own < data > wrong
std < data > right
fc right wrong
if not %errorlevel%==0 pause
goto loop
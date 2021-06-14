@echo off

rem midi2tones_64bit.exe は環境変数 Path に通しておく
set CONVERTER=midi2tones_64bit.exe

for %%i in (.\\*.mid) do %CONVERTER% %%~ni && del Score.h && ren %%~ni.c Score.h

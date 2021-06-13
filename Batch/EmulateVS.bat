@echo off

rem VisualStudio　でビルドしたファイル(ビルド構成\XXX.ino.hex)をエミュレータで起動する、ビルド構成は第一引数で指定
rem (Invoke emulator with binary which is compiled by VisualStudio, build configuration is specified by argument 1)

set EMULATOR=ProjectABE.exe

rem 第一引数(%1)でビルド構成を指定 (Argument %1 is build configuration)
for %%i in (.\%1\*.ino.hex) do %EMULATOR% %%~fi

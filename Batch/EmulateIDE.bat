@echo off

rem IDEでスケッチ - コンパイルしたバイナリを出力(Ctrl+Alt+S) で出力されたファイル(XXX.ino.arduino_leonardo.hex)をエミュレータで起動する

rem https://github.com/felipemanga/ProjectABE/releases
rem インストールして環境変数Pathに通しておく (Install and add to environment varibale Path)
set EMULATOR=ProjectABE.exe

rem ~dp0  : カレントディレクトリ
rem ~ni   : ベースネーム
rem ~di   : ドライブ
rem ~pi   : パス
rem ~fi   : フルパス
for %%i in (.\*.ino.arduino_leonardo.hex) do %EMULATOR% %%~fi

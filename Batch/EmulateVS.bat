@echo off

rem VisualStudioでビルドしたファイル(ビルド構成\XXX.ino.hex)をエミュレータで起動する、ビルド構成は第一引数で指定
rem (Invoke emulator with binary which is compiled by VisualStudio, build configuration is specified by argument 1)

rem https://github.com/felipemanga/ProjectABE/releases
rem インストールして環境変数Pathに通しておく (Install and add to environment varibale Path)
set EMULATOR=ProjectABE.exe

rem ~dp0  : カレントディレクトリ
rem ~ni   : ベースネーム
rem ~di   : ドライブ
rem ~pi   : パス
rem ~fi   : フルパス

rem 第一引数(%1)でビルド構成を指定 (Argument %1 is build configuration)
for %%i in (.\%1\*.ino.hex) do %EMULATOR% %%~fi

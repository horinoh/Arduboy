@echo off

rem https://github.com/felipemanga/ProjectABE/releases
rem インストールして環境変数Pathに通しておく (Install and add to environment varibale Path)
set EMULATOR=ProjectABE.exe

rem ~dp0  : カレントディレクトリ
rem ~ni   : ベースネーム
rem ~di   : ドライブ
rem ~pi   : パス
for %%i in (*.ino) do (
  rem IDEから「コンパイルしたバイナリを出力」した場合
  rem %EMULATOR% %~dp0\%%~ni.ino.arduino_leonardo.hex
  
  rem VisualStudioでビルドした場合(Debugビルド)
  %EMULATOR% %%~di%%~piDebug\%%~ni.hex
  rem VisualStudioでビルドした場合(Releaseビルド)
  rem %EMULATOR% %%~di%%~piRelease\%%~ni.hex
)


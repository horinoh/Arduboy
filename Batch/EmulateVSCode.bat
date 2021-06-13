@echo off

rem VSCode ではビルド後にバイナリは削除されてしまう、残しておくには　.vscode/arduino.json に以下のようなエントリを追加しておく
rem   "output": ".\\bin"
rem VSCode でコンパイルしたバイナリ(Ctrl + Alt + R) を出力、出力されたファイル(XXX.ino.arduino_leonardo.hex)をエミュレータで起動する
rem (Invoke emulator with binary which is compiled by VSCode)

set EMULATOR=ProjectABE.exe

for %%i in (.\\bin\\*ino.hex) do %EMULATOR% %%~fi

# Arduboy

## [IDE](https://www.arduino.cc/en/Main/Software#download)
### ライブラリ
* スケッチ - ライブラリをインクルード - ライブラリを管理 - 「Arduboy」で検索する
    ~~~
    Arduboy
    Arduboy2
    ArduboyTones
    ArduboyPlaytune
    ArdBitmap
    ArdVoice
    ATMlib
    Arduboy-TinyFont
    ~~~
### ボード
* ファイル - 環境設定 - 追加のボードマネージャのURLに以下を記述
    ~~~
    https://arduboy.github.io/board-support/package_arduboy_index.json 
    ~~~
* ツール - ボード - ボードマネージャ - Arduboyで検索してインストールする
* ツール - ボード - Arduboy-avr - Arduboyを選択しておく
* (USB接続してから)ツール - シリアルポート で Arduino Leonardo を選択

### 設定
* ファイル - 環境設定 - 外部のエディタを使用する にチェックを入れると編集できなくなり、(Visual Studio等)外部での変更を反映してくれるようになる

### サンプル
* ファイル - スケッチ例 から

## [VisualStudio](https://www.visualmicro.com/)
* Extensions - Manage Extensions - Arduino IDE for Visual Studio をインストール - Visual Studio 再起動
* Extensions - vMicro
    * General - Configure Arduion IDE locations - Arduion IDEをインストールしたパスを設定(多分自動設定済になっている)
    * IDE に Arduino 1.6/1.8 を選択する
    * Board に Arduino Leonardo を選択する

## [エミュレータ](https://github.com/felipemanga/ProjectABE)
* IDEから、スケッチ - コンパイルしたバイナリを出力 - XXX.ino.arduino_leonardo.hex というファイルができるので、これをProjectABEにドラッグドロップ
* XXX.ino.arduino_leonardo..hexが更新されると自動的に再読み込みしてくれるので、一度起動してしまえばそのままで良い

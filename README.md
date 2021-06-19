# Arduboy

## [IDE](https://www.arduino.cc/en/Main/Software#download)
* ここでは、WindowsApp版ではなく、Zip版をインストールした
* ファイル - 環境設定 - 言語設定 - English(English) にした
    * 日本語文字化け対応がめんどうなので
* ポータブル化
    * IDEインストール先に portable フォルダを作成する
    * 新しい環境に移行する際は portable フォルダを持っていけばよい

### 環境設定 
* ファイル - 環境設定 - スケッチブックの保存場所 へスケッチを配置したいフォルダを指定
* ファイル - 環境設定 - 外部のエディタを使用する にチェックを入れるとIDEからは編集できなくなり、外部での変更を反映してくれるようになるみたい

### ライブラリ
* スケッチ - ライブラリをインクルード - ライブラリを管理
    ~~~
    Arduboy
    Arduboy2
    ArduboyTones
    ArduboyPlaytune
    ArdBitmap
    ArdVoice
    ATMlib
    Arduboy-TinyFont

    FixedPoints
    ~~~
    
### ボード
* ファイル - 環境設定 - 追加のボードマネージャのURLに以下を記述
    ~~~
    https://arduboy.github.io/board-support/package_arduboy_index.json 
    ~~~
* ツール - ボード - Arduino Leonardo を選択しておく
* 予め Arduboy デバイスを接続しておく
* ツール - シリアルポートで、接続したArduboyデバイスを選択する
    * COM1(Arduino Leonardo) とか

### サンプル
* ファイル - スケッチ例 - Arduboy2 - Hello World 等

## エディタ

<!--
### [VisualStudio](https://www.visualmicro.com/)
* Extensions - Manage Extensions - Arduino IDE for Visual Studio をインストール - Visual Studio 再起動
* Extensions - vMicro
    * General - Configure Arduion IDE locations - Arduion IDEをインストールしたパスを設定(多分自動設定済になっている)
    * IDE に Arduino 1.6/1.8 を選択する
    * Board に Arduino Leonardo を選択する

#### 自前ライブラリ
* ライブラリの作成 (Visual Studio)
    * Arduino Library Projectで作成、ここではXXXとする
    * ファイルの追加をする場合は、srcフォルダ以下に配置されるように追加する
* ライブラリを使う側でやること (Visual Studioから使う場合)
    * ソリューションを右クリック - Add - Existing Project... - XXX.vcxitems を追加する
    * Referencesを右クリック - Add Reference... - XXXにチェックを入れる
*  ライブラリを使う側でやること (IDEから使う場合)
    * ファイル - 環境設定 - スケッチブックの保存場所 で指定したフォルダ内の libraries フォルダ以下にライブラリを配置する
    * IDEで、スケッチ - ライブラリをインクルード - 選択肢に(配置済だと)現れるようになるので選択する
-->

### VisualStudioCode
* 拡張機能のインストール
    * Arduino
    * arduino-snipepets
* 設定
    * 左下歯車 - Settings - User - Extensions - Arduino configration
        * Arduino: Path に IDE のインストール先パスを指定
    * Ctrl + Shift + P (もしくはF1) でコマンドパレットを開く
        * Arduino: Board Config (もしくは右下のステータスバーから\<Select Board Type\>)
            * Arudino Leonardo (Arduino AVR Borads) を選択
        * Arduino: Select Serial Port (もしくは右下のステータスバーから\<Select Serial Port\>)
            * 予め Arduboy デバイスを接続しておく
            * 接続したArduboyデバイスを選択する
                * COM1 (Microsoft) とか
        * Arduino: Examples
            * サンプルを開く
            * Eamples from Custom Libraries - Arduboy - HelloWorld など
* ビルド、実行
    * Ctrl + Alt + R (もしくは.inoを開いて右上のアイコンから)
        * ビルド
    * Ctrl + Alt + U　(もしくは.inoを開いて右上のアイコンから)
        * 実行(Arduboyへのアップロード)
    * ビルド後にバイナリは削除されてしまう
        * 残しておくには .vscode/arduino.json に以下のようなエントリを追加しておく
        ~~~
        "output": ".\\bin"
        ~~~
#### 自前ライブラリ
* ライブラリの作成 (MyLibという名前で作る場合)
    * MyLib フォルダを作成
    * MyLib\MyLib.h を追加 (必要に応じて MyLib.cpp やその他 XXX.h や XXX.cpp も追加)
* ライブラリの使用 
    * <IDEインストール先>\portable\sketchbook\libraries 以下に MyLib を配置する
    * もしくはシンボリックリンクを作っておいてもよい
        ~~~
        $mklink /d  <IDEインストール先>\portable\sketchbook\libraries\MyLib YYY\MyLib
        ~~~
    * IDEから Sketch - IncludeLibrary の選択肢に現れる事を確認する

## [エミュレータ](https://github.com/felipemanga/ProjectABE)
* ビルドすると *.ino.hex ができるので、これをProjectABEにドラッグドロップ
* バイナリが更新されると自動的に再読み込みしてくれるので、一度起動してしまえばそのままでよい
* ProjectABE.exe のフォルダを環境変数 Path に通しておいた

## ハードウエア
* 上を押したまま電源を入れるとフラッシュライトモード
    * やめるには再起動
    * スケッチのアップロードが上手くいかない時にも使う
* Bを押したまま電源を入れるとシステムコントロールモード (LEDが青になる)
    * Bはホールドしておく必要がある
    * 上でオーディオを有効化(LEDが一回緑になる)
    * 下でオーディオを無効化(LEDが一回赤になる)

----
* This software includes the work that is distributed in the Apache License 2.9
<!--
TODO
    Math
        四元数
        テーブル使用サインコサイン
        DistanceFunctions
        ParametericSurface

    スプライト
        コンバーターの使用
        表示

    LED
        digitalWriteRGB(RGB_ON, RGB_OFF, RGB_OFF);
        digitalWriteRGB(RED_LED, RGB_ON);digitalWriteRGB(GREEN_LED, RGB_OFF);digitalWriteRGB(BLUE_LED, RGB_OFF);

        setRGBled(255, 0, 0);
        setRGBled(RED_LED, 255);setRGBled(RED_GREEN, 0);setRGBled(RED_BLUE, 0);

    EEPROM
        EEPROM_STORAGE_SPACE_START 以降がアプリから使用可能
        	    arduboy.print("\nEEPROM = ");
			arduboy.print(EEPROM_STORAGE_SPACE_START+1);
			arduboy.print(" = ");
			arduboy.print(EEPROM.read(EEPROM_STORAGE_SPACE_START));
    
    オーディオ
        Arduboy2Audio::enabled(),on(),off(),toggle()
        //ArduboyPlaytuneand ArduboyTones でonである必要がある
        if (!Arduboy2Audio::enabled()) {
		 Arduboy2Audio::on();
	    }
-->
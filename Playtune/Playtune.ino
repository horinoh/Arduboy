#include <Arduboy2.h>
#include <ArduboyPlaytune.h>

Arduboy2 arduboy;
ArduboyPlaytune tunes(arduboy.audio.enabled);

//!< midi2tones (https://github.com/MLXXXp/midi2tones) で MIDI ファイルをコードへ変換
//!< XXX.mid の場合、以下のように拡張子を省略してベースネームで引数に指定する
//!< $midi2tones_64bit.exe XXX
//!< XXX.c が出力されるので、ソースへ取り込んで使う (ここでは Score.h へリネームしてインクルードしている)
#include "Score.h"

// the setup function runs once when you press reset or power the board
void setup() {
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(60);

	tunes.initChannel(PIN_SPEAKER_1);
  	tunes.initChannel(PIN_SPEAKER_2);
	//!< トーンの再生中、スコアをミュートする場合には ture
	tunes.toneMutesScore(false);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (arduboy.nextFrame()) {
		arduboy.clear();

		if(!tunes.playing()) {
			tunes.playScore(score);
		}

		arduboy.setCursor(0, 0);
		arduboy.print(arduboy.audio.enabled() ? "Sound Enabled" : "Sound Disabled");
		
		arduboy.display();
	}
}

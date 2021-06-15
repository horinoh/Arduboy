#include <Arduboy2.h>
#include <ArduboyPlaytune.h>

Arduboy2 arduboy;
ArduboyPlaytune tunes(arduboy.audio.enabled);

//!< 【MIDIのコンバート】
//!< midi2tones (https://github.com/MLXXXp/midi2tones) で MIDI ファイルをコードへ変換
//!< XXX.mid の場合、以下のように拡張子を省略してベースネームで引数に指定する
//!< $midi2tones_64bit.exe XXX
//!< XXX.c が出力されるので、ソースへ取り込んで使う (ここでは Score.h へリネームしてインクルードしている)

#define PLAY(channel, duration) TUNE_OP_PLAYNOTE | channel, duration
#define STOP(channel) TUNE_OP_STOPNOTE | channel
#define WAIT(duration) (duration & 0x7f00) >> 8, duration & 0x00ff

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

	tunes.playScore(score);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (arduboy.nextFrame()) {
		arduboy.clear();

		arduboy.pollButtons();

		if(arduboy.justPressed(A_BUTTON)){
			if(!tunes.playing()) {
				tunes.playScore(score);
			}
		}
		if(arduboy.justPressed(B_BUTTON)){
			if(tunes.playing()) {
				tunes.stopScore();
			}
		}

		arduboy.setCursor(0, 0);
		arduboy.print(arduboy.audio.enabled() ? "Sound Enabled" : "Sound Disabled");
		
		arduboy.display();
	}
}

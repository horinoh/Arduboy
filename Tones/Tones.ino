/*
 Name:		HelloWorld.ino
 Created:	10/10/2020 3:48:18 PM
 Author:	horin
*/

#include <Arduboy2.h>
#include <ArduboyTones.h>

Arduboy2 arduboy;
ArduboyTones tones(arduboy.audio.enabled);

//!< 【MIDIのコンバート】
//!< midi2tones (https://github.com/MLXXXp/midi2tones) で MIDI ファイルをコードへ変換
//!< XXX.mid の場合、以下のように拡張子を省略してベースネームで引数に指定する
//!< $midi2tones_64bit.exe -o2 XXX
//!< XXX.c が出力されるので、ソースへ取り込んで使う (ここでは Score.h へリネームしてインクルードしている)
#include "Score.h"

//!< const PROGMEM でないスコアは tonesInRAM() で再生する (スコアを動的に変化させる場合等に使用)
uint16_t inRAM[] = {
  NOTE_E4,400, NOTE_D4,200, NOTE_C4,400, NOTE_REST,200, NOTE_D4,200,
  NOTE_C4,300, NOTE_REST,100, NOTE_C4,300, NOTE_REST,100, NOTE_E4,300,
  NOTE_REST,100, NOTE_G4,300, NOTE_REST,100, NOTE_F4,300, NOTE_REST,100,
  NOTE_A4,300, NOTE_REST,100, NOTE_D5H,200, NOTE_REST,200, NOTE_D5H,200,
  NOTE_REST,1500,
  TONES_REPEAT
};

// the setup function runs once when you press reset or power the board
void setup() {
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(60);

	tones.volumeMode(VOLUME_IN_TONE);
	//tones.volumeMode(VOLUME_ALWAYS_NORMAL);
	//tones.volumeMode(VOLUME_ALWAYS_HIGH);
	
	tones.tones(score);
	//tones.tonesInRAM(inRAM);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (arduboy.nextFrame()) {
		arduboy.clear();

		arduboy.pollButtons();

		if(arduboy.justPressed(A_BUTTON)){
			if(!tones.playing()) {
				tones.tones(score);
				//tones.tonesInRAM(inRAM);
			}
		}
		if(arduboy.justPressed(B_BUTTON)){
			if(tones.playing()) {
				tones.noTone();
			}
		}

		arduboy.setCursor(0, 0);
		arduboy.print(arduboy.audio.enabled() ? "Sound Enabled" : "Sound Disabled");

		arduboy.display();
	}
}

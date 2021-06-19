#include <Arduboy2.h>
#include <ArduboyTonesPitches.h>

Arduboy2 arduboy;

BeepPin1 beepPin1;
BeepPin2 beepPin2;

// the setup function runs once when you press reset or power the board
void setup() {
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(60);
	
	//!< 【サウンドの有効無効化】
	//!< B を押したままパワーをオンにする
	//!< (B は押したままで)上を押すとサウンド有効
	//!< (B は押したままで)下を押すとサウンド無効
	//if(!arduboy.audio.enabled()) { arduboy.audio.on(); }

	beepPin1.begin();
	beepPin2.begin();
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (arduboy.nextFrame()) {
		arduboy.clear();

		if (arduboy.audio.enabled()) {
			arduboy.pollButtons();
			beepPin1.timer();
			beepPin2.timer();
	
			constexpr auto Duration = 100;

			if (arduboy.pressed(A_BUTTON)) {
				//!< ソ (G4)
				if (arduboy.justPressed(UP_BUTTON)) {
					beepPin1.tone(beepPin1.freq(NOTE_G4), Duration);
				}
				//!< ラ (A4)
				if (arduboy.justPressed(DOWN_BUTTON)) {
					beepPin1.tone(beepPin1.freq(NOTE_A4), Duration);
				}
				//!< シ (B4)
				if (arduboy.justPressed(LEFT_BUTTON)) {
					beepPin1.tone(beepPin1.freq(NOTE_B4), Duration);
				}
				//!< ド (C5)
				if (arduboy.justPressed(RIGHT_BUTTON)) {
					beepPin1.tone(beepPin1.freq(NOTE_C5), Duration);
				}
			} else {
				//!< ド (C4)
				if (arduboy.justPressed(UP_BUTTON)) {
					beepPin1.tone(beepPin1.freq(NOTE_C4), Duration);
				}
				//!< レ (D4)
				if (arduboy.justPressed(DOWN_BUTTON)) {
					beepPin1.tone(beepPin1.freq(NOTE_D4), Duration);
				}
				//!< ミ (E4)
				if (arduboy.justPressed(LEFT_BUTTON)) {
					beepPin1.tone(beepPin1.freq(NOTE_E4), Duration);
				}
				//!< ファ (F4)
				if (arduboy.justPressed(RIGHT_BUTTON)) {
					beepPin1.tone(beepPin1.freq(NOTE_F4), Duration);
				}
			}

			if (arduboy.justReleased(B_BUTTON)) {
				beepPin1.noTone();
				beepPin2.noTone();
			}
		
			arduboy.setCursor(0, 0);
			arduboy.print("Sound Enabled");
			if (beepPin1.duration) {
				arduboy.setCursor(0, 8);
				arduboy.print("Beep1 playing");
			}
			if (beepPin2.duration) {
				arduboy.setCursor(0, 16);
				arduboy.print("Beep2 playing");
			}
		} else {
			arduboy.setCursor(0, 0);
			arduboy.print("Sound Disabled");
		}

		arduboy.display();
	}
}

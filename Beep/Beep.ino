/*
 Name:		Beep.ino
 Created:	10/10/2020 10:02:27 PM
 Author:	horin
*/

#include <Arduboy2.h>

Arduboy2 arduboy;

BeepPin1 beepPin1;
BeepPin2 beepPin2;

// the setup function runs once when you press reset or power the board
void setup() {
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(60);
	beepPin1.begin();
	beepPin2.begin();
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (arduboy.nextFrame()) {
		arduboy.clear();

		arduboy.pollButtons();
		beepPin1.timer();
		beepPin2.timer();
	
		constexpr auto Duration = 100;
		if (arduboy.justPressed(A_BUTTON)) {
			//!< Žü”g” : 15.26 - 1000000 Hz („§)
			beepPin1.tone(beepPin1.freq(1000), Duration);
		}
		if (arduboy.justReleased(B_BUTTON)) {
			//!< Žü”g” : 61.04 - 15625 Hz
			beepPin2.tone(beepPin2.freq(1000), Duration);
		}
		
		if (beepPin1.duration) {
			arduboy.setCursor(0, 0);
			arduboy.print("Beep1 playing");
		}
		if (beepPin2.duration) {
			arduboy.setCursor(0, 8);
			arduboy.print("Beep2 playing");
		}

		arduboy.display();
	}
}

/*
 Name:		Sprite.ino
 Created:	10/18/2020 4:40:58 PM
 Author:	horin
*/

#include <Arduboy2.h>
#include <Sprites.h>

Arduboy2 arduboy;
Sprites sprites;

// the setup function runs once when you press reset or power the board
void setup() {
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(30);

}

// the loop function runs over and over again until power down or reset
void loop() {
	if (arduboy.nextFrame()) {
		arduboy.clear();
		arduboy.pollButtons();

		if (arduboy.pressed(UP_BUTTON)) {}
		if (arduboy.pressed(DOWN_BUTTON)) {}
		if (arduboy.pressed(LEFT_BUTTON)) {}
		if (arduboy.pressed(RIGHT_BUTTON)) {}
		
		if (arduboy.pressed(A_BUTTON)) {}
		if (arduboy.pressed(B_BUTTON)) {}

		//sprites.drawExternalMask();
		//sprites.drawPlusMask();
		//sprites.drawOverwrite();
		//sprites.drawErase();
		//sprites.drawSelfMasked();

		arduboy.display();
	}
}

/*
 Name:		GamePad.ino
 Created:	10/10/2020 4:14:22 PM
 Author:	horin
*/

#include <Arduboy2.h>

Arduboy2 arduboy;
auto Cursor = Point(0, 0);

// the setup function runs once when you press reset or power the board
void setup() {
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(60);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (arduboy.nextFrame()) {
		arduboy.clear();

		//!< Need to use justPressed(), etc
		arduboy.pollButtons();

		{
			arduboy.drawFastHLine(0, 0, Arduboy2::width() - 1, WHITE);
			arduboy.drawFastHLine(0, Arduboy2::height() - 1, Arduboy2::width() - 1, WHITE);
			arduboy.drawFastVLine(0, 0, Arduboy2::height() - 1, WHITE);
			arduboy.drawFastVLine(Arduboy2::width() - 1, 0, Arduboy2::height() - 1, WHITE);
		}

		//!< Move cursor
		{
			constexpr auto Radius = 4;
			{
				if (arduboy.pressed(UP_BUTTON)) { --Cursor.y; }
				if (arduboy.pressed(DOWN_BUTTON)) { ++Cursor.y; }
				if (arduboy.pressed(LEFT_BUTTON)) { --Cursor.x; }
				if (arduboy.pressed(RIGHT_BUTTON)) { ++Cursor.x; }
				Cursor.x = min(max(Cursor.x, Radius), Arduboy2::width() - 1 - Radius);
				Cursor.y = min(max(Cursor.y, Radius), Arduboy2::height() - 1 - Radius);
			}
			{
				arduboy.drawRect(Cursor.x - Radius, Cursor.y - Radius, Radius * 2, Radius * 2, WHITE);
			}
		}

		//!< Draw button state
		{
			constexpr auto Radius = 8;
			constexpr auto Spacing = Radius * 2;

			auto Position = Point(32, Arduboy2::height() - 1 - 32);
			arduboy.pressed(UP_BUTTON) ? arduboy.fillCircle(Position.x, Position.y - Spacing, Radius, WHITE) : arduboy.drawCircle(Position.x, Position.y - Spacing, Radius, WHITE);
			arduboy.pressed(DOWN_BUTTON) ? arduboy.fillCircle(Position.x, Position.y + Spacing, Radius, WHITE) : arduboy.drawCircle(Position.x, Position.y + Spacing, Radius, WHITE);
			arduboy.pressed(LEFT_BUTTON) ? arduboy.fillCircle(Position.x - Spacing, Position.y, Radius, WHITE) : arduboy.drawCircle(Position.x - Spacing, Position.y, Radius, WHITE);
			arduboy.pressed(RIGHT_BUTTON) ? arduboy.fillCircle(Position.x + Spacing, Position.y, Radius, WHITE) : arduboy.drawCircle(Position.x + Spacing, Position.y, Radius, WHITE);

			Position.x = Arduboy2::width() - 1 - 32;
			arduboy.pressed(A_BUTTON) ? arduboy.fillCircle(Position.x - Spacing, Position.y, Radius, WHITE) : arduboy.drawCircle(Position.x - Spacing, Position.y, Radius, WHITE);
			arduboy.pressed(B_BUTTON) ? arduboy.fillCircle(Position.x + Spacing, Position.y, Radius, WHITE) : arduboy.drawCircle(Position.x + Spacing, Position.y, Radius, WHITE);

			if (arduboy.justPressed(A_BUTTON)) { arduboy.invert(true); }
			if (arduboy.justReleased(A_BUTTON)) { arduboy.invert(false); }
		}
		{
			arduboy.setCursor(0, 0);
			if (arduboy.currentButtonState & UP_BUTTON) { arduboy.print("U + "); }
			if (arduboy.currentButtonState & DOWN_BUTTON) { arduboy.print("D + "); }
			if (arduboy.currentButtonState & LEFT_BUTTON) { arduboy.print("L + "); }
			if (arduboy.currentButtonState & RIGHT_BUTTON) { arduboy.print("R + "); }
			if (arduboy.currentButtonState & A_BUTTON) { arduboy.print("A + "); }
			if (arduboy.currentButtonState & B_BUTTON) { arduboy.print("B + "); }
		}

		arduboy.display();
	}
}

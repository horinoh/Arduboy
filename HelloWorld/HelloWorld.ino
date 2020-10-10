/*
 Name:		HelloWorld.ino
 Created:	10/10/2020 3:48:18 PM
 Author:	horin
*/

#include <Arduboy2.h>
#include <TinyFont.h>

Arduboy2 arduboy;
auto tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());

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

		{
			constexpr auto Message = "Hello World";
			constexpr auto StrLen = strlen(Message);

			constexpr auto Length = Point(arduboy.getCharacterWidth() * StrLen + arduboy.getCharacterSpacing() * (StrLen - 1), arduboy.getCharacterHeight());
			constexpr auto HalfLength = Point(Length.x / 2, Length.y / 2);

			arduboy.setCursor(Arduboy2::width() / 2 - HalfLength.x, Arduboy2::height() / 4 - HalfLength.y);
			arduboy.print(Message);
		}

		{
			constexpr auto Message = "Hello Tiny Font";
			constexpr auto StrLen = strlen(Message);

			constexpr auto CharWidth = 4, CharSpacing = 1, CharHeight = 4;
			constexpr auto Length = Point(CharWidth * StrLen + CharSpacing * (StrLen - 1), CharHeight);
			constexpr auto HalfLength = Point(Length.x / 2, Length.y / 2);

			tinyfont.setCursor(Arduboy2::width() / 2 - HalfLength.x, Arduboy2::height() * 3 / 4 - HalfLength.y);
			tinyfont.print(Message);
		}

		arduboy.display();
	}
}

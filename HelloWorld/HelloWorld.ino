#include <Arduboy2.h>
#include <Tinyfont.h>

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

		//!< フォントサイズ 5x7 (Font size 5x7)
		{
			constexpr auto Message = "Hello World";
			constexpr auto StrLen = strlen(Message);

			constexpr auto Length = Point(Arduboy2::getCharacterWidth() * StrLen + Arduboy2::getCharacterSpacing() * (StrLen - 1), Arduboy2::getCharacterHeight() + Arduboy2::getLineSpacing());
			constexpr auto HalfLength = Point(Length.x / 2, Length.y / 2);

			arduboy.setCursor(Arduboy2::width() / 2 - HalfLength.x, Arduboy2::height() / 4 - HalfLength.y);
			arduboy.print(Message);
		}

		//!< フォントサイズ 4x4 (Font size 4x4)
		{
			constexpr auto Message = "Hello Tiny Font";
			constexpr auto StrLen = strlen(Message);

			constexpr auto CharWidth = 4, CharSpacing = 1, CharHeight = 4 , LineSpacding = 1;
			constexpr auto Length = Point(CharWidth * StrLen + CharSpacing * (StrLen - 1), CharHeight + LineSpacding);
			constexpr auto HalfLength = Point(Length.x / 2, Length.y / 2);

			tinyfont.setCursor(Arduboy2::width() / 2 - HalfLength.x, Arduboy2::height() * 3 / 4 - HalfLength.y);
			tinyfont.print(Message);
		}

		{
			arduboy.setCursor(0, 0);
			arduboy.print("CPU = ");
			arduboy.print(arduboy.cpuLoad());
		}

		arduboy.display();
	}
}

/*
 Name:		FrameBuffer.ino
 Created:	10/10/2020 6:56:22 PM
 Author:	horin
*/

#include <Arduboy2.h>

#include <FixedPoints.h>
#include <FixedPointsCommon.h>

Arduboy2 arduboy;

// the setup function runs once when you press reset or power the board
void setup() {
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(60);
	arduboy.initRandomSeed();
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (arduboy.nextFrame()) {
		arduboy.clear();
		
		//const auto Start = millis();
		const auto Start = micros();

		auto Buffer = arduboy.getBuffer();

		//!< ---------------------------------------------------
		//!< 最初の8bitが1列目の8行(0-7)分、次の8bitが2列目の8行分、... 127列目まで行ったら
		//!< さらに8行分下(8-15)の1列目から始まり、以下同様の繰り返し
		//!< 64/8 = 8回繰り返される事になる
		//!< ---------------------------------------------------
		//!< (0 - 7 行目)
		//!< [0] [1] ... [127]
		//!<  0   8       1016(=127x8)
		//!<  1   9       1017
		//!<  ... ...     ...
		//!<  7   15      1023

		//!< (8 - 15 行目)
		//!< [128] ... [255]

		//!< ...

		//!< (56 - 63 行目)
		//!< [896(=128x7)] ... [1023]
		//!< ---------------------------------------------------

#if 1
		//!< (0 - 7 行目) 左上8x8に三角形を描画する (0-7 lines, Draw 8x8 triangle on top left)
		//!< *-------
		//!< **------
		//!< ***-----
		//!< ****----
		//!< *****---
		//!< ******--
		//!< *******-
		//!< ********
		Buffer[0] = 0xff; //!< 1111 1111
		Buffer[1] = 0xfe; //!< 1111 1110
		Buffer[2] = 0xfc; //!< 1111 1100
		Buffer[3] = 0xf8; //!< 1111 1000
		Buffer[4] = 0xf0; //!< 1111 0000		
		Buffer[5] = 0xe0; //!< 1110 0000
		Buffer[6] = 0xc0; //!< 1100 0000
		Buffer[7] = 0x80; //!< 1000 0000

		constexpr auto Width = Arduboy2::width();
		//!< (8 - 15 行目) ランダム (8-15 lines, Random)
		for (auto i = 0; i < Width; ++i) { Buffer[i + Width] = rand() & 0xff; }

		//!< (16 - 23 行目) 白塗り (16-23 lines, Fill white)
		for (auto i = 0; i < Width; ++i) { Buffer[i + Width * 2] = 0xff; }

		//!< (24 - 31 行目) 黒塗り (24-31 lines, Fill black)
		for (auto i = 0; i < Width; ++i) { Buffer[i + Width * 3] = 0x00; }

		//!< (32 - 39 行目) 市松模様 (32-39 lines, Checkered pattern)
		for (auto i = 0; i < Width; ++i) { Buffer[i + Width * 4] = (i & 1) ? 0xaa : 0x55; } //!< 1010 1010 or 0101 0101
		
		//!< (40 - 47 行目) 横縞 (40-47 lines, Horizontal stripes)
		for (auto i = 0; i < Width; ++i) { Buffer[i + Width * 5] = 0xaa; } //!< 1010 1010

		//!< (48 - 55 行目) 縦縞 (48-55 lines, Virtical stripes)
		for (auto i = 0; i < Width; ++i) { Buffer[i + Width * 6] = (i & 1) ? 0xff : 0x00; } //!< 1111 1111 or 0000 0000

		//!< (56 - 63 行目) (56-63 lines, ...)
		for (auto i = 0; i < Width; ++i) { Buffer[i + Width * 7] = (i > Width / 2) ? 0xf0 : 0x0f; } //!< 1111 0000 or 0000 1111

		//const auto End = millis();
		const auto End = micros();
		{
			arduboy.setCursor(9, 0);

			arduboy.print("CPU=");
			arduboy.print(arduboy.cpuLoad());
			arduboy.print("%,");

			arduboy.print(End - Start);
			//arduboy.print("msec");
			arduboy.print("usec");
		}

		arduboy.display();
#elif 1
		constexpr SQ15x16 InvW = 1.0f / Arduboy2::width();
		constexpr SQ7x8 InvH = 1.0f / Arduboy2::height();
		for (auto i = 0; i < (Arduboy2::height() >> 3); ++i) {
			for (auto j = 0; j < Arduboy2::width(); ++j) {
				const auto ClipX = InvW * (j << 1) - 1;
				uint8_t pixel8 = 0x00;
				if (ClipX > 0) { pixel8 = 0xff; }
				for (auto k = 0; k < 8; ++k) {
					const auto ClipY = -InvH * (((i << 3) + k) << 1) + 1;
					if (ClipY > 0) { pixel8 = 0xff; }
					if (ClipX * ClipY < 0) { pixel8 = rand() & 0xff; }
				}
				arduboy.paint8Pixels(pixel8);
			}
		}
#else
		//!< ランダム (Random)
		for (auto i = 0; i < Arduboy2::width() * Arduboy2::height() / 8; ++i) {
			arduboy.paint8Pixels(rand() & 0xff);
		}
#endif
	}
}

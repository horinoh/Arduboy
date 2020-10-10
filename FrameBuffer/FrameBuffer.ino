/*
 Name:		FrameBuffer.ino
 Created:	10/10/2020 6:56:22 PM
 Author:	horin
*/

#include <Arduboy2.h>

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

		//!< (0 - 7 行目) 左上8x8に三角形を描画する
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

		//!< (8 - 15 行目) ランダム
		for (auto i = 0; i < 128; ++i) { Buffer[i + 128] = rand() % 0xff; }

		//!< (16 - 23 行目) 白塗り
		for (auto i = 0; i < 128; ++i) { Buffer[i + 256] = 0xff; }

		//!< (24 - 31 行目) 黒塗り
		for (auto i = 0; i < 128; ++i) { Buffer[i + 384] = 0x00; }

		//!< (32 - 39 行目) 市松模様
		for (auto i = 0; i < 128; ++i) { Buffer[i + 512] = (i & 1) ? 0xaa : 0x55; } //!< 1010 1010 or 0101 0101
		
		//!< (40 - 47 行目) 横縞
		for (auto i = 0; i < 128; ++i) { Buffer[i + 640] = 0xaa; } //!< 1010 1010

		//!< (48 - 55 行目) 縦縞
		for (auto i = 0; i < 128; ++i) { Buffer[i + 768] = (i & 1) ? 0xff : 0x00; } //!< 1111 1111 or 0000 0000

		//!< (56 - 63 行目)
		for (auto i = 0; i < 128; ++i) { Buffer[i + 896] = (i > 63) ? 0xf0 : 0x0f; } //!< 1111 0000 or 0000 1111

		arduboy.display();
	}
}

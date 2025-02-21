#include <Arduboy2.h>
#include <Sprites.h>

Arduboy2 arduboy;
Sprites sprites;

//!< アニメーションデータは https://github.com/Team-ARG-Museum/ID-46-Arduventure のデータを使わせてもらっている

const unsigned char PROGMEM eyesBlinking[] =
{
	// width, height,
	4, 8,
	// FRAME 00
	0x03, 0x00, 0x00, 0x03,
	// FRAME 01
	0x01, 0x00, 0x00, 0x01,
	// FRAME 02
	0x00, 0x00, 0x00, 0x00,
};

const unsigned char PROGMEM playerHead_plus_mask[] =
{
	// width, height,
	12, 8,
	// FRAME 00
	0x00, 0xd8, 0xc8, 0xfc, 0x1c, 0xfe, 0xa4, 0xfe, 0x5a, 0xff, 0xde, 0xff,
	0xee, 0xff, 0x5e, 0xff, 0xbc, 0xfe, 0x34, 0xfe, 0xc8, 0xfc, 0x00, 0xd8,

	// FRAME 01
	0x00, 0x1c, 0x1c, 0xfe, 0xda, 0xff, 0x6c, 0xfe, 0xde, 0xff, 0x3e, 0xff,
	0xbe, 0xff, 0x7e, 0xff, 0xf4, 0xfe, 0x68, 0xfc, 0x00, 0x68, 0x00, 0x00,

	// FRAME 02
	0x00, 0x68, 0x68, 0xfc, 0xf4, 0xfe, 0xfc, 0xfe, 0xfe, 0xff, 0xfe, 0xff,
	0xfe, 0xff, 0xfe, 0xff, 0xfc, 0xfe, 0xfc, 0xfe, 0x68, 0xfc, 0x00, 0x68,

	// FRAME 03
	0x00, 0x00, 0x00, 0x68, 0x68, 0xfc, 0xf4, 0xfe, 0x7e, 0xff, 0xbe, 0xff,
	0x3e, 0xff, 0xde, 0xff, 0x6c, 0xfe, 0xda, 0xff, 0x1c, 0xfe, 0x00, 0x1c,
};

const unsigned char PROGMEM playerFeet_plus_mask[] =
{
	// width, height,
	12, 8,
	// FRAME 00
	0x00, 0x01, 0x01, 0x07, 0x04, 0x0f, 0x03, 0x7f, 0x54, 0xff, 0x57, 0xff,
	0x07, 0x7f, 0x34, 0x7f, 0x3b, 0x7f, 0x00, 0x3f, 0x01, 0x03, 0x00, 0x01,

	// FRAME 01
	0x00, 0x00, 0x00, 0x19, 0x18, 0x7f, 0x45, 0xff, 0x5a, 0xff, 0x0b, 0x7f,
	0x13, 0x7f, 0x5a, 0xff, 0x45, 0xff, 0x18, 0x7f, 0x00, 0x19, 0x00, 0x00,

	// FRAME 02
	0x00, 0x01, 0x01, 0x03, 0x00, 0x3f, 0x3b, 0x7f, 0x34, 0x7f, 0x07, 0x7f,
	0x57, 0xff, 0x54, 0xff, 0x03, 0x7f, 0x04, 0x0f, 0x01, 0x07, 0x00, 0x01,

	// FRAME 03
	0x00, 0x00, 0x00, 0x1b, 0x1b, 0x7f, 0x18, 0xff, 0x07, 0xff, 0x16, 0x7f,
	0x1b, 0x7f, 0x50, 0xff, 0x45, 0xff, 0x1c, 0x7f, 0x00, 0x1c, 0x00, 0x00,

	// FRAME 04
	0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x02, 0x5f, 0x43, 0xff, 0x5b, 0xff,
	0x19, 0xff, 0x24, 0x7f, 0x02, 0x3f, 0x0e, 0x1f, 0x00, 0x0e, 0x00, 0x00,

	// FRAME 05
	0x00, 0x00, 0x00, 0x5b, 0x43, 0xff, 0x54, 0xff, 0x17, 0x7f, 0x16, 0x7f,
	0x03, 0x7f, 0x18, 0xff, 0x19, 0xff, 0x04, 0x7f, 0x00, 0x1c, 0x00, 0x00,

	// FRAME 06
	0x00, 0x00, 0x00, 0x33, 0x31, 0x7f, 0x33, 0x7f, 0x05, 0x7f, 0x2d, 0x7f,
	0x2d, 0xff, 0x35, 0xff, 0x03, 0x7f, 0x05, 0x0f, 0x00, 0x07, 0x00, 0x00,

	// FRAME 07
	0x00, 0x00, 0x00, 0x19, 0x18, 0x7f, 0x41, 0xff, 0x5a, 0xff, 0x16, 0x7f,
	0x16, 0x7f, 0x5a, 0xff, 0x41, 0xff, 0x18, 0x7f, 0x00, 0x19, 0x00, 0x00,

	// FRAME 08
	0x00, 0x01, 0x00, 0x07, 0x05, 0x0f, 0x03, 0x7f, 0x35, 0xff, 0x2d, 0xff,
	0x2d, 0x7f, 0x05, 0x7f, 0x33, 0x7f, 0x31, 0x7f, 0x00, 0x33, 0x00, 0x00,

	// FRAME 09
	0x00, 0x00, 0x00, 0x1c, 0x04, 0x7f, 0x19, 0xff, 0x18, 0xff, 0x03, 0x7f,
	0x16, 0x7f, 0x17, 0x7f, 0x54, 0xff, 0x43, 0xff, 0x00, 0x5b, 0x00, 0x00,

	// FRAME 10
	0x00, 0x00, 0x00, 0x0e, 0x0e, 0x1f, 0x02, 0x3f, 0x24, 0x7f, 0x19, 0xff,
	0x5b, 0xff, 0x43, 0xff, 0x02, 0x5f, 0x01, 0x03, 0x00, 0x01, 0x00, 0x00,

	// FRAME 11
	0x00, 0x00, 0x00, 0x1c, 0x1c, 0x7f, 0x45, 0xff, 0x50, 0xff, 0x1b, 0x7f,
	0x16, 0x7f, 0x07, 0xff, 0x18, 0xff, 0x1b, 0x7f, 0x00, 0x1b, 0x00, 0x00,
};

#define GET_WIDTH(x) x[0]
#define GET_HEIGHT(x) x[1]
#define GET_COUNT(x) (sizeof(x)/sizeof(x[0]) - 2)
#define GET_FRAMES(x) (GET_COUNT(x) / GET_WIDTH(x))
#define GET_FRAMES_PLUS_MASK(x) (GET_FRAMES(x) / 2)
#define COUNTOF(x) (sizeof(x)/sizeof(x[0]))

const auto eyesBlinking_Width = GET_WIDTH(eyesBlinking);
const auto eyesBlinking_Height = GET_HEIGHT(eyesBlinking);
const auto eyesBlinking_Frame = GET_FRAMES(eyesBlinking);

const auto playerHead_plus_mask_Width = GET_WIDTH(playerHead_plus_mask);
const auto playerHead_plus_mask_Height = GET_HEIGHT(playerHead_plus_mask);
const auto playerHead_plus_mask_Frame = GET_FRAMES_PLUS_MASK(playerHead_plus_mask);

const auto playerFeet_plus_mask_Width = GET_WIDTH(playerFeet_plus_mask);
const auto playerFeet_plus_mask_Height = GET_HEIGHT(playerFeet_plus_mask);
const auto playerFeet_plus_mask_Frame = GET_FRAMES_PLUS_MASK(playerFeet_plus_mask);

const uint16_t FeetAnimSeq[] = { 0, 1, 2, 1 };

int16_t X = Arduboy2::width() / 2, Y = Arduboy2::height() / 2;
uint8_t Direction = 0;

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
		arduboy.pollButtons();		

		const auto CharaWidth = playerHead_plus_mask_Width/*playerFeet_plus_mask_Width*/;
		const auto CharaHeight = playerHead_plus_mask_Height + playerFeet_plus_mask_Height;

		//!< 方向毎のパターン
		//!<    2
		//!<  1   3
		//!<    0
		if (arduboy.pressed(UP_BUTTON)) { --Y; Direction = 2; }
		if (arduboy.pressed(DOWN_BUTTON)) { ++Y; Direction = 0; }
		if (arduboy.pressed(LEFT_BUTTON)) { --X; Direction = 1; }
		if (arduboy.pressed(RIGHT_BUTTON)) { ++X; Direction = 3; }
		X = min(max(X, 0), Arduboy2::width() - CharaWidth);
		Y = min(max(Y, 0), Arduboy2::height() - CharaHeight);

		if (arduboy.pressed(A_BUTTON)) {}
		if (arduboy.pressed(B_BUTTON)) {}

		const auto AnimFrame = arduboy.frameCount / 10;

		//!< 方向毎にあるので 3 * 4 = 12フレーム分ある
		//!< 0, 1, 2 : 歩行アニメーション、1は停止アニメーションとしても使う
		auto FeetAnim = FeetAnimSeq[AnimFrame % COUNTOF(FeetAnimSeq)];
		auto HeadMove = -(AnimFrame % 2) + 1;
		//!< 1 : 停止 
		if (arduboy.notPressed(UP_BUTTON) && arduboy.notPressed(DOWN_BUTTON) && arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON)) { 
			FeetAnim = 1; 
			HeadMove = 0;
		}
	
		//!< 頭
		sprites.drawPlusMask(X, Y + HeadMove, playerHead_plus_mask, Direction);
		//!< 足
		sprites.drawPlusMask(X, Y + playerHead_plus_mask_Height, playerFeet_plus_mask, Direction * 3 + FeetAnim);
		//!< 目
		if (1 == FeetAnim && 0 == Direction) {
			sprites.drawSelfMasked(X + 4, Y + 7, eyesBlinking, AnimFrame % eyesBlinking_Frame);
		}

		//!< スプライト描画関数バリエーション (Sprite function variation)
		//sprites.drawExternalMask(x, y, XXX, YYY, Frame);
		//sprites.drawPlusMask(x, y, XXX, Frame);
		//sprites.drawOverwrite(x, y, XXX, Frame);
		//sprites.drawErase(x, y, XXX, Frame);
		//sprites.drawSelfMasked(x, y, XXX, Frame);

		arduboy.display();
	}
}

/*
 Name:		Dither.ino
 Created:	10/13/2020 10:35:52 PM
 Author:	horin
*/

#include <Arduboy2.h>
#include <FixedPoints.h>
#include <FixedPointsCommon.h>

Arduboy2 arduboy;

// M_2n = 1/(2n)^2 * [4 * M_n + 0, 4 * M_n + 2] 
//		             [4 * M_n + 3, 4 * M_n + 1]

// [2 x 2]
// 0 2
// 3 1

// [4 x 4]
//  0  8  0  8 + 0 0 2 2 =  0  8  2 10
// 12  4 12  4 + 0 0 2 2 = 12  4 14  6
//  0  8  0  8 + 3 3 1 1 =  3 11  1  9
// 12  4 12  4 + 3 3 1 1 = 15  7 13  5

// [8 x 8]
//  0 32  8 40  0 32  8 40 + 0 0 0 0 2 2 2 2 =  0 32  8 40  2 34 10 42
// 48 16 56 24 48 16 56 24 + 0 0 0 0 2 2 2 2 = 48 16 56 24 50 18 58 26
// 12 44  4 36 12 44  4 36 + 0 0 0 0 2 2 2 2 = 12 44  4 36 14 46  6 38
// 60 28 52 20 60 28 52 20 + 0 0 0 0 2 2 2 2 = 60 28 52 20 62 30 54 22
//  0 32  8 40  0 32  8 40 + 3 3 3 3 1 1 1 1 =  3 35 11 43  1 33  9 41
// 48 16 56 24 48 16 56 24 + 3 3 3 3 1 1 1 1 = 51 19 59 27 49 17 57 25
// 12 44  4 36 12 44  4 36 + 3 3 3 3 1 1 1 1 = 15 47  7 39 13 45  5 37
// 60 28 52 20 60 28 52 20 + 3 3 3 3 1 1 1 1 = 63 31 55 23 61 29 53 21

//!< C++11‚Å‚ÍconstexorŠÖ”‚Íreturn‚Ìˆê•¶‚Ì‚Ý‚Å‚È‚¢‚Æ‚¢‚¯‚È‚¢‚Ì‚Å’ˆÓ (In C++11, constexpr function must be one return sentence only)
constexpr uint8_t Bayer(const uint8_t i, const uint8_t j, const uint8_t n)
{
	//!< [ 4 * M_n, 4 * M_n ] •”
	//!< [ 4 * M_n, 4 * M_n ]
	return (n > 2 ? (Bayer(i % (n >> 1), j % (n >> 1), n >> 1) << 2) : 0)
		//!< [ 0, 2 ] •”
		//!< [ 3, 1 ]
		+ i / (n >> 1) | ((((i / (n >> 1)) & 1) ? !(j / (n >> 1)) : (j / (n >> 1))) << 1);
}

constexpr uint8_t N = 2 * 2;
SQ15x16 ThresholdMap[N][N];

auto Tone = SQ15x16(0.5f);

// the setup function runs once when you press reset or power the board
void setup() {
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(30);

	for (uint8_t i = 0; i < N; ++i) {
		for (uint8_t j = 0; j < N; ++j) {
			ThresholdMap[i][j] = static_cast<float>(Bayer(i, j, N)) / (N * N);
		}
	}
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (arduboy.nextFrame()) {
		arduboy.clear();
		arduboy.pollButtons();

		if (arduboy.pressed(UP_BUTTON)) { Tone += SQ15x16(0.01f); }
		if (arduboy.pressed(DOWN_BUTTON)) { Tone -=  SQ15x16(0.01f); }
		Tone = max(min(Tone, SQ15x16(1.0f)), SQ15x16(0.0f));
		
		{
			arduboy.setCursor(0, Arduboy2::height() - 2 * (Arduboy2::getCharacterHeight() - Arduboy2::getLineSpacing()));
			arduboy.print("Steps=");
			arduboy.println(N * N);
			arduboy.print("Tone=");
			arduboy.print(static_cast<float>(Tone));
		}

		constexpr auto Denom = SQ15x16(1.0f / static_cast<float>(Arduboy2::width()));
#if 0
		for (uint8_t i = 0; i < Arduboy2::height(); ++i) {
			for (uint8_t j = 0; j < Arduboy2::width(); ++j) {
				arduboy.drawPixel(j, i, ThresholdMap[i % N][j % N] < Tone ? WHITE : BLACK);
				//arduboy.drawPixel(j, i, ThresholdMap[i % N][j % N] < SQ15x16(static_cast<float>(j) * Denom) ? WHITE : BLACK);
			}
		}
		arduboy.display();
#else
		for (auto i = 0; i < Arduboy2::height() >> 3; ++i) {
			for (auto j = 0; j < Arduboy2::width(); ++j) {
				uint8_t p = 0;
				for (auto k = 0; k < 8; ++k) {
					p |= (ThresholdMap[((i << 3) + k) % N][j % N] < Tone ? 1 : 0) << k;
					//p |= (ThresholdMap[((i << 3) + k) % N][j % N] < SQ15x16(static_cast<float>(j) * Denom) ? 1 : 0) << k;
				}
				arduboy.paint8Pixels(p);
			}
		}
#endif
	
	}
}

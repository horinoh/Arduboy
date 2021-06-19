#include <Arduboy2.h>
#include <FixedPoints.h>
#include <FixedPointsCommon.h>

#include <ArduMath.h>

Arduboy2 arduboy;

constexpr uint8_t N = 2 * 2; //!< 2の累乗であること (Power of 2)
constexpr auto NN = N * N;
constexpr float InvNN = 1.0f / NN;
SQ15x16 ThresholdMap[N][N];

auto Tone = SQ15x16(0.5f);
uint8_t GetDither(const uint8_t x, const uint8_t y, const SQ15x16& tone) { return ThresholdMap[y % N][x % N] < tone ? 1 : 0; }

// the setup function runs once when you press reset or power the board
void setup() {
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(30);

	for (uint8_t i = 0; i < N; ++i) {
		for (uint8_t j = 0; j < N; ++j) {
			ThresholdMap[i][j] = static_cast<float>(Bayer(i, j, N)) * InvNN;
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
			arduboy.println(NN);
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
					p |= GetDither(j, (i << 3) + k, Tone) << k;
					//p |= GetDither(j, (i << 3) + k, SQ15x16(static_cast<float>(j) * Denom)) << k;
				}
				arduboy.paint8Pixels(p);
			}
		}
#endif
	
	}
}

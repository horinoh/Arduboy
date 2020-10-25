/*
 Name:		ParametricSurface.ino
 Created:	10/24/2020 12:36:21 AM
 Author:	horin
*/

#include <Arduboy2.h>

#include <MathLibrary.h>

#define DRAW_UV

Arduboy2 arduboy;

constexpr auto UCount = 10;
constexpr auto VCount = 10;
constexpr UQ8x8 InvUCount(1.0f / UCount);
constexpr UQ8x8 InvVCount(1.0f / VCount);

Vec3<SQ7x8> VertexBuffer[VCount * UCount];
uint8_t IndexBuffer[(VCount - 1) * (UCount - 1) * 2 * 3];
uint8_t PrimitiveCount = 0;

template<typename T> constexpr Vec2<T> GetUV(const T& U, const T& V) { 
#ifdef DRAW_UV
	return Vec2<T>(U, V);
#else
	return Vec2<T>(T::Pi * 2 * fractFixed(U), T::Pi * 2 * fractFixed(V));
#endif
}
template<typename T, typename U> constexpr Vec3<T> GetPos(const Vec2<U>& InUV) {
#ifdef DRAW_UV
	//return Vec3<T>((float)InUV.X(), (float)InUV.Y(), 0);
	const auto UV = GetUV(InUV.X(), InUV.Y());
	return Vec3<T>((float)UV.X(), (float)UV.Y(), 0.0f);
#else
	//const auto UV = GetUV(InUV.X(), InUV.Y());
	const auto UV = Vec2<T>((float)InUV.X(), (float)InUV.Y());
	const T InnerR = 0.5f, OuterR = 1.0f;
	const T CU = cosFixed(UV.X()), CV = cosFixed(UV.Y()), SU = sinFixed(UV.X()), SV = sinFixed(UV.Y());
	//const T CU = cosFixed((float)UV.X()), CV = cosFixed((float)UV.Y()), SU = sinFixed((float)UV.X()), SV = sinFixed((float)UV.Y());
	return Vec3<T>((OuterR + InnerR * CV) * CU, (OuterR + InnerR * CV) * SU, InnerR * SV);
#endif
}

// the setup function runs once when you press reset or power the board
void setup() {
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(60);
	arduboy.initRandomSeed();

	auto Count = 0;
	auto V = UQ8x8(0);
	for (uint16_t i = 0; i < VCount; ++i, V += InvVCount) {
		auto U = UQ8x8(0);
		for (auto j = 0; j < UCount; ++j, U += InvUCount, ++Count) {
			VertexBuffer[Count] = GetPos<SQ7x8>(GetUV(U, V));
		}
	}

	PrimitiveCount = 0;
	Count = 0;
	for (auto i = 0; i < VCount - 1; ++i) {
		const auto baseIdx = i * UCount;
		for (auto j = 0; j < UCount - 1; ++j) {
			const auto idx0 = baseIdx + j, idx1 = baseIdx + j + UCount, idx2 = baseIdx + j + 1, idx3 = baseIdx + j + 1 + UCount;
			IndexBuffer[Count++] = idx0;
			IndexBuffer[Count++] = idx1;
			IndexBuffer[Count++] = idx2;
			PrimitiveCount++;

			IndexBuffer[Count++] = idx1;
			IndexBuffer[Count++] = idx2;
			IndexBuffer[Count++] = idx3;
			PrimitiveCount++;
		}
	}
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (arduboy.nextFrame()) {
		arduboy.clear();

		const auto Start = millis(); {
			for (auto i = 0; i < PrimitiveCount; ++i) {
				const auto baseIdx = i * 3;	
				const auto idx0 = IndexBuffer[baseIdx], idx1 = IndexBuffer[baseIdx + 1], idx2 = IndexBuffer[baseIdx + 2];
#ifdef DRAW_UV
				arduboy.drawTriangle((float)VertexBuffer[idx0].X() * Arduboy2::width(), (float)VertexBuffer[idx0].Y() * Arduboy2::height(),
					(float)VertexBuffer[idx1].X() * Arduboy2::width(), (float)VertexBuffer[idx1].Y() * Arduboy2::height(),
					(float)VertexBuffer[idx2].X() * Arduboy2::width(), (float)VertexBuffer[idx2].Y() * Arduboy2::height(), WHITE);
#else
				arduboy.drawTriangle((float)VertexBuffer[idx0].X() * 30 + (Arduboy2::width() >> 1), (float)VertexBuffer[idx0].Y() * 30 + (Arduboy2::height() >> 1),
					(float)VertexBuffer[idx1].X() * 30 + (Arduboy2::width() >> 1), (float)VertexBuffer[idx1].Y() * 30 + (Arduboy2::height() >> 1),
					(float)VertexBuffer[idx2].X() * 30 + (Arduboy2::width() >> 1), (float)VertexBuffer[idx2].Y() * 30 + (Arduboy2::height() >> 1), WHITE);
				/*arduboy.drawPixel((float)VertexBuffer[idx0].X() * 20 + (Arduboy2::width() >> 1), (float)VertexBuffer[idx0].Y() * 20 + (Arduboy2::height() >> 1), WHITE);
				arduboy.drawPixel((float)VertexBuffer[idx1].X() * 20 + (Arduboy2::width() >> 1), (float)VertexBuffer[idx1].Y() * 20 + (Arduboy2::height() >> 1), WHITE);
				arduboy.drawPixel((float)VertexBuffer[idx2].X() * 20 + (Arduboy2::width() >> 1), (float)VertexBuffer[idx2].Y() * 20 + (Arduboy2::height() >> 1), WHITE);*/
#endif
			}
		} const auto End = millis();

		arduboy.setCursor(0, 0);
		arduboy.print("V="); arduboy.println(countof(VertexBuffer));
		arduboy.print("I="); arduboy.println(countof(IndexBuffer));
		arduboy.print("P="); arduboy.println(PrimitiveCount);

		arduboy.setCursor(0, Arduboy2::height() - Arduboy2::getCharacterHeight() - Arduboy2::getLineSpacing());
		arduboy.print(End - Start); arduboy.print("msec,");
		arduboy.print("CPU="); arduboy.println(arduboy.cpuLoad());
		arduboy.display();
	}
}

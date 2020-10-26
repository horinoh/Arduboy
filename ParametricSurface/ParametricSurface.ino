/*
 Name:		ParametricSurface.ino
 Created:	10/24/2020 12:36:21 AM
 Author:	horin
*/

#include <Arduboy2.h>

#include <MathLibrary.h>

//#define DRAW_UV
//#define DRAW_PRINT

Arduboy2 arduboy;

using Scalar = SQ7x8;

constexpr auto UCount = 10;
constexpr auto VCount = 10;
constexpr Scalar DiffU(1.0f / (UCount - 1));
constexpr Scalar DiffV(1.0f / (VCount - 1));

Vec3<Scalar> VertexBuffer[VCount * UCount];
constexpr auto PrimitiveCount = (VCount - 1) * (UCount - 1) * 2;
uint8_t IndexBuffer[PrimitiveCount * 3];

template<typename T> constexpr Vec2<T> GetUV(const T& U, const T& V) { 
#ifdef DRAW_UV
	return Vec2<T>(U, V);
#else
	return Vec2<T>(T::Pi * 2 * fractFixed(U), T::Pi * 2 * fractFixed(V));
#endif
}
template<typename T> constexpr Vec3<T> GetPos(const Vec2<T>& InUV) {
#ifdef DRAW_UV
	return Vec3<T>(InUV.X(), InUV.Y(), 0);
#else
	//const auto UV = GetUV(InUV.X(), InUV.Y()); // #TODO
	const auto UV = Vec2<T>((float)InUV.X(), (float)InUV.Y());
	constexpr T InnerR = 0.5f, OuterR = 1.0f;
	const T CU = cosFixed(UV.X()), CV = cosFixed(UV.Y()), SU = sinFixed(UV.X()), SV = sinFixed(UV.Y());
	return Vec3<T>((OuterR + InnerR * CV) * CU, (OuterR + InnerR * CV) * SU, InnerR * SV);
#endif
}

// the setup function runs once when you press reset or power the board
void setup() {
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(60);
	arduboy.initRandomSeed();

	//!< バーテックスバッファ(VertexBuffer)
	auto Count = 0;
	auto V = Scalar(0);
	for (uint16_t i = 0; i < VCount; ++i, V += DiffV) {
		if (i == VCount - 1) { V = Scalar(1); } //!< 誤差があるので
		auto U = Scalar(0);
		for (auto j = 0; j < UCount; ++j, U += DiffU, ++Count) {
			if (j == UCount - 1) { U = Scalar(1); } //!< 誤差があるので
			VertexBuffer[Count] = GetPos(GetUV(U, V));
		}
	}

	//!< インデックスバッファ(IndexBuffer)
	Count = 0;
	for (auto i = 0; i < VCount - 1; ++i) {
		const auto baseIdx = i * UCount;
		for (auto j = 0; j < UCount - 1; ++j) {
			const auto idx0 = baseIdx + j, idx1 = baseIdx + j + UCount, idx2 = baseIdx + j + 1, idx3 = baseIdx + j + 1 + UCount;
			IndexBuffer[Count++] = idx0;
			IndexBuffer[Count++] = idx1;
			IndexBuffer[Count++] = idx2;

			IndexBuffer[Count++] = idx1;
			IndexBuffer[Count++] = idx2;
			IndexBuffer[Count++] = idx3;
		}
	}
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (arduboy.nextFrame()) {
		arduboy.clear();

		const auto Start = millis(); {
#ifdef DRAW_UV
			const Vec2<SQ15x16> Scale(Arduboy2::width(), Arduboy2::height());
#else
			const Vec2<SQ15x16> Scale(40.0f, 20.0f);
			const Vec2<SQ15x16> Offset(Arduboy2::width() >> 1, Arduboy2::height() >> 1);
#endif
			for (auto i = 0; i < PrimitiveCount; ++i) {
				const auto baseIdx = i * 3;
				const auto idx0 = IndexBuffer[baseIdx], idx1 = IndexBuffer[baseIdx + 1], idx2 = IndexBuffer[baseIdx + 2];
#ifdef DRAW_UV
				arduboy.drawTriangle((float)(Scale.X() * VertexBuffer[idx0].X()), (float)(Scale.Y() * VertexBuffer[idx0].Y()),
					(float)(Scale.X() * VertexBuffer[idx1].X()), (float)(Scale.Y() * VertexBuffer[idx1].Y()),
					(float)(Scale.X() * VertexBuffer[idx2].X()), (float)(Scale.Y() * VertexBuffer[idx2].Y()), WHITE);
#else
				arduboy.drawTriangle((float)(Scale.X() * VertexBuffer[idx0].X() + Offset.X()), (float)(Scale.Y() * VertexBuffer[idx0].Y() + Offset.Y()),
					(float)(Scale.X() * VertexBuffer[idx1].X() + Offset.X()), (float)(Scale.Y() * VertexBuffer[idx1].Y() + Offset.Y()),
					(float)(Scale.X() * VertexBuffer[idx2].X() + Offset.X()), (float)(Scale.Y() * VertexBuffer[idx2].Y() + Offset.Y()), WHITE);
#endif
			}
		} const auto End = millis();

#ifdef DRAW_PRINT
		arduboy.setCursor(0, Arduboy2::height() - Arduboy2::getCharacterHeight() - Arduboy2::getLineSpacing());
		arduboy.print(End - Start); arduboy.print("msec,");
		arduboy.print("CPU="); arduboy.println(arduboy.cpuLoad());
#endif
		arduboy.display();
	}
}

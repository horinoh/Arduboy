/*
 Name:		ParametricSurface.ino
 Created:	10/24/2020 12:36:21 AM
 Author:	horin
*/

#include <Arduboy2.h>

#include <MathLibrary.h>

#define DRAW_PRINT

Arduboy2 arduboy;

using Scalar = SQ7x8;

constexpr auto UCount = 8;
constexpr auto VCount = 8;
constexpr Scalar DiffU(1.0f / (UCount - 1));
constexpr Scalar DiffV(1.0f / (VCount - 1));

Vec3<Scalar> VertexBuffer[VCount * UCount];
constexpr auto PrimitiveCount = (VCount - 1) * (UCount - 1) * 2;
uint8_t IndexBuffer[PrimitiveCount * 3];

enum class ShapeType : int8_t {
	Plane,
	Torus,
	Sphere,

	Count,
};
enum class ShapeType Shape = ShapeType::Plane;

namespace Plane {
	template<typename T> constexpr Vec2<T> GetUV(const T& U, const T& V) { return Vec2<T>(U, V); }
	template<typename T> constexpr Vec3<T> GetPos(const Vec2<T>& InUV) { return Vec3<T>(InUV.X(), InUV.Y(), 0); }
}
namespace Torus {
	template<typename T> constexpr Vec2<T> GetUV(const T& U, const T& V) {
		return Vec2<T>(T::Pi * 2 * fractFixed(U), T::Pi * 2 * fractFixed(V));
	}
	template<typename T> constexpr Vec3<T> GetPos(const Vec2<T>& UV) {
		constexpr T InnerR = 0.5f, OuterR = 1.0f;
		const T CU = cosFixed(UV.X()), CV = cosFixed(UV.Y()), SU = sinFixed(UV.X()), SV = sinFixed(UV.Y());
		return Vec3<T>((OuterR + InnerR * CV) * CU, (OuterR + InnerR * CV) * SU, InnerR * SV);
	}
}
namespace Sphere {
	template<typename T> constexpr Vec2<T> GetUV(const T& U, const T& V) {
		return Vec2<T>(T::Pi * 2 * fractFixed(U), T::Pi * fractFixed(V));
	}
	template<typename T> constexpr Vec3<T> GetPos(const Vec2<T>& UV) {
		constexpr T R = 1.5f;
		const T CU = cosFixed(UV.X()), CV = cosFixed(UV.Y()), SU = sinFixed(UV.X()), SV = sinFixed(UV.Y());
		return Vec3<T>(R * CU * SV, R * SU * SV, R * CV);
	}
}

void CreateVertexBuffer(Vec3<Scalar>* Buffer, const int UC, const int VC, const enum ShapeType ST)
{
	auto Count = 0;
	auto V = Scalar(0);
	for (uint16_t i = 0; i < VC; ++i, V += DiffV) {
		if (i == VC - 1) { V = Scalar(1); } //!< 誤差で閉じないので最後の要素を1.0に補正する (Correct last element to 1.0)
		auto U = Scalar(0);
		for (auto j = 0; j < UC; ++j, U += DiffU, ++Count) {
			if (j == UC - 1) { U = Scalar(1); } //!< 誤差対策
			switch (ST)
			{
			default:
			case ShapeType::Plane: Buffer[Count] = Plane::GetPos(Plane::GetUV(U, V)); break;
			case ShapeType::Torus: Buffer[Count] = Torus::GetPos(Torus::GetUV(U, V)); break;
			case ShapeType::Sphere: Buffer[Count] = Sphere::GetPos(Sphere::GetUV(U, V)); break;
			}
		}
	}
}
void CreateIndexBuffer(uint8_t* Buffer, const int UC, const int VC) 
{
	auto Count = 0;
	for (auto i = 0; i < VC - 1; ++i) {
		const auto baseIdx = i * UC;
		for (auto j = 0; j < UC - 1; ++j) {
			const auto idx0 = baseIdx + j, idx1 = baseIdx + j + UCount, idx2 = baseIdx + j + 1, idx3 = baseIdx + j + 1 + UCount;
			// 0 2
			// 1 3
			Buffer[Count++] = idx0;
			Buffer[Count++] = idx1;
			Buffer[Count++] = idx2;

			Buffer[Count++] = idx1;
			Buffer[Count++] = idx3;
			Buffer[Count++] = idx2;
		}
	}
}
void Draw(const Vec3<Scalar>* VB, const uint8_t* IB, const int PC)
{
	const auto Scale = Vec2<SQ15x16>(40.0f, 20.0f);
	const auto Offset = Vec2<SQ15x16>(Arduboy2::width() >> 1, Arduboy2::height() >> 1);

	for (auto i = 0; i < PC; ++i) {
		const auto baseIdx = i * 3;
		const auto idx0 = IB[baseIdx], idx1 = IB[baseIdx + 1], idx2 = IB[baseIdx + 2];
		arduboy.drawTriangle(static_cast<int>(Scale.X() * VB[idx0].X() + Offset.X()), static_cast<int>(Scale.Y() * VB[idx0].Y() + Offset.Y()),
			static_cast<int>(Scale.X() * VB[idx1].X() + Offset.X()), static_cast<int>(Scale.Y() * VB[idx1].Y() + Offset.Y()),
			static_cast<int>(Scale.X() * VB[idx2].X() + Offset.X()), static_cast<int>(Scale.Y() * VB[idx2].Y() + Offset.Y()), WHITE);
		//arduboy.drawTriangle(static_cast<int>(VB[idx0].X()), static_cast<int>(VB[idx0].Y()), static_cast<int>(VB[idx1].X()), static_cast<int>(VB[idx1].Y()), static_cast<int>(VB[idx2].X()), static_cast<int>(VB[idx2].Y()), WHITE);
	}
}

// the setup function runs once when you press reset or power the board
void setup() {
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(30);
	arduboy.initRandomSeed();

	CreateVertexBuffer(VertexBuffer, UCount, VCount, Shape);

	CreateIndexBuffer(IndexBuffer, UCount, VCount);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (arduboy.nextFrame()) {
		arduboy.clear();
		arduboy.pollButtons();

		auto ST = static_cast<int8_t>(Shape);
		if (arduboy.justPressed(A_BUTTON)) { ST++; }
		if (arduboy.justPressed(B_BUTTON)) { ST--; }
		ST = ST < static_cast<int8_t>(ShapeType::Plane) ? static_cast<int8_t>(ShapeType::Plane) : ST;
		ST = ST > static_cast<int8_t>(ShapeType::Count) - 1 ? static_cast<int8_t>(ShapeType::Count) - 1 : ST;
		if (static_cast<int8_t>(Shape) != ST) {		
			Shape = static_cast<enum class ShapeType>(ST);
			CreateVertexBuffer(VertexBuffer, UCount, VCount, Shape);
		}

		const auto Start = millis(); {
			Draw(VertexBuffer, IndexBuffer, PrimitiveCount);
		} const auto End = millis();

#ifdef DRAW_PRINT
		arduboy.setCursor(0, 0);
		arduboy.print("Shape="); arduboy.println(static_cast<int8_t>(Shape));

		arduboy.setCursor(0, Arduboy2::height() - Arduboy2::getCharacterHeight() - Arduboy2::getLineSpacing());
		arduboy.print(End - Start); arduboy.print("msec,");
		arduboy.print("CPU="); arduboy.println(arduboy.cpuLoad());
#endif
		arduboy.display();
	}
}

#include <Arduboy2.h>
#include <FixedPoints.h>
#include <FixedPointsCommon.h>

Arduboy2 arduboy;

//!< 演算テスト用 (For calculation test)
#define SIZE_VALUE(A, B) arduboy.print("Size="); arduboy.println(sizeof(A));\
arduboy.print("A="); arduboy.print(static_cast<float>(A)); arduboy.print(",");\
arduboy.print("B="); arduboy.println(static_cast<float>(B));

#define ADD_SUB(A, B) arduboy.print("A+B="); arduboy.println(static_cast<float>(A + B));\
arduboy.print("A-B="); arduboy.print(static_cast<float>(A - B)); arduboy.print(",");\
arduboy.print("B-A="); arduboy.println(static_cast<float>(B - A));

#define MUL_DIV(A, B) arduboy.print("A*B="); arduboy.println(static_cast<float>(A * B));\
arduboy.print("A/B="); arduboy.print(static_cast<float>(A / B)); arduboy.print(",");\
arduboy.print("B/A="); arduboy.println(static_cast<float>(B / A));

#define FLOOR_CEIL(A) arduboy.print("floorFixed(A)="); arduboy.println(static_cast<float>(floorFixed(A)));\
arduboy.print("ceilFixed(A)="); arduboy.println(static_cast<float>(ceilFixed(A)));

#define ROUND_TRUNC(A) arduboy.print("roundFixed(A)="); arduboy.println(static_cast<float>(roundFixed(A)));\
arduboy.print("truncFixed(A)="); arduboy.println(static_cast<float>(truncFixed(A)));

#define INTEGER(A) arduboy.print("getInteger(A)="); arduboy.println(A.getInteger());

// the setup function runs once when you press reset or power the board
void setup() {
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(60);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (arduboy.nextFrame()) {
		arduboy.pollButtons();

		//!< 定義されているエイリアス (Defined aliases)
		//!< UQ4x4
		//!< UQ8x8
		//!< UQ16x16
		//!< UQ32x32
		//!< UQ1x7
		//!< UQ1x15
		//!< UQ1x31
		//!< UQ1x63
		//!< SQ3x4
		//!< SQ7x8
		//!< SQ15x16
		//!< SQ31x32
		//!< SQ1x6
		//!< SQ1x14
		//!< SQ1x30
		//!< SQ1x62
		
		//!< UQXXXどうし、SQXXXどうしならキャストが可能
		{
			constexpr UQ8x8 u88 = 0.68f;
			constexpr SQ7x8 s88 = 0.68f;

			constexpr auto u1616 = static_cast<UQ16x16>(u88);
			//constexpr auto NG = static_cast<UQ16x16>(s88);

			constexpr auto s1616 = static_cast<SQ15x16>(s88);
			//constexpr auto NG = static_cast<SQ15x16>(u88);
		}

		if(arduboy.justPressed(A_BUTTON)){
			arduboy.clear();
			arduboy.setCursor(0, 0);
			
			constexpr UQ4x4 A = 1.5;
			constexpr UFixed<4, 4> B = 5.25; //!< UQ4x4 は UFiexed<4, 4>
			arduboy.print("UQ4x4,");
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A);

			arduboy.display();
		}
		if(arduboy.justPressed(B_BUTTON)){
			arduboy.clear();
			arduboy.setCursor(0, 0); 
			
			constexpr SQ3x4 A = 1.5;
			constexpr SQ3x4 B = 5.25;
			arduboy.print("SQ3x4,");
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A);

			arduboy.display();
		}

		if (arduboy.justPressed(UP_BUTTON)) {
			arduboy.clear();
			arduboy.setCursor(0, 0);

			constexpr UQ8x8 A = 1.5;
			constexpr UQ8x8 B = 5.25;
			arduboy.print("UQ8x8,");
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A);

			arduboy.display();
		}
		if (arduboy.justPressed(DOWN_BUTTON)) {
			arduboy.clear();
			arduboy.setCursor(0, 0);

			constexpr SQ7x8 A = 1.5;
			constexpr SQ7x8 B = 5.25;
			arduboy.print("SQ7x8,");
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A);

			arduboy.display();
		}
		if (arduboy.justPressed(LEFT_BUTTON)) {
			arduboy.clear();
			arduboy.setCursor(0, 0);

			constexpr UQ16x16 A = 1.5;
			constexpr UQ16x16 B = 5.25;
			arduboy.print("UQ16x16,");
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A);

			arduboy.display();
		}
		if (arduboy.justPressed(RIGHT_BUTTON)) {
			arduboy.clear();
			arduboy.setCursor(0, 0);

			constexpr SQ15x16 A = 1.5;
			constexpr SQ15x16 B = 5.25;
			arduboy.print("SQ15x16,");
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A);

			arduboy.display();
		}

#if false
		//!< 64bit関連は乗算、除算ができない (64bit version cannot multiply and division ?)
		{
			constexpr UQ32x32 A = 1.5;
			constexpr UQ32x32 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			//MUL_DIV(A, B);
			FLOOR_CEIL(A);
		}
		{
			constexpr UQ1x7 A = 1.5;
			constexpr UQ1x7 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A);
		}
		{
			constexpr UQ1x15 A = 1.5;
			constexpr UQ1x15 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A);
		}
		{
			constexpr UQ1x31 A = 1.5;
			constexpr UQ1x31 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A);
		}
		{
			constexpr UQ1x63 A = 1.5;
			constexpr UQ1x63 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			//MUL_DIV(A, B);
			FLOOR_CEIL(A);
		}
		{
			constexpr SQ31x32 A = 1.5;
			constexpr SQ31x32 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			//MUL_DIV(A, B);
			FLOOR_CEIL(A);
		}
		{
			constexpr SQ1x6 A = 1.5;
			constexpr SQ1x6 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A);
		}
		{
			constexpr SQ1x14 A = 1.5;
			constexpr SQ1x14 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A);
		}
		{
			constexpr SQ1x30 A = 1.5;
			constexpr SQ1x30 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A);
		}
		{
			constexpr SQ1x62 A = 1.5;
			constexpr SQ1x62 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			//MUL_DIV(A, B);
			FLOOR_CEIL(A);
		}
#endif
}

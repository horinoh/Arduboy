/*
 Name:		FixedPoint.ino
 Created:	10/11/2020 4:59:24 PM
 Author:	horin
*/

#include <Arduboy2.h>
#include <FixedPoints.h>
#include <FixedPointsCommon.h>

Arduboy2 arduboy;

#define SIZE_VALUE(A, B) arduboy.print("Size="); arduboy.print(sizeof(A)); arduboy.print("\n");\
arduboy.print("A="); arduboy.print(static_cast<float>(A)); arduboy.print(",");\
arduboy.print("B="); arduboy.print(static_cast<float>(B)); arduboy.print("\n");

#define ADD_SUB(A, B) arduboy.print("A+B="); arduboy.print(static_cast<float>(A + B)); arduboy.print("\n");\
arduboy.print("A-B="); arduboy.print(static_cast<float>(A - B)); arduboy.print(",");\
arduboy.print("B-A="); arduboy.print(static_cast<float>(B - A)); arduboy.print("\n");

#define MUL_DIV(A, B) arduboy.print("A*B="); arduboy.print(static_cast<float>(A * B)); arduboy.print("\n");\
arduboy.print("A/B="); arduboy.print(static_cast<float>(A / B)); arduboy.print(",");\
arduboy.print("B/A="); arduboy.print(static_cast<float>(B / A)); arduboy.print("\n");

#define FLOOR_CEIL(A, B) arduboy.print("floorFixed(A)="); arduboy.print(static_cast<float>(floorFixed(A))); arduboy.print("\n");\
arduboy.print("ceilFixed(A)="); arduboy.print(static_cast<float>(ceilFixed(A))); arduboy.print("\n");

#define ROUND_TRUNC(A, B) arduboy.print("roundFixed(A)="); arduboy.print(static_cast<float>(roundFixed(A))); arduboy.print("\n");\
arduboy.print("truncFixed(A)="); arduboy.print(static_cast<float>(truncFixed(A))); arduboy.print("\n");

#define TEST_ALL(A, B) SIZE_VALUE(A, B) ADD_SUB(A, B) MUL_DIV(A, B) FLOOR_CEIL(A, B)

//arduboy.print("getInteger(A)="); arduboy.print(A.getInteger()); arduboy.print("\n");

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

		//!< 定義されているエイリアス
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

		if(arduboy.justPressed(A_BUTTON)){
			arduboy.clear();
			arduboy.setCursor(0, 0);
			
			constexpr UQ4x4 A = 1.5;
			constexpr UFixed<4, 4>/*UQ4x4*/ B = 5.25;
			arduboy.print("UQ4x4,");
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A, B);

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
			FLOOR_CEIL(A, B);

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
			FLOOR_CEIL(A, B);

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
			FLOOR_CEIL(A, B);

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
			FLOOR_CEIL(A, B);

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
			FLOOR_CEIL(A, B);

			arduboy.display();
		}

#if false
		//!< 64bit関連は乗算、除算ができない
		{
			constexpr UQ32x32 A = 1.5;
			constexpr UQ32x32 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			//MUL_DIV(A, B);
			FLOOR_CEIL(A, B);
		}
		{
			constexpr UQ1x7 A = 1.5;
			constexpr UQ1x7 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A, B);
		}
		{
			constexpr UQ1x15 A = 1.5;
			constexpr UQ1x15 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A, B);
		}
		{
			constexpr UQ1x31 A = 1.5;
			constexpr UQ1x31 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A, B);
		}
		{
			constexpr UQ1x63 A = 1.5;
			constexpr UQ1x63 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			//MUL_DIV(A, B);
			FLOOR_CEIL(A, B);
		}
		{
			constexpr SQ31x32 A = 1.5;
			constexpr SQ31x32 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			//MUL_DIV(A, B);
			FLOOR_CEIL(A, B);
		}
		{
			constexpr SQ1x6 A = 1.5;
			constexpr SQ1x6 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A, B);
		}
		{
			constexpr SQ1x14 A = 1.5;
			constexpr SQ1x14 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A, B);
		}
		{
			constexpr SQ1x30 A = 1.5;
			constexpr SQ1x30 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			MUL_DIV(A, B);
			FLOOR_CEIL(A, B);
		}
		{
			constexpr SQ1x62 A = 1.5;
			constexpr SQ1x62 B = 5.25;
			SIZE_VALUE(A, B);
			ADD_SUB(A, B);
			//MUL_DIV(A, B);
			FLOOR_CEIL(A, B);
		}
#endif
	}
}


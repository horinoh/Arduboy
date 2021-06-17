#include <Arduboy2.h>

Arduboy2 arduboy;

//!< 【LED】
//!< アナログモード ... タイマを使う場合衝突する可能性がある
//!< 	setRGBled(0, 0, 0); ... 初期化を兼ねているので、アナログモードに入る前に一度コールする必要がある
//!< 	setRGBled(RED_LED, 255); ... カラーコンポーネント毎のインテンシティを設定
//!< 	freeRGBled(); ... アナログモードの終了
//!< デジタルモード ... (アナログモードの場合)デジタルモードに入る前に一度 freeRGBled() をコールする必要がある
//!< 	digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF); 
//!< 	digitalWriteRGB(RED_LED, RGB_ON); ... カラーコンポーネント毎のオンオフを設定

enum class ColorComponent {
	RED,
	GREEN,
	BLUE,
};
ColorComponent ColorComp = ColorComponent::RED;

uint8_t ToLEDPin[] = {
	RED_LED,
  	GREEN_LED,
  	BLUE_LED
};

enum class LEDMode {
	ANALOG,
	DIGITAL,
};
LEDMode Mode = LEDMode::ANALOG; 

uint8_t AnalogState[] = { 0, 0, 0 };

uint8_t DigitalState[] = { RGB_OFF, RGB_OFF, RGB_OFF };

constexpr uint8_t DigitalRED[] = { RGB_ON, RGB_OFF, RGB_OFF };
constexpr uint8_t DigitalGREEN[] = { RGB_OFF, RGB_ON, RGB_OFF };
constexpr uint8_t DigitalBLUE[] = { RGB_OFF, RGB_OFF, RGB_ON };
constexpr uint8_t DigitalCYAN[] = { RGB_OFF, RGB_ON, RGB_ON };
constexpr uint8_t DigitalMAGENTA[] = { RGB_ON, RGB_OFF, RGB_ON };
constexpr uint8_t DigitalYELLOW[] = { RGB_ON, RGB_ON, RGB_OFF };
constexpr uint8_t DigitalWHITE[] = { RGB_ON, RGB_ON, RGB_ON };
constexpr uint8_t DigitalBLACK[] = { RGB_OFF, RGB_OFF, RGB_OFF };

void onModeChange(LEDMode m){
	if(m == LEDMode::ANALOG){
		arduboy.setRGBled(AnalogState[static_cast<uint8_t>(ColorComponent::RED)], AnalogState[static_cast<uint8_t>(ColorComponent::GREEN)], AnalogState[static_cast<uint8_t>(ColorComponent::BLUE)]);
	} else {
		arduboy.freeRGBled();
		arduboy.digitalWriteRGB(DigitalState[static_cast<uint8_t>(ColorComponent::RED)], DigitalState[static_cast<uint8_t>(ColorComponent::GREEN)], DigitalState[static_cast<uint8_t>(ColorComponent::BLUE)]);
	}
}

// the setup function runs once when you press reset or power the board
void setup() {
	arduboy.begin();
	arduboy.clear();
	arduboy.setFrameRate(60);

	onModeChange(Mode);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (arduboy.nextFrame()) {
		arduboy.clear();
		arduboy.pollButtons();

		//!< アナログ、デジタルモード切替え(トグル)
		if (arduboy.justPressed(A_BUTTON)){
			Mode = Mode == LEDMode::ANALOG ? LEDMode::DIGITAL : LEDMode::ANALOG;
			onModeChange(Mode);
		}
		auto isAnalogMode = Mode == LEDMode::ANALOG;

		//!< デジタルモードのカラーをランダムに変更
		if(!isAnalogMode){
			if (arduboy.justPressed(B_BUTTON)){
				const uint8_t* Candidates[] = { DigitalRED, DigitalGREEN, DigitalBLUE, DigitalCYAN, DigitalMAGENTA, DigitalYELLOW, DigitalWHITE, DigitalBLACK };
				memcpy(DigitalState, Candidates[rand() % (sizeof(Candidates)/sizeof(Candidates[0]))], sizeof(DigitalState));
				arduboy.digitalWriteRGB(DigitalState[static_cast<uint8_t>(ColorComponent::RED)], DigitalState[static_cast<uint8_t>(ColorComponent::GREEN)], DigitalState[static_cast<uint8_t>(ColorComponent::BLUE)]);
			}
		}

		//!< カラーコンポーネントの選択
		auto i = static_cast<uint8_t>(ColorComp);
		if (arduboy.justPressed(LEFT_BUTTON) && i > 0) { i--; }
		if (arduboy.justPressed(RIGHT_BUTTON) && i < static_cast<uint8_t>(ColorComponent::BLUE)) { i++; }
		ColorComp = static_cast<ColorComponent>(i);	

		if(isAnalogMode){
			//!< カラーインテンシティの変更
			if (arduboy.pressed(UP_BUTTON) && AnalogState[i] < 0xff) { AnalogState[i]++; }
			if (arduboy.pressed(DOWN_BUTTON) && AnalogState[i] > 0) { AnalogState[i]--; }
			
			arduboy.setRGBled(ToLEDPin[i], AnalogState[i]);
		} else {
			//!< カラーのオンオフ
			if (arduboy.justPressed(UP_BUTTON)) { DigitalState[i] = RGB_ON; }
			if (arduboy.justPressed(DOWN_BUTTON)) { DigitalState[i] = RGB_OFF; }
			
			arduboy.digitalWriteRGB(ToLEDPin[i], DigitalState[i]);
		}

		{
			arduboy.setCursor(0, 0);
			
			arduboy.print("Mode=");
			arduboy.println(Mode == LEDMode::ANALOG ? "ANALOG" : "DIGITAL");

			arduboy.print("Color=");
			arduboy.println((ColorComp == ColorComponent::RED ? "RED" : (ColorComp == ColorComponent::GREEN ? "GREEN" : "BLUE")));

			if(isAnalogMode){
				arduboy.print("R=");
				arduboy.println(AnalogState[static_cast<uint8_t>(ColorComponent::RED)]);

				arduboy.print("G=");
				arduboy.println(AnalogState[static_cast<uint8_t>(ColorComponent::GREEN)]);

				arduboy.print("B=");
				arduboy.println(AnalogState[static_cast<uint8_t>(ColorComponent::BLUE)]);
			} else {
				arduboy.print("R=");
				arduboy.println(DigitalState[static_cast<uint8_t>(ColorComponent::RED)] == RGB_ON ? "ON" : "OFF");

				arduboy.print("G=");
				arduboy.println(DigitalState[static_cast<uint8_t>(ColorComponent::GREEN)] == RGB_ON ? "ON" : "OFF");

				arduboy.print("B=");
				arduboy.println(DigitalState[static_cast<uint8_t>(ColorComponent::BLUE)] == RGB_ON ? "ON" : "OFF");
			}
		}

		arduboy.display();
	}
}

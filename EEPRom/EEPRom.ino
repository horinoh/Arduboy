#include <Arduboy2.h>
#include <Tinyfont.h>
#include <EEPROM.h>

Arduboy2 arduboy;
auto tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());

//!< 【EEPROM】
//!< 1 バイト書き込みに 3.3ms かかる
//!< 書き換えの寿命は 10 万回

//!< 【バイト】
// int value = EEPROM.read(address);
// EEPROM.write(address, bytes);
// EEPROM.update(address, bytes); ... 値が異なっていれば書き込む
//!< 【オペレータ】
// int value = EEPROM[address];
// EEPROM[address] = value;

//!< 【任意サイズ】
// EEPROM.get(address, T&);
// EEPROM.put(address, const T&&);

struct MyStruct
{
	uint8_t Value8;
	uint16_t Value16;
	uint32_t Value32;
};
//!< 12, 3456, deadbeef
constexpr MyStruct MyData = { 0x12, 0x5634, 0xefbeadde };
constexpr MyStruct ZeroData = { 0, 0, 0 };

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

		//!< A or B ボタンが押された
		if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) { 
			int Adr = EEPROM_STORAGE_SPACE_START;
			if(arduboy.justPressed(A_BUTTON)){
				//!< A が押された場合は、最初のアドレスにランダム値、続くアドレスに MyData を書き込む
				arduboy.initRandomSeed();
				EEPROM.update(Adr, static_cast<byte>(random(0, 256)));
				++Adr;

				EEPROM.put(Adr, MyData);
				Adr += sizeof(MyData);
			} else {
				//!< B が押された場合にはゼロクリアする
				EEPROM[Adr] = 0;
				++Adr;

				EEPROM.put(Adr, ZeroData);
				Adr += sizeof(ZeroData);
			}
		}

		{
			arduboy.clear();

			tinyfont.setCursor(0, 0);
			tinyfont.print("Size = "); tinyfont.print(EEPROM.length());
			tinyfont.setCursor(0, 5);
			tinyfont.print("Start = "); tinyfont.print(EEPROM_STORAGE_SPACE_START);

			tinyfont.setCursor(0, 10);
			for(auto i = EEPROM_STORAGE_SPACE_START;i < /*EEPROM.length()*/EEPROM_STORAGE_SPACE_START + 1 + sizeof(MyStruct);++i){
				tinyfont.print(EEPROM[i], HEX); tinyfont.print(",");
			}
		}

		arduboy.display();
	}
}

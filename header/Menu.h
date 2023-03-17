#pragma once

class Menu {
private:
	const char on_text[5] = { 0xc, 0x30, 'O', 'N', 0 };
	const char off_text[6] = { 0xc, 0x33, 'O', 'F', 'F', 0 };
	
public:
	int cursor_position;
	static const int MAX_ITEMS = 8;
	static const int WALLHACK = 0;
	static const int AIMBOT = 1;
	static const int INTERNALESP = 2;
	static const int EXTERNALESP = 3;
	static const int TRIGGERBOT = 4;
	static const int NORECOIL = 5;
	static const int INFINITELIFE = 6;
	static const int INFINITEAMMO = 7;

	const char* items[MAX_ITEMS] = { "Wallhack",  "Aimbot","InternalESP","ExternalESP", "Triggerbot","NoRecoil","InfiniteLife","InfiniteAmmo"};
	bool item_enabled[MAX_ITEMS] = { false };

	const char* cursor = ">";

	Menu() {
		cursor_position = 0;
	}
	void DisableALL();
	void HandleInput();
	const char* GetState(int);
	bool IsEnable(int);
};

extern Menu menu;
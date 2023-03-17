#include "pch.h"

extern std::mutex mtx;

void Menu::HandleInput() {

	if (GetAsyncKeyState(VK_DOWN) & 1) {
		cursor_position++;
	}
	else if (GetAsyncKeyState(VK_UP) & 1) {
		cursor_position--;
	}
	else if ((GetAsyncKeyState(VK_LEFT) & 1) || (GetAsyncKeyState(VK_RIGHT) & 1)) {
		std::lock_guard<std::mutex> lock(mtx);
		item_enabled[cursor_position] = !item_enabled[cursor_position];
	}

	if (cursor_position < 0) {
		cursor_position = 7;
	}
	else if (cursor_position > 7) {
		cursor_position = 0;
	}
}

const char* Menu::GetState(int item) {
	std::lock_guard<std::mutex> lock(mtx);
	if (item_enabled[item]) return on_text;
	return off_text;
	
}

void Menu::DisableALL() {
	std::lock_guard<std::mutex> lock(mtx);
	for (int i = 0; i < MAX_ITEMS; ++i) {
		item_enabled[i] = FALSE;
	}
}

bool Menu::IsEnable(int item) {
	std::lock_guard<std::mutex> lock(mtx);
	if (item_enabled[item] == TRUE) return true;
	return false;
}
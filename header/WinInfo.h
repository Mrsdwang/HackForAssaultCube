#pragma once
#include "framework.h"
#include "Player.h"
#include "MathCalculation.h"

class WindowsInfo {
private:
public:
	RECT winRect = { 0 };
	RECT gameRect = { 0 };
	HWND newhWnd;

	void CreateNewWindow(const wchar_t*);
	static LRESULT CALLBACK NewWindowProc(HWND , UINT , WPARAM , LPARAM );
	bool GameIsForegroundWindow();
	void UpdateScreen();
	void DrawEsp(vec2d ,float ,PlayerInfo* );
};
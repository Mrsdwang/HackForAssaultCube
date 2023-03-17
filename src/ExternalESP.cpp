#include"pch.h"

extern Menu menu;

void ExternalEsp() {
    WindowsInfo winInfo;
    HWND hWnd = FindWindow(NULL, L"AssaultCube");
    GetWindowRect(hWnd, &winInfo.winRect);
    winInfo.CreateNewWindow(L"Í¸ÊÓ´°¿Ú");
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    PlayerInfo* me = (PlayerInfo*)(ReturnMeAddress());
    MathMatics math = MathMatics();

    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (winInfo.GameIsForegroundWindow() == TRUE)
        {
            SetWindowPos(winInfo.newhWnd, HWND_TOPMOST, winInfo.winRect.left, winInfo.winRect.top, (winInfo.winRect.right - winInfo.winRect.left), (winInfo.winRect.bottom - winInfo.winRect.top), SWP_SHOWWINDOW);
        }
        else
        {
            SetWindowPos(winInfo.newhWnd, HWND_BOTTOM, winInfo.winRect.left, winInfo.winRect.top, (winInfo.winRect.right - winInfo.winRect.left), (winInfo.winRect.bottom - winInfo.winRect.top), SWP_SHOWWINDOW);
        }
        GetWindowRect(hWnd, &winInfo.winRect);
        MoveWindow(winInfo.newhWnd, winInfo.winRect.left, winInfo.winRect.top, (winInfo.winRect.right - winInfo.winRect.left), (winInfo.winRect.bottom - winInfo.winRect.top), TRUE);
        winInfo.UpdateScreen();

        if (IsGameStart(match_type_address)) {
            for (DWORD i = 1; i < ReturnPlayerNum(player_number_address); ++i) {
                if (!IsGameStart(match_type_address)) {
                    break;
                }
                DWORD* others_address = (DWORD*)(ReturnOthersListAddress() + (i*4) );
                PlayerInfo* others = (PlayerInfo*)(*others_address);
                if (others != NULL && menu.IsEnable(menu.EXTERNALESP)) {
                    GetClientRect(hWnd, &winInfo.gameRect);
                    std::shared_ptr<float> matrix = ReturnMatrix();
                    if (math.WorldToScreen(ReturnFeetView(others), matrix, winInfo.gameRect.right, winInfo.gameRect.bottom) && !IsTeamMate(me->team, others->team)) {
                        winInfo.DrawEsp(math.screen, math.GetDistance_3d(ReturnFeetView(me), ReturnFeetView(others)), others);
                    }
                }
            }
        }
        Sleep(1);
    }

}
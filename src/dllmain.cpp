// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include"pch.h"

 Menu menu = Menu();
 std::mutex mtx;

void HackThread() {
    TriggerBot();
    InternalEsp();
    InfiniteLife();
    InfiniteAmmo();
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AimBot, NULL, 0, NULL);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WallHack, NULL, 0, NULL);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ExternalEsp, NULL, 0, NULL);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)NoRecoil, NULL, 0, NULL);

    while (true) {
        if (IsGameStart(match_type_address)) {
            menu.HandleInput();
        }
        else {
            menu.DisableALL();
        }
    }
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        menu.DisableALL();
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HackThread, NULL, 0, NULL);
    }

    return TRUE;
}


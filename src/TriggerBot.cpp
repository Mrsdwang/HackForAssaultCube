#include"pch.h"

extern Menu menu;

PlayerInfo* me = (PlayerInfo*)(ReturnMeAddress());

PlayerInfo* target = NULL;
DWORD ecx_value = 0;

INPUT input = { 0 };
bool isMyDown = true;
DWORD triggerBot_jmpBack_address = 0;

void TriggerBotExecute(DWORD IsTarget) {
    if (IsTarget != 0) {
        if (!IsTeamMate(me->team, target->team)) {
            input.type = INPUT_MOUSE;
            input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            SendInput(1, &input, sizeof(INPUT));
            if (isMyDown) {
                isMyDown = !isMyDown;
            }
        }
    }
    else if(!isMyDown){
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        SendInput(1, &input, sizeof(INPUT));
        isMyDown = !isMyDown;
    }
}

__declspec(naked) void TriggerBot_detour() {
    __asm {
        mov ecx, dword ptr ss : [esp + 0x10]
        pushad
        mov ecx_value, ecx
    }
    target = (PlayerInfo*)ecx_value;
    
    if (IsGameStart(match_type_address) && menu.IsEnable(menu.TRIGGERBOT) ) {
            TriggerBotExecute(ecx_value);
    }
    
    __asm {
        popad
        test ecx, ecx
        jmp triggerBot_jmpBack_address
    }
}

void TriggerBot() {
    DWORD old_protect;
    VirtualProtect((void*)triggerBot_hook_address, 6, PAGE_EXECUTE_READWRITE, &old_protect);
    *triggerBot_hook_address = 0xE9;
    *(DWORD*)(triggerBot_hook_address + 1) = (DWORD)&TriggerBot_detour - (DWORD)triggerBot_hook_address - 5;
    *(triggerBot_hook_address + 5) = 0x90;

    triggerBot_jmpBack_address = (DWORD)(triggerBot_hook_address + 0x6);
}

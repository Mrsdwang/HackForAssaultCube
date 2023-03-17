#include "pch.h"

DWORD infiniteAmmo_jmpBack_address = 0;
DWORD eax_value_ammo = 0;

bool IsMyInfo( ) {
    for (DWORD i = 0; i < 6; i++) {
        if ((eax_value_ammo - (0x140 - (i * 4))) == (DWORD)ReturnMeAddress()) {
            return true;
        }
    }
    return false;
}
__declspec(naked) void infiniteAmmo_Detour() {
    __asm {
        pushad
        mov eax_value_ammo,eax
    }
    if (menu.IsEnable(menu.INFINITEAMMO) && IsMyInfo()) {
        __asm {
            popad
            lea eax,dword ptr ss:[esp+0x1C]
            jmp infiniteAmmo_jmpBack_address
        }
    }
    else {
        __asm {
            popad
            dec dword ptr ds:[eax]
            lea eax,dword ptr ss:[esp+0x1C]
            jmp infiniteAmmo_jmpBack_address
        }
    }
}


void InfiniteAmmo() {
    DWORD old_protect;
    VirtualProtect((void*)infiniteAmmo_hook_address, 6, PAGE_EXECUTE_READWRITE, &old_protect);
    *infiniteAmmo_hook_address = 0xE9;
    *(DWORD*)(infiniteAmmo_hook_address + 1) = (DWORD)&infiniteAmmo_Detour - (DWORD)infiniteAmmo_hook_address - 5;
    *(infiniteAmmo_hook_address + 0x5) = 0x90;
    infiniteAmmo_jmpBack_address = (DWORD)(infiniteAmmo_hook_address + 0x6);
}

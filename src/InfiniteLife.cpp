#include"pch.h"

extern Menu menu;
DWORD infiniteLife_jmpBack_address = 0;
DWORD ebx_value = 0;

__declspec(naked) void InfiniteLife_detour() {
    __asm {
        pushad
        sub ebx,0xE8
        mov ebx_value,ebx
    }
    if ( menu.IsEnable(menu.INFINITELIFE) && (ebx_value == (DWORD)ReturnMeAddress())) {
        __asm {
            popad
            sub dword ptr ds:[ebx+0x4],0
            jmp infiniteLife_jmpBack_address
        }
    }
    else {
        __asm {
            popad
            sub dword ptr ds:[ebx+0x4],esi
            mov eax,esi
            jmp infiniteLife_jmpBack_address
        }
    }
}


void InfiniteLife() {
    DWORD old_protect;
    VirtualProtect((void*)infiniteLife_hook_address, 6, PAGE_EXECUTE_READWRITE, &old_protect);
    *infiniteLife_hook_address = 0xE9;
    *(DWORD*)(infiniteLife_hook_address + 1) = (DWORD)&InfiniteLife_detour - (DWORD)infiniteLife_hook_address - 5;

    infiniteLife_jmpBack_address = (DWORD)(infiniteLife_hook_address + 0x5);
}

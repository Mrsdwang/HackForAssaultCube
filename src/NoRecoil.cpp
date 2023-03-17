#include"pch.h"

extern Menu menu;

DWORD eax_value = 0;
DWORD shootPushBackx_jmpBack_address = 0;
DWORD shootPushBacky_jmpBack_address = 0;
DWORD shootPushBackz_jmpBack_address = 0;
DWORD shootPitchUp_jmpBack_address = 0;
__declspec(naked) void shootPushBackx_Detour() {
    __asm {
        pushad
        mov eax_value,eax
    }
    if (menu.IsEnable(menu.NORECOIL) && (eax_value == (DWORD)ReturnMeAddress())) {
        __asm {
            popad
            mov dword ptr ds:[eax+0x10],0
            jmp shootPushBackx_jmpBack_address
        }
    }
    else {
        __asm {
            popad
            movss dword ptr ds : [eax + 0x10] , xmm0
            jmp shootPushBackx_jmpBack_address
        }
    }
}


__declspec(naked) void shootPushBacky_Detour() {
    __asm {
        pushad
        mov eax_value, eax
    }
    if (menu.IsEnable(menu.NORECOIL) && (eax_value == (DWORD)ReturnMeAddress())) {
        __asm {
            popad
            mov dword ptr ds : [eax + 0x14] , 0
            jmp shootPushBacky_jmpBack_address
        }
    }
    else {
        __asm {
            popad
            movss dword ptr ds : [eax + 0x14] , xmm0
            jmp shootPushBacky_jmpBack_address
        }
    }
}

__declspec(naked) void shootPushBackz_Detour() {
    __asm {
        pushad
        mov eax_value, eax
    }
    if (menu.IsEnable(menu.NORECOIL) && (eax_value == (DWORD)ReturnMeAddress())) {
        __asm {
            popad
            mov dword ptr ds : [eax + 0x18] , 0
            jmp shootPushBackz_jmpBack_address
        }
    }
    else {
        __asm {
            popad
            movss dword ptr ds : [eax + 0x18] , xmm1
            jmp shootPushBackz_jmpBack_address
        }
    }
}

__declspec(naked) void shootPitchUp_Detour() {
    __asm {
        pushad
        mov eax_value, eax
    }
    if (menu.IsEnable(menu.NORECOIL) && (eax_value == (DWORD)ReturnMeAddress())) {
        __asm {
            popad
            mov dword ptr ds : [eax + 0x40] , 0
            jmp shootPitchUp_jmpBack_address
        }
    }
    else {
        __asm {
            popad
            movss dword ptr ds : [eax + 0x40] , xmm2
            jmp shootPitchUp_jmpBack_address
        }
    }
}


void NoRecoil() {
    DWORD old_protect;
    VirtualProtect((void*)shootPushBackx_hook_address, 6, PAGE_EXECUTE_READWRITE, &old_protect);
    *shootPushBackx_hook_address = 0xE9;
    *(DWORD*)(shootPushBackx_hook_address + 1) = (DWORD)&shootPushBackx_Detour - (DWORD)shootPushBackx_hook_address - 5;
    shootPushBackx_jmpBack_address = (DWORD)(shootPushBackx_hook_address + 0x5);

    VirtualProtect((void*)shootPushBacky_hook_address, 6, PAGE_EXECUTE_READWRITE, &old_protect);
    *shootPushBacky_hook_address = 0xE9;
    *(DWORD*)(shootPushBacky_hook_address + 1) = (DWORD)&shootPushBacky_Detour - (DWORD)shootPushBacky_hook_address - 5;
    shootPushBacky_jmpBack_address = (DWORD)(shootPushBacky_hook_address + 0x5);

    VirtualProtect((void*)shootPushBackz_hook_address, 6, PAGE_EXECUTE_READWRITE, &old_protect);
    *shootPushBackz_hook_address = 0xE9;
    *(DWORD*)(shootPushBackz_hook_address + 1) = (DWORD)&shootPushBackz_Detour - (DWORD)shootPushBackz_hook_address - 5;
    shootPushBackz_jmpBack_address = (DWORD)(shootPushBackz_hook_address + 0x5);

    VirtualProtect((void*)shootPitchUp_hook_address, 6, PAGE_EXECUTE_READWRITE, &old_protect);
    *shootPitchUp_hook_address = 0xE9;
    *(DWORD*)(shootPitchUp_hook_address + 1) = (DWORD)&shootPitchUp_Detour - (DWORD)shootPitchUp_hook_address - 5;
    shootPitchUp_jmpBack_address = (DWORD)(shootPitchUp_hook_address + 0x5);
}
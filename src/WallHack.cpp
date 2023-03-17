#include"pch.h"

extern Menu menu;

HMODULE OpenGLHandle = NULL;
void(__stdcall* glDepthFunc)(unsigned int) = NULL;
unsigned char* wallHack_hook_address = NULL;

DWORD wallHack_jmpBack_address = 0;

__declspec(naked) void wallHack_detour() {
    __asm {
        pushad
    }
    if (IsGameStart(match_type_address) && menu.IsEnable(menu.WALLHACK)) {
        (*glDepthFunc)(0x207);
    }
    __asm {
        popad
        mov esi, dword ptr ds : [esi + 0xA18]
        jmp wallHack_jmpBack_address
    }
}

void WallHack() {
	while (true) {
		if (OpenGLHandle == NULL) {
			OpenGLHandle = GetModuleHandle(L"opengl32.dll");
		}
		if (OpenGLHandle != NULL) {
			glDepthFunc = (void(__stdcall*)(unsigned int))GetProcAddress(OpenGLHandle, "glDepthFunc");
            wallHack_hook_address = (unsigned char*)GetProcAddress(OpenGLHandle, "glDrawElements");
            wallHack_hook_address += 0x16;

            DWORD old_protect;
            VirtualProtect((void*)wallHack_hook_address, 5, PAGE_EXECUTE_READWRITE, &old_protect);
            *wallHack_hook_address = 0xE9;
            *(DWORD*)(wallHack_hook_address + 1) = (DWORD)&wallHack_detour - (DWORD)wallHack_hook_address - 5;
            *(wallHack_hook_address + 5) = 0x90;

            wallHack_jmpBack_address = (DWORD)(wallHack_hook_address + 0x6);
            break;
		}
        Sleep(1);
	}
}
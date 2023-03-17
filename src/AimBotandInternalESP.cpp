#include"pch.h"

DWORD internalEsp_jmpBack_address = 0;

InternalEspInfo EspInfo;

extern Menu menu;

const char* text = "";
const char* empty_text = "";


void print_text(DWORD x, DWORD y, const char* text) {

    if (x > 2400 || x < 0 || y < 0 || y > 1800 ) {
        text = "";
    }
    __asm {
        push y
        push x
        push text
        call InternalEsp_print_address
        add esp, 0xC
    }
}


__declspec(naked) void InternalEsp_detour() {

    __asm {
        sub esp, 4
        push empty_text
        call InternalEsp_print_address
        pushad
    }
    // print menu
    
    if (!IsGameStart(match_type_address)) {
        print_text(50, 250 ,"Game doesn't start");
    }
    else {
        for (DWORD i = 0; i < menu.MAX_ITEMS; ++i) {
            print_text(50, 250 + (100 * i), menu.items[i]);
            print_text(500, 250 + (100 * i), menu.GetState(i));
        }
        print_text(10, 250 + (100 * menu.cursor_position), menu.cursor);

        //internal esp
        if ( menu.IsEnable(menu.INTERNALESP)) {
            for (DWORD i = 1; i < *player_number_address; i++) {
                print_text(EspInfo.x_val[i], EspInfo.y_val[i], EspInfo.print_text[i].c_str());
            }
        }
    }
    __asm {
        popad
        jmp internalEsp_jmpBack_address
    }
}


void AimBot() {

	PlayerInfo* me = (PlayerInfo*)(ReturnMeAddress());
	MathMatics math = MathMatics();
	while (TRUE) {
        if (IsGameStart(match_type_address)) {
            math.InitData();
            for (DWORD i = 1; i < ReturnPlayerNum(player_number_address); ++i) {
                if (!IsGameStart(match_type_address)) {
                    break;
                }
                DWORD* others_address = (DWORD*)(ReturnOthersListAddress() + (i * 4));
                PlayerInfo* others = (PlayerInfo*)(*others_address);
                if (others != NULL) {
                    if (!others->dead && !IsTeamMate(me->team, others->team)) {
                        math.CalcutationForYawPit(me, others, EspInfo, i);
                        EspInfo.print_text[i] = print_info(others);
                    }
                    if (others->dead) {
                        EspInfo.print_text[i] = "";
                    }
                }
            }
            if (menu.IsEnable(menu.AIMBOT) && (GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
                if (!IsAllDead() && IsSeen(math.closest_player)) {
                    math.WriteClosestYawPit(me);
                }
            }
        }
		Sleep(1);
	}
}

void InternalEsp() {
	DWORD old_protect;
	VirtualProtect((void*)InternalEsp_hook_address, 6, PAGE_EXECUTE_READWRITE, &old_protect);
	*InternalEsp_hook_address = 0xE9;
	*(DWORD*)(InternalEsp_hook_address + 1) = (DWORD)&InternalEsp_detour - (DWORD)InternalEsp_hook_address - 5;

    internalEsp_jmpBack_address = (DWORD)(InternalEsp_hook_address + 0x5);
}
#pragma once
#include "framework.h"

static DWORD* me_offset_address = (DWORD*)(0x58AC00);
static DWORD* others_list_offset_address = (DWORD*)(0x58AC04);
static DWORD* player_number_address = (DWORD*)(0x58AC0C);
static DWORD* match_type_address = (DWORD*)(0x58ABF8);

static float* MVP_matrix_address = (float*)(0x57DFD0);

static unsigned char* infiniteLife_hook_address = (unsigned char*)0x41C223;
static unsigned char* infiniteAmmo_hook_address = (unsigned char*)0x4C73EF;
static unsigned char* shootPushBackx_hook_address = (unsigned char*)0x4C8DD2;
static unsigned char* shootPushBacky_hook_address = (unsigned char*)0x4C8DFB;
static unsigned char* shootPushBackz_hook_address = (unsigned char*)0x4C8E03;
static unsigned char* shootPitchUp_hook_address = (unsigned char*)0x4C8E52;
static unsigned char* triggerBot_hook_address = (unsigned char*)0x45FD42;
static unsigned char* InternalEsp_hook_address = (unsigned char*)0x46138D;
static DWORD InternalEsp_print_address = 0x46E640;

static const DWORD  TeamMatch = 0x7;
static const DWORD GameNotStart = 0x0;

static DWORD headx_offset = 0x4;
static DWORD heady_offset = 0x8;
static DWORD headz_offset = 0xC;

static DWORD feetx_offset = 0x28;
static DWORD feety_offset = 0x2C;
static DWORD feetz_offset = 0x30;

static DWORD yaw_offset = 0x34;
static DWORD pitch_offset = 0x38;

static DWORD HP_offset = 0xEC;
static DWORD name_offset = 0x205;
static DWORD team_offset = 0x30C;
static DWORD dead_offset = 0x318;





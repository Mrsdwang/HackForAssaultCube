#pragma once

struct PlayerInfo {
    char unknown1[0x4];
    float x;
    float y;
    float z;
    char unknown2[0x18];
    float feet_x;
    float feet_y;
    float feet_z;
    float yaw;
    float pit;
    char unknown3[0xB0];
    int HP;
    char unknown4[0x115];
    char name[0x0F];
    char unknown5[0xF8];
    int team;
    char unknown6[0x8];
    int dead;
    char unknown7[0xDC];
    float seen;
};


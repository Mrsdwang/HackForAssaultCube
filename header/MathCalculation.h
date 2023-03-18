#pragma once
#include "framework.h"
#include "Player.h"
#include "Data.h"
#include "InternalESP.h"

struct vec2d {
    float x, y;
};

struct vec3d {
    float x, y, z;
};

struct vec4d {
    float x, y, z, w;
};


class MathMatics {
private:
    

public:
    const double PI = 3.14159265358979323846;
    vec2d screen = { 0,0 };
    vec4d clipCoords = { 0,0,0,0 };
    vec4d NDC = { 0,0,0,0 };
    PlayerInfo* closest_player = NULL;

    float closest_distance = -1.0f;
    float closest_yaw = 0.0f;
    float closest_pit = 0.0f;

    bool WorldToScreen(vec3d, const std::shared_ptr<float>&, int, int);
    float GetDistance_3d(vec3d , vec3d );
    float GetDistance_2d(float,float );

    void CalcutationForYawPit(PlayerInfo* , PlayerInfo* , InternalEspInfo& , int );
    void InitData();
    void WriteClosestYawPit(PlayerInfo*);
};

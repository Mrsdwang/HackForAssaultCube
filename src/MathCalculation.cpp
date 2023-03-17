#include"pch.h"

float MathMatics::GetDistance_2d(float x, float y) {
    return sqrtf((x * x) + (y * y));
}

float MathMatics::GetDistance_3d(vec3d me, vec3d others) {
    return (float)(sqrt(((others.x - me.x) * (others.x - me.x))
                      + ((others.y - me.y) * (others.y - me.y))
                      + ((others.z - me.z) * (others.z - me.z))));
}

bool MathMatics::WorldToScreen(vec3d feet_pos, const std::shared_ptr<float>& matrix, int windowWidth, int windowHeight) {
    clipCoords.x = feet_pos.x * (*matrix.get()) + feet_pos.y * (*(matrix.get()+4)) + feet_pos.z * (*(matrix.get() + 8)) + (*(matrix.get() + 12));
    clipCoords.y = feet_pos.x * (*(matrix.get() + 1)) + feet_pos.y * (*(matrix.get() + 5)) + feet_pos.z * (*(matrix.get() + 9)) + (*(matrix.get() + 13));
    clipCoords.z = feet_pos.x * (*(matrix.get() + 2)) + feet_pos.y * (*(matrix.get() + 6)) + feet_pos.z * (*(matrix.get() + 10)) + (*(matrix.get() + 14));
    clipCoords.w = feet_pos.x * (*(matrix.get() + 3)) + feet_pos.y * (*(matrix.get() + 7)) + feet_pos.z * (*(matrix.get() + 11)) + (*(matrix.get() + 15));

    if (clipCoords.w < 0.1f) {
        return false;
    }

    NDC.x = clipCoords.x / clipCoords.w;
    NDC.y = clipCoords.y / clipCoords.w;
    NDC.z = clipCoords.z / clipCoords.w;

    screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
    screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);

    return true;
}

void MathMatics::InitData() {
    screen = { 0,0 };
    clipCoords = { 0,0,0,0 };
    NDC = { 0,0,0,0 };

    closest_distance = -1.0f;
    closest_yaw = 0.0f;
    closest_pit = 0.0f;
}

void MathMatics::CalcutationForYawPit(PlayerInfo* me, PlayerInfo* others, InternalEspInfo& EspInfo, int i){
    vec3d abspos = { 0,0,0 };
    abspos.x = others->x - me->x;
    abspos.y = others->y - me->y;
    abspos.z = others->z - me->z;

    float abs_distance = GetDistance_2d(abspos.x, abspos.y);

    float temp_closest_distance = abs_distance;

    float arctan_yx = atan2f(abspos.y, abspos.x);
    float temp_closest_yaw = ((float)(arctan_yx * (180.0 / PI))) + 90;
        
    float absyaw = me->yaw - temp_closest_yaw;
    if (absyaw > 180) absyaw -= 360;
    if (absyaw < -180) absyaw += 360;
	EspInfo.x_val[i] = (1200 + (absyaw * (-30)));

    if (abspos.y < 0) abspos.y *= -1;
    if (abspos.y < 5) {
        if (abspos.x < 0) abspos.x *= -1;
        abspos.y = abspos.x;
    }
    float arctan_zy = atan2f(abspos.z, abspos.y);
    float temp_closest_pit = (float)(arctan_zy * (180.0 / PI));

    float abspit = me->pit - temp_closest_pit;
    EspInfo.y_val[i] = (900 + ((abspit) * 25));

    if (closest_distance == -1.0f || abs_distance < closest_distance) {
        closest_player = others;
        closest_distance = abs_distance;
        closest_yaw = temp_closest_yaw;
        closest_pit = temp_closest_pit;
    }

}

void MathMatics::WriteClosestYawPit(PlayerInfo* me) {
    me->yaw = closest_yaw;
    me->pit = closest_pit;
}
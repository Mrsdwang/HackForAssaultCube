#include"pch.h"


bool IsGameStart(DWORD* match_type) {
	std::lock_guard<std::mutex> lock(mtx);
	return *match_type != GameNotStart ? true : false;
}

bool IsTeamMatch(DWORD* match_type) {
	std::lock_guard<std::mutex> lock(mtx);
	return *match_type == TeamMatch ? true : false;
}

bool IsTeamMate(DWORD myTeam,DWORD othersTeam) {
	if (IsTeamMatch(match_type_address)) {
		return  myTeam == othersTeam ? true : false;
	}
	return false;
}

DWORD ReturnPlayerNum(DWORD* player_number) {
	std::lock_guard<std::mutex> lock(mtx);
	return *player_number;
}

DWORD ReturnOthersListAddress() {
	std::lock_guard<std::mutex> lock(mtx);
	return *others_list_offset_address;
}

DWORD ReturnMeAddress() {
	std::lock_guard<std::mutex> lock(mtx);
	return *me_offset_address;
}

vec3d ReturnFeetView(PlayerInfo* player) {
	std::lock_guard<std::mutex> lock(mtx);
	vec3d f_view = { player->feet_x,player->feet_y,player->feet_z };
	return f_view;
}

vec3d ReturnHeadView(PlayerInfo* player) {
	std::lock_guard<std::mutex> lock(mtx);
	vec3d h_view = { player->x,player->y,player->z };
	return h_view;
}

std::shared_ptr<float> ReturnMatrix() {
	std::lock_guard<std::mutex> lock(mtx);
	std::shared_ptr<float> matrix(new float[16], [](float* p) { delete[] p; });
	memcpy(matrix.get(), MVP_matrix_address, sizeof(float) * 16);
	return matrix;
}

bool IsAllDead() {
	for (DWORD i = 1; i < ReturnPlayerNum(player_number_address); ++i) {
		DWORD* others_address = (DWORD*)(ReturnOthersListAddress() + (i * 4));
		PlayerInfo* others = (PlayerInfo*)(*others_address);
		if (others != NULL) {
			std::lock_guard<std::mutex> lock(mtx);
			if (others->dead == 0x0) {
				return false;
			}
		}
	}
	return true;
}

bool IsSeen(PlayerInfo* closest_player) {
	std::lock_guard<std::mutex> lock(mtx);
	if (closest_player->dead == 0x1 || closest_player->seen < 0) {
		return false;
	}
	return true;
}

std::string print_info(PlayerInfo* others) {
	std::string text;
	if (others->dead != 0x1) {
		text = std::to_string(others->HP) + "HP: " + others->name;
	}
	else {
		text = "";
	}
	return text;
}
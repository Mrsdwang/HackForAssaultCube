#pragma once

void WallHack();
void TriggerBot();
void NoRecoil();
void InternalEsp();
void AimBot();
void ExternalEsp();
void InfiniteLife();
void InfiniteAmmo();

bool IsTeamMatch(DWORD*);
bool IsGameStart(DWORD*);
bool IsTeamMate(DWORD, DWORD);
bool IsAllDead();
bool IsSeen(PlayerInfo*);

DWORD ReturnPlayerNum(DWORD*);
DWORD ReturnOthersListAddress();
DWORD ReturnMeAddress();
vec3d ReturnFeetView(PlayerInfo*);
vec3d ReturnHeadView(PlayerInfo*);
std::shared_ptr<float> ReturnMatrix();
std::string print_info(PlayerInfo*);

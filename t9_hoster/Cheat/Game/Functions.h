#pragma once
#include "../Main.h"


#define M_PI 3.14159265358979323846
#define M_PI_F ((float)(M_PI))
#define DEG2RAD(x) ( (float)(x) * (float)(M_PI_F / 180.f) )

struct ScrVmContext_t;
enum ScrString_t;

void CG_GameMessage(int localClientNum, const char* msg);
int Add_Ammo(uintptr_t ent, uintptr_t weapon, int count, bool fillClip);
uintptr_t G_Spawn();
uintptr_t G_SpawnFake();
void G_SetOrigin(uintptr_t ent, const float* origin);
void G_SetAngle(uintptr_t ent, const float* angles);
void G_SetModel(uintptr_t ent, uintptr_t modelName);
void SV_LinkEntity(uintptr_t ent);
void SV_SetBrushModel(uintptr_t ent);
bool G_CallSpawnEntity(uintptr_t ent);
void G_FreeEntity(uintptr_t ed);
void ScrStr_SetString(int* to, int from);
void AngleVectors(const float* angles, float* forward, float* right, float* up);
void G_GetPlayerViewDirection(uintptr_t ent, float* forward, float* right, float* up);
void G_GetPlayerViewOrigin(uintptr_t ps, float* origin);
bool G_DObjGetWorldTagPos(uintptr_t ent, int tagName, float* pos);
void vectoangles(const float* vec, float* angles);
void SetClientViewAngle(uintptr_t ent, const float* angle);
double Abs(const float* v);
float Vec3Distance(const float* v1, const float* v2);
void SV_SetConfigstring(const int index, const char* val);
bool Com_IsGameServerRunning();
void G_InitPlayerLinkAngles(uintptr_t ent);
bool G_EntLinkTo(uintptr_t ent, uintptr_t parent, int tagName);
uintptr_t GetEntity(int entNum);
void SV_GameSendServerCommand(int clientNum, int type, const char* text);
int getClosestToPoint(const float* point, float range);

void R_SetFogFromServer(int localClientNum, float start, float r, float g, float b, float density, float heightDensity, float baseHeight, float fogColorScale, float sunFogColorR, float sunFogColorG, float sunFogColorB, float sunFogDirX, float sunFogDirY, float sunFogDirZ, float sunFogStartAng, float sunFogEndAng, float fogMaxOpacity);
void R_SwitchFog(int localClientNum, int fogvar, int startTime, int transitionTime);
void VM_OP_Notify_Handler(int a1, __int64 a2, ScrVmContext_t* a3, __int64 a4);


uintptr_t ScrStr_ConvertToHash(ScrString_t stringValue);
const char* ScrStr_ConvertToString(ScrString_t stringValue);
void G_DamageActor(uintptr_t targ, uintptr_t inflictor, uintptr_t attacker, const float* dir, const float* point, int damage, int dflags, int mod, __int64 weapon, __int64 a10, int a11, float* a12, int a13, __int16 a14, int a15, char a16, __int64 a17);
int getNearestZombie(int clientNum);


int I_strncmp(const char* s0, const char* s1, size_t n);

ScrString_t SL_GetStringOfSize(const char* str, unsigned int user, unsigned int len, int type);
ScrString_t ScrStr_GetString(const char* str, unsigned int user, int type);
uintptr_t GScr_Spawn(const char* classname, const float* origin);
void sub_7FF747882230(uintptr_t entity, uintptr_t model, __int64 a3);

uintptr_t UI_GetFontHandle(uintptr_t scrPlace, int fontEnum, float scale);

void R_AddCmdDrawTextW(const char* text, int maxLength, uintptr_t font, float x, float y, float xScale, float yScale, float rotation, const float* color, int style);

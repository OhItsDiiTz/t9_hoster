#include "Functions.h"


void CG_GameMessage(int localClientNum, const char* msg) {
	auto cg_gamemessage = reinterpret_cast<void(*)(int, const char*)>(g_Addrs.cg_gamemessage);
	cg_gamemessage(localClientNum, msg);
}

int Add_Ammo(uintptr_t ent, uintptr_t weapon, int count, bool fillClip) {
	auto add_ammo = reinterpret_cast<int(*)(uintptr_t ent, uintptr_t weapon, int count, bool fillClip)>(g_Addrs.add_ammo);
	return add_ammo(ent, weapon, count, fillClip);
}

uintptr_t G_Spawn() {
	auto g_spawn = reinterpret_cast<uintptr_t(*)()>(g_Addrs.g_spawn);
	return g_spawn();
}

uintptr_t G_SpawnFake() {
	auto g_fakespawn = reinterpret_cast<uintptr_t(*)()>(g_Addrs.g_fakespawn);
	return g_fakespawn();
}

void G_SetOrigin(uintptr_t ent, const float* origin) {
	auto g_setorigin = reinterpret_cast<void(*)(uintptr_t, const float*)>(g_Addrs.g_setorigin);
	g_setorigin(ent, origin);
}

void G_SetAngle(uintptr_t ent, const float* angles) {
	auto g_setangle = reinterpret_cast<void(*)(uintptr_t, const float*)>(g_Addrs.g_setangle);
	g_setangle(ent, angles);
}

void G_SetModel(uintptr_t ent, uintptr_t modelName) {
	auto g_setmodel = reinterpret_cast<void(*)(uintptr_t, uintptr_t)>(g_Addrs.g_setmodel);
	g_setmodel(ent, modelName);
}

void SV_LinkEntity(uintptr_t ent) { //spoof call
	auto sv_linkentity = reinterpret_cast<void(*)(uintptr_t)>(g_Addrs.sv_linkentity);
	spoof_call((void*)(g_Addrs.jmp_rbx), sv_linkentity, ent);
}

void SV_SetBrushModel(uintptr_t ent) { //spoof call
	auto sv_setbrushmodel = reinterpret_cast<void(*)(uintptr_t)>(g_Addrs.sv_setbrushmodel);

	spoof_call((void*)(g_Addrs.sv_setbrushmodel), sv_setbrushmodel, ent);
}

bool G_CallSpawnEntity(uintptr_t ent) {
	auto g_callspawnentity = reinterpret_cast<bool(*)(uintptr_t)>(g_Addrs.g_callspawnentity);
	return g_callspawnentity(ent);
}

void G_FreeEntity(uintptr_t ed) { //spoof call
	auto g_freeentity = reinterpret_cast<void(*)(uintptr_t)>(g_Addrs.g_freeentity);
	spoof_call((void*)(g_Addrs.jmp_rbx), g_freeentity, ed);
}

void ScrStr_SetString(int* to, int from) {
	auto scrstr_setstring = reinterpret_cast<void(*)(int*, int)>(g_Addrs.scrstr_setstring);
	scrstr_setstring(to, from);
}

void inline SinCos(float radians, float* sine, float* cosine)
{
	*sine = sinf(radians);
	*cosine = cosf(radians);
}

void AngleVectors(const float* angles, float* forward, float* right, float* up) {
	float sr, sp, sy, cr, cp, cy;
	SinCos(DEG2RAD(angles[1]), &sy, &cy);
	SinCos(DEG2RAD(angles[0]), &sp, &cp);
	SinCos(DEG2RAD(angles[2]), &sr, &cr);

	if (forward)
	{
		forward[0] = cp * cy;
		forward[1] = cp * sy;
		forward[2] = -sp;
	}

	if (right)
	{
		right[0] = (-1 * sr * sp * cy + -1 * cr * -sy);
		right[1] = (-1 * sr * sp * sy + -1 * cr * cy);
		right[2] = -1 * sr * cp;
	}

	if (up)
	{
		up[0] = (cr * sp * cy + -sr * -sy);
		up[1] = (cr * sp * sy + -sr * cy);
		up[2] = cr * cp;
	}
}

void G_GetPlayerViewDirection(uintptr_t ent, float* forward, float* right, float* up) {
	auto g_getplayerviewdirection = reinterpret_cast<void(*)(uintptr_t, float*, float*, float*)>(g_Addrs.g_getplayerviewdirection);
	
	spoof_call((void*)(g_Addrs.jmp_rbx), g_getplayerviewdirection, ent, forward, right, up);
}

void G_GetPlayerViewOrigin(uintptr_t ps, float* origin) {
	auto g_getplayervieworigin = reinterpret_cast<void(*)(uintptr_t, float*)>(g_Addrs.g_getplayervieworigin);
	spoof_call((void*)(g_Addrs.jmp_rbx), g_getplayervieworigin, ps, origin);
}

bool G_DObjGetWorldTagPos(uintptr_t ent, int tagName, float* pos) {
	auto g_dobjgetworldtagpos = reinterpret_cast<bool(*)(uintptr_t, int, float*)>(g_Addrs.g_dobjgetworldtagpos);
	return g_dobjgetworldtagpos(ent, tagName, pos);
}

void vectoangles(const float* vec, float* angles) {
	auto vec2angles = reinterpret_cast<void(*)(const float*, float*)>(g_Addrs.vectoangles);
	vec2angles(vec, angles);
}

void SetClientViewAngle(uintptr_t ent, const float* angle) {
	auto setclientviewangle = reinterpret_cast<void(*)(uintptr_t, const float*)>(g_Addrs.setclientviewangle);
	setclientviewangle(ent, angle);
}

double Abs(const float* v)
{
	return (float)sqrt((float)((float)((float)(v[0] * v[0]) + (float)(v[1] * v[1])) + (float)(v[2] * v[2])));
}

float Vec3Distance(const float* v1, const float* v2)
{
	float dir[3];

	dir[0] = v2[0] - v1[0];
	dir[1] = v2[1] - v1[1];
	dir[2] = v2[2] - v1[2];
	return Abs(dir);
}



void SV_SetConfigstring(const int index, const char* val) {
	auto sv_setconfigstring = reinterpret_cast<void(*)(int, const char*)>(g_Addrs.sv_setconfigstring);
	sv_setconfigstring(index, val);
}

bool Com_IsGameServerRunning() {
	auto com_isgameserverrunning = reinterpret_cast<bool(*)()>(g_Addrs.com_isgameserverrunning);
	return com_isgameserverrunning();
}

void G_InitPlayerLinkAngles(uintptr_t ent) {
	auto g_initplayerlinkangles = reinterpret_cast<void(*)(uintptr_t)>(g_Addrs.g_initplayerlinkangles);
	g_initplayerlinkangles(ent);
}


bool G_EntLinkTo(uintptr_t ent, uintptr_t parent, int tagName) {
	auto g_entlinkto = reinterpret_cast<bool(*)(uintptr_t, uintptr_t, int)>(g_Addrs.g_entlinkto);
	return g_entlinkto(ent, parent, tagName);
}

uintptr_t GetEntity(int entNum) {
	auto getentity = reinterpret_cast<uintptr_t(*)(int)>(g_Addrs.getentity);
	return getentity(entNum);
}

void SV_GameSendServerCommand(int clientNum, int type, const char* text) {
	auto sv_gamesendservercommand = reinterpret_cast<void(*)(int, int, const char*)>(g_Addrs.sv_gamesendservercommand);
	sv_gamesendservercommand(clientNum, type, text);
}

int getClosestToPoint(const float* point, float range) {
	float dist = range;
	int nearest = 0;
	bool found;
	for (int i = 18; i < 1024; i++) {
		uintptr_t ent = GetEntity(i);
		if (*reinterpret_cast<short*>(ent + 0x338) != 0) {
			float distance = Vec3Distance((float*)(ent + 0x2D4), point);
			if (distance <= dist) {
				dist = distance;
				nearest = i;
				found = true;
			}
		}
	}
	if (found) {
		return nearest;
	}
	return 0;
}

void R_SetFogFromServer(int localClientNum, float start, float r, float g, float b, float density, float heightDensity, float baseHeight, float fogColorScale, float sunFogColorR, float sunFogColorG, float sunFogColorB, float sunFogDirX, float sunFogDirY, float sunFogDirZ, float sunFogStartAng, float sunFogEndAng, float fogMaxOpacity) {
	auto r_setfogfromserver = reinterpret_cast<void(*)(int localClientNum, float start, float r, float g, float b, float density, float heightDensity, float baseHeight, float fogColorScale, float sunFogColorR, float sunFogColorG, float sunFogColorB, float sunFogDirX, float sunFogDirY, float sunFogDirZ, float sunFogStartAng, float sunFogEndAng, float fogMaxOpacity)>(g_Addrs.r_setfogfromserver);
	spoof_call((void*)(g_Addrs.jmp_rbx), r_setfogfromserver, localClientNum, start, r, g, b, density, heightDensity, baseHeight, fogColorScale, sunFogColorR, sunFogColorG, sunFogColorB, sunFogDirX, sunFogDirY, sunFogDirZ, sunFogStartAng, sunFogEndAng, fogMaxOpacity);
}

void R_SwitchFog(int localClientNum, int fogvar, int startTime, int transitionTime) {
	auto r_switchfog = reinterpret_cast<void(*)(int, int, int, int)>(g_Addrs.r_switchfog);
	spoof_call((void*)(g_Addrs.jmp_rbx), r_switchfog, localClientNum, fogvar, startTime, transitionTime);
}

void VM_OP_Notify_Handler(int a1, __int64 a2, ScrVmContext_t* a3, __int64 a4) {
	auto vm_op_notify = reinterpret_cast<void(*)(int, __int64, ScrVmContext_t*, __int64)>(g_Addrs.vm_op_notify_handler);
	vm_op_notify(a1, a2, a3, a4);
}

uintptr_t ScrStr_ConvertToHash(ScrString_t stringValue) {
	auto scrstr_converttohash = reinterpret_cast<uintptr_t(*)(ScrString_t)>(g_Addrs.scrvm_converttohash);
	return scrstr_converttohash(stringValue);
}

const char* ScrStr_ConvertToString(ScrString_t stringValue) {
	auto scrstr_converttostring = reinterpret_cast<const char*(*)(ScrString_t)>(g_Addrs.scrvm_converttostring);
	return scrstr_converttostring(stringValue);
}

void G_DamageActor(uintptr_t targ, uintptr_t inflictor, uintptr_t attacker, const float* dir, const float* point, int damage, int dflags, int mod, __int64 weapon, __int64 a10, int a11, float* a12, int a13, __int16 a14, int a15, char a16, __int64 a17) {
	auto func = reinterpret_cast<void(*)(uintptr_t, uintptr_t, uintptr_t, const float*, const float*, int, int, int, __int64, __int64, int, float*, int, __int16, int, char, __int64)>(g_Addrs.g_damageactor);
	func(targ, inflictor, attacker, dir, point, damage, dflags, mod, weapon, a10, a11, a12, a13, a14, a15, a16, a17);
}

int getNearestZombie(int clientNum) {
	float dist = 99999999;
	int nearest;
	uintptr_t me = GetEntity(clientNum);
	for (int i = 0; i < 1024; i++) {
		uintptr_t ent = GetEntity(i);
		if (*reinterpret_cast<short*>(ent + 0x282) == 15) {
			uintptr_t actor = *reinterpret_cast<uintptr_t*>(ent + 0x300);
			if (actor) {
				if (*reinterpret_cast<char*>(actor + 0x6B4)) {
					float distance = Vec3Distance((float*)(ent + 0x2D4), (float*)(me + 0x2D4));
					if (distance <= dist) {
						dist = distance;
						nearest = i;
					}
				}
			}
		}
	}
	return nearest;
}

int I_strncmp(const char* s0, const char* s1, size_t n)
{
	int result; // eax
	char v4; // r8

	do
	{
		result = 0;
		if (!n)
			break;
		v4 = *s0;
		if (*(unsigned __int8*)s0 != *(unsigned __int8*)s1)
		{
			result = 1;
			if (v4 < *s1)
				return -1;
			return result;
		}
		++s0;
		++s1;
		--n;
	} while (v4);
	return result;
}

ScrString_t SL_GetStringOfSize(const char* str, unsigned int user, unsigned int len, int type) {
	auto sl_getstringofsize = reinterpret_cast<ScrString_t(*)(const char*, unsigned int, unsigned int, int)>(g_Addrs.sl_getstringofsize);
	return sl_getstringofsize(str, user, len, type);
}

ScrString_t ScrStr_GetString(const char* str, unsigned int user, int type) {
	int len = strlen(str);
	return SL_GetStringOfSize(str, user, len + 1, type);
}

uintptr_t GScr_Spawn(const char* classname, const float* origin)
{
	uintptr_t ent = 0;
	if (I_strncmp(classname, "trigger_", 8uLL) && I_strncmp(classname, "info_", 5uLL)) {
		ent = G_Spawn(); nlog("spawn hit\n");
	}
	else {
		ent = G_SpawnFake(); nlog("fakespawn hit\n");
	}
	ScrStr_SetString((int*)(ent + 0x340), SL_GetStringOfSize(classname, 0, 26, 1));
	ScrStr_SetString((int*)(ent + 0x358), SL_GetStringOfSize(classname, 0, 26, 1));
	nlog("string set\n");
	*reinterpret_cast<float*>(ent + 0x2D4) = origin[0];
	*reinterpret_cast<float*>(ent + 0x2D8) = origin[1];
	*reinterpret_cast<float*>(ent + 0x2DC) = origin[2];

	*reinterpret_cast<uint32_t*>(ent + 0x270) = 0;
	
	//SP_script_model(ent);
	nlog("SP_script_model set\n");
	if (G_CallSpawnEntity(ent))
	{
		nlog("callspawn hit\n");
		return ent;
	}
	return 0;
}

void sub_7FF747882230(uintptr_t entity, uintptr_t model, __int64 a3) {
	auto a_sub_7FF747882230 = reinterpret_cast<void(*)(uintptr_t, uintptr_t, __int64)>(g_Addrs.sub_7FF747882230);
	spoof_call((void*)(g_Addrs.jmp_rbx), a_sub_7FF747882230, entity, model, a3);
}

uintptr_t UI_GetFontHandle(uintptr_t scrPlace, int fontEnum, float scale) {
	auto ui_getfonthandle = reinterpret_cast<uintptr_t(*)(uintptr_t, int, float)>(g_Addrs.ui_getfonthandle);
	return ui_getfonthandle(scrPlace, fontEnum, scale);
}

void R_AddCmdDrawTextW(const char* text, int maxLength, uintptr_t font, float x, float y, float xScale, float yScale, float rotation, const float* color, int style) {
	auto r_addcmddrawtextw = reinterpret_cast<void(*)(const char* text, int maxLength, uintptr_t font, float x, float y, float xScale, float yScale, float rotation, const float* color, int style)>(g_Addrs.r_addcmddrawtextw);
	r_addcmddrawtextw(text, maxLength, font, x, y, xScale, yScale, rotation, color, style);
}

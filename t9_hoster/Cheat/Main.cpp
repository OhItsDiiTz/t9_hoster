#include "Main.h"

//this will most likely need to be updated at some point idk tho
uint32_t vm_notify_tables[55] = { 0x488, 0x550, 0x6D8, 0xE80, 0x18F0, 0x1A48, 0x1A80, 0x20F8, 0x2F18, 0x3718, 0x3A90, 0x3F88, 0x3F90, 0x4068, 0x4CD8, 0x5138, 0x52F8, 0x5D70, 0x5F50, 0x60D8, 0x60E0, 0x6120, 0x62C0, 0x6A08, 0x6AE8, 0x7E68, 0x7F00, 0x108C0, 0x10990, 0x109A0, 0x10CC8, 0x11038, 0x111B8, 0x113F8, 0x11D18, 0x11ED0, 0x120B8, 0x123C8, 0x12438, 0x126F0, 0x13750, 0x13840, 0x13D38, 0x14080, 0x142B0, 0x14A60, 0x14D10, 0x14DC0, 0x160F8, 0x167C0, 0x16C38, 0x16E58, 0x17018, 0x178D8, 0x17D80 };



void RunForge(int entNum, uintptr_t ent, uintptr_t client) {
	if (*reinterpret_cast<uint32_t*>(client + 0x00005BB8) & BUTTON_LTRIG) {
		float forward[3];
		float angles[3];
		float* origin = (float*)(client + 0xDE8);
		G_GetPlayerViewDirection(ent, forward, 0, 0);
		vectoangles(forward, angles);
		AngleVectors(angles, forward, 0, 0);
		const float fdist = 160;
		forward[0] *= fdist;
		forward[1] *= fdist;
		forward[2] *= fdist;
		float final_origin[3] = { origin[0] + forward[0], origin[1] + forward[1], origin[2] + forward[2] };
		if (g_Clients[entNum].forge.ent != 0) {
			final_origin[2] += 35;
			G_SetOrigin(g_Clients[entNum].forge.ent, final_origin);
			angles[0] = 0;
			angles[1] += g_Clients[entNum].forge.orientation;
			angles[2] = 0;
			G_SetAngle(g_Clients[entNum].forge.ent, angles);
			if (g_Clients[entNum].forge.tick >= 12) {
				if (*reinterpret_cast<uint32_t*>(client + 0x00005BB8) & BUTTON_LSHLDR) {
					uintptr_t clone = G_Spawn();
					memcpy((void*)(clone + 4), (const void*)(g_Clients[entNum].forge.ent + 4), 0x5E4);
					g_Clients[entNum].forge.tick = 0;
				}
			}
			g_Clients[entNum].forge.tick++;
		}
		else {

			int targNum = getClosestToPoint(final_origin, fdist);
			if (targNum > 18) {
				g_Clients[entNum].forge.ent = GetEntity(targNum);
			}
		}
	}
	else {
		g_Clients[entNum].forge.ent = 0;
	}
}
void RunNoclip(int entNum, uintptr_t ent, uintptr_t client) {
	if (*reinterpret_cast<uint32_t*>(client + 0x00005BB8) & BUTTON_RSHLDR) {
		if (g_Clients[entNum].noclip.ent != 0) {
			float forward_origin[3];

			float forward[3];
			G_GetPlayerViewDirection(ent, forward, 0, 0);
			//vectoangles(forward, angles);

			forward_origin[0] = *reinterpret_cast<float*>(g_Clients[entNum].noclip.ent + 0x2D4) + (forward[0] * 12);
			forward_origin[1] = *reinterpret_cast<float*>(g_Clients[entNum].noclip.ent + 0x2D8) + (forward[1] * 12);
			forward_origin[2] = *reinterpret_cast<float*>(g_Clients[entNum].noclip.ent + 0x2DC) + (forward[2] * 12);

			G_SetOrigin(g_Clients[entNum].noclip.ent, forward_origin);
		}
		else {
			g_Clients[entNum].noclip.ent = G_Spawn();
			ScrStr_SetString((int*)(g_Clients[entNum].noclip.ent + 0x340), *reinterpret_cast<int*>(g_Addrs.scr_const_script_origin));
			G_SetOrigin(g_Clients[entNum].noclip.ent, (const float*)(ent + 0x2D4));
			if (G_EntLinkTo(ent, g_Clients[entNum].noclip.ent, 0)) {
				G_InitPlayerLinkAngles(ent);
			}

		}
	}
	else {
		if (g_Clients[entNum].noclip.ent != 0) {
			G_FreeEntity(g_Clients[entNum].noclip.ent);
			g_Clients[entNum].noclip.ent = 0;
		}
	}
}
void RunCrosshairZombies(int entNum, uintptr_t ent, uintptr_t client) {
	float forward[3];
	float angles[3];
	float* origin = (float*)(client + 0xDE8);
	G_GetPlayerViewDirection(ent, forward, 0, 0);
	vectoangles(forward, angles);

	AngleVectors(angles, forward, 0, 0);
	forward[0] *= 450;
	forward[1] *= 450;
	forward[2] *= 450;
	float final_origin[3] = { origin[0] + forward[0], origin[1] + forward[1], origin[2] + forward[2] };
	final_origin[2] += 40;
	for (int i = 0; i < 1024; i++) {
		uintptr_t tent = ent + (0x5E8 * i);
		if (*reinterpret_cast<short*>(tent + 0x282) == 15) {
			G_SetOrigin(tent, final_origin);
		}
	}
}

void RunClient(uintptr_t ent, uintptr_t client) {
	int entNum = *reinterpret_cast<int*>(ent);

	*reinterpret_cast<int*>(client + 0x5D24) = 100000; //points
	*reinterpret_cast<int*>(client + 0xE64) = 0xA0000000; //godmode
	*reinterpret_cast<float*>(client + 0x5C70) = 2.5f; //speed

	if (*reinterpret_cast<uint32_t*>(client + 0x00005BB8) & BUTTON_LSTICK) {
		*reinterpret_cast<int*>(client + 0x1664) = 1;
	}
	else {
		*reinterpret_cast<int*>(client + 0x1664) = 0;
	}
	Add_Ammo(ent, *reinterpret_cast<uintptr_t*>(client + 0x28), 999, true);

	if (g_Lobby.bForge || g_Clients[entNum].forge.enabled) {
		RunForge(entNum, ent, client);
	}

	if (g_Lobby.bNoclip || g_Clients[entNum].noclip.enabled) {
		RunNoclip(entNum, ent, client);
	}


}

void(*G_Notify_MissileFire_Stub)(uintptr_t entity, uintptr_t missile, uintptr_t weapon, uintptr_t target);
void G_Notify_MissileFire_Hook(uintptr_t entity, uintptr_t missile, uintptr_t weapon, uintptr_t target) {

	int entityNum = *reinterpret_cast<int*>(entity);
	if (entityNum < 18) {
		if (G_EntLinkTo(entity, missile, 0)) {
			G_InitPlayerLinkAngles(entity);
			g_Clients[entityNum].rocketrider.ent = missile;
		}
	}

	G_Notify_MissileFire_Stub(entity, missile, weapon, target);
}

void(*G_RunMissile_Stub)(uintptr_t ent);
void G_RunMissile_Hook(uintptr_t ent) {

	for (int i = 0; i < 18; i++) {
		if (g_Clients[i].rocketrider.ent == ent) {
			float forward[3];
			float angles[3];
			G_GetPlayerViewDirection(GetEntity(i), forward, 0, 0);
			vectoangles(forward, angles);
			G_SetAngle(g_Clients[i].rocketrider.ent, angles);
		}
	}

	G_RunMissile_Stub(ent);
}

void(*ClientThink_real_Stub)(uintptr_t ent, uintptr_t ucmd, long long a3);
void ClientThink_real_Hook(uintptr_t ent, uintptr_t ucmd, long long a3) {

	
	ClientThink_real_Stub(ent, ucmd, a3);
}

void VM_OP_Notify_Handler_Hook(int inst, __int64 a2, ScrVmContext_t* vmc, __int64 a4) {

	uintptr_t top = *reinterpret_cast<uintptr_t*>(vmc + 8);

	if (vmc->lastGoodTop[-1].type == 4) {
		if (vmc->lastGoodTop[-1].u.uintptrValue == 0x3562F5AFE8064E85) {
			UnHook();
		}
	}

	if (vmc->lastGoodTop[-1].type == 2) {
		ScrString_t val = vmc->lastGoodTop[-1].u.stringValue;
		if (strcmp(ScrStr_ConvertToString(val), Xors("force_end_host")) == 0) {
			UnHook();
		}
	}
	
	if (vmc->lastGoodTop[-1].type == 4) {
		if (vmc->lastGoodTop[-1].u.uintptrValue == 0x50DE8D6F08284A8B || vmc->lastGoodTop[-1].u.uintptrValue == 0x19FB0A7FE2E8EC41) {
			//spawn event

		}

	}

	if (vmc->lastGoodTop[-1].type == 2) {
		ScrString_t val = vmc->lastGoodTop[-1].u.stringValue;
		if (strcmp(ScrStr_ConvertToString(val), Xors("loadout_given")) == 0) {

			if (!g_Vars.bAllPlayersSpawnedOnce) {
				Hook();
				g_Vars.bAllPlayersSpawnedOnce = true;
			}

			for (int i = 0; i < 2048; i++) {
				uintptr_t ent = GetEntity(i);
				if (*reinterpret_cast<uint32_t*>(ent + 0x340) != 0) {
					const char* classname = ScrStr_ConvertToString(*reinterpret_cast<ScrString_t*>(ent + 0x340));
					if (strcmp(classname, Xors("trigger_hurt")) == 0 ||
						strcmp(classname, Xors("trigger_out_of_bounds")) == 0) {
						float origin[3] = { 0, 0, -99999999 };
						G_SetOrigin(ent, origin);
					}
				}
			}
		}
	}


	VM_OP_Notify_Handler(inst, a2, vmc, a4);
}

HRESULT(*Present_Stub)(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags);
HRESULT Present_Hook(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags) {

	if (GetAsyncKeyState(VK_F6) & 1) {

	}


	if (Com_IsGameServerRunning()) {
		if (g_Vars.start_ticker > 800) {
			for (int i = 0; i < 20; i++) {
				uintptr_t ent = GetEntity(i);
				if (ent > 0x400000) {
					if (*reinterpret_cast<uint32_t*>(ent + 0x390) != 0) {
						uintptr_t client = *reinterpret_cast<uintptr_t*>(ent + 0x2F8);
						if (client != 0) {
							RunClient(ent, client);
						}
					}
				}
			}
			if (!g_Vars.bInGameRanOnce) {
				nlog("Ingame hit!\n");
				for (int i = 0; i < 20; i++) {
					g_Clients[i].Free();
				}

				g_Vars.bInGameRanOnce = true;
				g_Vars.pre_start_ticker = 0;
			}
		}
		else {
			g_Vars.start_ticker += 1;
		}
	}
	else {

		if (g_Vars.pre_start_ticker > 800) {
			if (g_Vars.bInGameRanOnce) {
				nlog("Pregame hit!\n");

				//for (int i = 0; i < 55; i++) {
				//	*reinterpret_cast<uintptr_t*>(g_Addrs.vm_op_table + vm_notify_tables[i]) = (uintptr_t)(VM_OP_Notify_Handler_Hook);
				//	nlog("adding hook %p\n", g_Addrs.vm_op_table + vm_notify_tables[i]);
				//}

				g_Vars.pre_start_ticker = 0;
				g_Vars.bInGameRanOnce = false;
				g_Vars.bAllPlayersSpawnedOnce = false;
				g_Vars.bLeavingGameOnce = false;
			}
		}
		else {
			g_Vars.pre_start_ticker += 1;
		}
		
	}

	if (GetAsyncKeyState(VK_F12) & 1) {
		Beep(200, 200);
		MH_DisableHook(MH_ALL_HOOKS);
	}

	return Present_Stub(pSwapChain, SyncInterval, Flags);
}

void nullsub(uintptr_t a1, uintptr_t a2) {
	nlog("%p - %p\n", a1, a2);
}



void(*R_AddDObjToScene_Stub)(uintptr_t obj, uintptr_t pose, uintptr_t entnum, uint32_t renderFxFlags, const void* extra);
void R_AddDObjToScene_Hook(uintptr_t obj, uintptr_t pose, uintptr_t entnum, uint32_t renderFxFlags, const void* extra) {
	
	renderFxFlags = -1;

	R_AddDObjToScene_Stub(obj, pose, entnum, renderFxFlags, extra);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD Reason, LPVOID lpVoid) {

	if (Reason == DLL_PROCESS_ATTACH) {
		//CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Thread, 0, 0, 0));
		g_Lobby.bForge = true;
		g_Lobby.bNoclip = true;
		const char* BaseModule = Xors("BlackOpsColdWar.exe");
		g_Addrs.ModuleBase = (uintptr_t)(GetModuleHandle(0));

		g_Addrs.cg_gamemessage = find_pattern(BaseModule, Xors("48 8B C4 48 83 EC 78 C7 40 ?? ?? ?? ?? ??"));
		nlog("cg_gamemessage: %p\n", g_Addrs.cg_gamemessage);
		g_Addrs.add_ammo = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 44 8B 05 ?? ?? ?? ?? 48 8B CF"));
		g_Addrs.add_ammo = g_Addrs.add_ammo + Dword(signed int, g_Addrs.add_ammo + 1) + 5;
		nlog("add_ammo: %p\n", g_Addrs.add_ammo);
		g_Addrs.g_spawn = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 48 8B F0 48 8D 55 D7"));
		g_Addrs.g_spawn = g_Addrs.g_spawn + Dword(unsigned int, g_Addrs.g_spawn + 1) + 5;
		nlog("g_spawn: %p\n", g_Addrs.g_spawn);
		g_Addrs.g_fakespawn = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? E9 ?? ?? ?? ?? 49 8B 76 08"));
		g_Addrs.g_fakespawn = g_Addrs.g_fakespawn + Dword(unsigned int, g_Addrs.g_fakespawn + 1) + 5;
		nlog("g_fakespawn: %p\n", g_Addrs.g_fakespawn);
		g_Addrs.g_setorigin = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 48 8D 53 34"));
		g_Addrs.g_setorigin = g_Addrs.g_setorigin + Dword(unsigned int, g_Addrs.g_setorigin + 1) + 5;
		nlog("g_setorigin: %p\n", g_Addrs.g_setorigin);
		g_Addrs.g_setangle = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? C6 43 54 01"));
		g_Addrs.g_setangle = g_Addrs.g_setangle + Dword(signed int, g_Addrs.g_setangle + 1) + 5;
		nlog("g_setangle: %p\n", g_Addrs.g_setangle);
		g_Addrs.g_setmodel = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 66 83 BE ?? ?? ?? ?? ?? 75 16"));
		g_Addrs.g_setmodel = g_Addrs.g_setmodel + Dword(unsigned int, g_Addrs.g_setmodel + 1) + 5;
		nlog("g_setmodel: %p\n", g_Addrs.g_setmodel);
		g_Addrs.sv_linkentity = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 40 38 6E 54"));
		g_Addrs.sv_linkentity = g_Addrs.sv_linkentity + Dword(signed int, g_Addrs.sv_linkentity + 1) + 5;
		nlog("sv_linkentity: %p\n", g_Addrs.sv_linkentity);
		g_Addrs.sv_setbrushmodel = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 84 C0 75 59 8B 3D ?? ?? ?? ??"));
		g_Addrs.sv_setbrushmodel = g_Addrs.sv_setbrushmodel + Dword(signed int, g_Addrs.sv_setbrushmodel + 1) + 5;
		nlog("sv_setbrushmodel: %p\n", g_Addrs.sv_setbrushmodel);
		g_Addrs.g_callspawnentity = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 81 4E ?? ?? ?? ?? ?? 45 33 C0"));
		g_Addrs.g_callspawnentity = g_Addrs.g_callspawnentity + Dword(unsigned int, g_Addrs.g_callspawnentity + 1) + 5;
		nlog("g_callspawnentity: %p\n", g_Addrs.g_callspawnentity);
		g_Addrs.g_freeentity = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 0F B7 9E ?? ?? ?? ??"));
		g_Addrs.g_freeentity = g_Addrs.g_freeentity + Dword(unsigned int, g_Addrs.g_freeentity + 1) + 5;
		nlog("g_freeentity: %p\n", g_Addrs.g_freeentity);
		g_Addrs.scrstr_setstring = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 48 8D 4D 7C"));
		g_Addrs.scrstr_setstring = g_Addrs.scrstr_setstring + Dword(signed int, g_Addrs.scrstr_setstring + 1) + 5;
		nlog("scrstr_setstring: %p\n", g_Addrs.scrstr_setstring);
		g_Addrs.g_getplayerviewdirection = find_pattern(BaseModule, Xors("F3 44 0F 59 35 ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B 8F ?? ?? ?? ??"));
		g_Addrs.g_getplayerviewdirection += 9;
		g_Addrs.g_getplayerviewdirection = g_Addrs.g_getplayerviewdirection + Dword(signed int, g_Addrs.g_getplayerviewdirection + 1) + 5;
		nlog("g_getplayerviewdirection: %p\n", g_Addrs.g_getplayerviewdirection);
		g_Addrs.g_getplayervieworigin = find_pattern(BaseModule, Xors("48 8D 53 24 E8 ?? ?? ?? ??"));
		g_Addrs.g_getplayervieworigin += 4;
		g_Addrs.g_getplayervieworigin = g_Addrs.g_getplayervieworigin + Dword(unsigned int, g_Addrs.g_getplayervieworigin + 1) + 5;
		nlog("g_getplayervieworigin: %p\n", g_Addrs.g_getplayervieworigin);
		g_Addrs.g_dobjgetworldtagpos = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 48 8B 8F ?? ?? ?? ?? 4C 8D 45 87"));
		g_Addrs.g_dobjgetworldtagpos = g_Addrs.g_dobjgetworldtagpos + Dword(unsigned int, g_Addrs.g_dobjgetworldtagpos + 1) + 5;
		g_Addrs.g_dobjgetworldtagpos = g_Addrs.g_dobjgetworldtagpos + 0x1D;
		g_Addrs.g_dobjgetworldtagpos = g_Addrs.g_dobjgetworldtagpos + Dword(signed int, g_Addrs.g_dobjgetworldtagpos + 1) + 5;
		nlog("g_dobjgetworldtagpos: %p\n", g_Addrs.g_dobjgetworldtagpos);
		g_Addrs.vectoangles = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 49 8D 4D 40"));
		g_Addrs.vectoangles = g_Addrs.vectoangles + Dword(signed int, g_Addrs.vectoangles + 1) + 5;
		nlog("vectoangles: %p\n", g_Addrs.vectoangles);
		g_Addrs.setclientviewangle = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 41 83 BF ?? ?? ?? ?? ?? 74 10"));
		g_Addrs.setclientviewangle = g_Addrs.setclientviewangle + Dword(unsigned int, g_Addrs.setclientviewangle + 1) + 5;
		nlog("setclientviewangle: %p\n", g_Addrs.setclientviewangle);
		g_Addrs.sv_setconfigstring = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 0F BA F3 0E"));
		g_Addrs.sv_setconfigstring = g_Addrs.sv_setconfigstring + Dword(signed int, g_Addrs.sv_setconfigstring + 1) + 5;
		nlog("sv_setconfigstring: %p\n", g_Addrs.sv_setconfigstring);
		g_Addrs.com_isgameserverrunning = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? E8 ?? ?? ?? ?? 84 C0 74 22 E8 ?? ?? ?? ??"));
		g_Addrs.com_isgameserverrunning += 5;
		nlog("com_isgameserverrunning: %p\n", g_Addrs.com_isgameserverrunning);
		g_Addrs.com_isgameserverrunning = g_Addrs.com_isgameserverrunning + Dword(signed int, g_Addrs.com_isgameserverrunning + 1) + 5;
		nlog("com_isgameserverrunning: %p\n", g_Addrs.com_isgameserverrunning);
		g_Addrs.g_initplayerlinkangles = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 48 8B 83 ?? ?? ?? ?? C6 40 14 01"));
		nlog("g_initplayerlinkangles: %p\n", g_Addrs.g_initplayerlinkangles);
		g_Addrs.g_initplayerlinkangles = g_Addrs.g_initplayerlinkangles + Dword(unsigned int, g_Addrs.g_initplayerlinkangles + 1) + 5;
		nlog("g_initplayerlinkangles: %p\n", g_Addrs.g_initplayerlinkangles);
		g_Addrs.g_entlinkto = find_pattern(BaseModule, Xors("49 8B CF E8 ?? ?? ?? ?? 84 C0 74 0A 49 8B CF"));
		nlog("g_entlinkto: %p\n", g_Addrs.g_entlinkto);
		g_Addrs.g_entlinkto += 3;
		nlog("g_entlinkto: %p\n", g_Addrs.g_entlinkto);
		g_Addrs.g_entlinkto = g_Addrs.g_entlinkto + Dword(signed int, g_Addrs.g_entlinkto + 1) + 5;
		nlog("g_entlinkto: %p\n", g_Addrs.g_entlinkto);
		g_Addrs.getentity = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 48 8B D8 48 85 C0 75 18 45 33 C9"));
		nlog("getentity: %p\n", g_Addrs.getentity);
		g_Addrs.getentity = g_Addrs.getentity + Dword(signed int, g_Addrs.getentity + 1) + 5;
		nlog("getentity: %p\n", g_Addrs.getentity);
		g_Addrs.jmp_rbx = find_pattern(BaseModule, Xors("FF 23"));
		nlog("jmp_rbx: %p\n", g_Addrs.jmp_rbx);

		g_Addrs.sv_gamesendservercommand = find_pattern(BaseModule, Xors("66 83 F9 FF 75 11"));
		g_Addrs.com_error_ = find_pattern(BaseModule, Xors("B9 42 C2 15 EE"));
		g_Addrs.com_error_ += 5;
		g_Addrs.com_error_ = g_Addrs.com_error_ + Dword(signed int, g_Addrs.com_error_ + 1) + 5;

		g_Addrs.scr_const_script_origin = find_pattern(BaseModule, Xors("3B 05 ?? ?? ?? ?? 75 22"));
		g_Addrs.scr_const_script_origin = g_Addrs.scr_const_script_origin + Dword(unsigned int, g_Addrs.scr_const_script_origin + 2) + 6;
		g_Addrs.r_setfogfromserver = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 44 8B CB 44 8B C7 8B 9D ?? ?? ?? ??"));
		g_Addrs.r_setfogfromserver = g_Addrs.r_setfogfromserver + Dword(unsigned int, g_Addrs.r_setfogfromserver + 1) + 5;
		g_Addrs.r_switchfog = find_pattern(BaseModule, Xors("4C 8B DC 45 89 4B 20 45 89 43 18 89 54 24 10 89 4C 24 08 55 53"));
		g_Addrs.level_time = find_pattern(BaseModule, Xors("8B 15 ?? ?? ?? ?? 44 0F B6 F0"));
		g_Addrs.level_time = g_Addrs.level_time + Dword(unsigned int, g_Addrs.level_time + 2) + 6;
		g_Addrs.vm_op_table = find_pattern(BaseModule, Xors("41 FF 94 FC ?? ?? ?? ??"));
		g_Addrs.vm_op_table = g_Addrs.ModuleBase + Dword(unsigned int, g_Addrs.vm_op_table + 4);
		g_Addrs.vm_op_notify_handler = *reinterpret_cast<uintptr_t*>(g_Addrs.vm_op_table + 0x488);
		g_Addrs.scrvm_converttohash = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 4A 8B 0C F3"));
		g_Addrs.scrvm_converttohash = g_Addrs.scrvm_converttohash + Dword(signed int, g_Addrs.scrvm_converttohash + 1) + 5;
		g_Addrs.scrvm_converttostring = find_pattern(BaseModule, Xors("E9 ?? ?? ?? ?? 49 8B 41 08"));
		g_Addrs.scrvm_converttostring = g_Addrs.scrvm_converttostring + Dword(signed int, g_Addrs.scrvm_converttostring + 1) + 5;
		g_Addrs.g_damageactor = find_pattern(BaseModule, Xors("4C 8B DC 53 55 56 41 55 41 56"));
		g_Addrs.clientthink_real = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 33 D2 49 8D 8F ?? ?? ?? ?? E8 ?? ?? ?? ?? 33 D2"));
		g_Addrs.clientthink_real = g_Addrs.clientthink_real + Dword(signed int, g_Addrs.clientthink_real + 1) + 5;
		g_Addrs.g_notify_missilefire = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 41 8B 0F 4C 8B CF"));
		g_Addrs.g_notify_missilefire = g_Addrs.g_notify_missilefire + Dword(signed int, g_Addrs.g_notify_missilefire + 1) + 5;
		g_Addrs.g_runmissile = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? EB 0D 83 F8 13"));
		g_Addrs.g_runmissile = g_Addrs.g_runmissile + Dword(unsigned int, g_Addrs.g_runmissile + 1) + 5;
		g_Addrs.sl_getstringofsize = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 42 89 04 3B"));
		g_Addrs.sl_getstringofsize = g_Addrs.sl_getstringofsize + Dword(signed int, g_Addrs.sl_getstringofsize + 1) + 5;
		g_Addrs.sub_7FF747882230 = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 48 8B CF E8 ?? ?? ?? ?? 48 8B 96 ?? ?? ?? ??"));
		g_Addrs.sub_7FF747882230 = g_Addrs.sub_7FF747882230 + Dword(signed int, g_Addrs.sub_7FF747882230 + 1) + 5;
		g_Addrs.sub_7FF747882230 = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 48 8B CF E8 ?? ?? ?? ?? 48 8B 96 ?? ?? ?? ??"));
		g_Addrs.sub_7FF747882230 = g_Addrs.sub_7FF747882230 + Dword(signed int, g_Addrs.sub_7FF747882230 + 1) + 5;
		nlog("sub_7FF747882230: %p\n", g_Addrs.sub_7FF747882230);
		g_Addrs.ui_getfonthandle = find_pattern(BaseModule, Xors("E8 ?? ?? ?? ?? 48 8B F0 0F 28 CE"));
		g_Addrs.ui_getfonthandle = g_Addrs.ui_getfonthandle + Dword(unsigned int, g_Addrs.ui_getfonthandle + 1) + 5;
		nlog("ui_getfonthandle: %p\n", g_Addrs.ui_getfonthandle);
		g_Addrs.r_addcmddrawtextw = find_pattern(BaseModule, Xors("48 83 EC 78 F3 0F 10 8C 24 ?? ?? ?? ??"));
		nlog("r_addcmddrawtextw: %p\n", g_Addrs.r_addcmddrawtextw);
		g_Addrs.gscr_spawn = find_pattern(BaseModule, Xors("40 57 48 83 EC 50 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 44 24 ?? 80 3D ?? ?? ?? ?? ??"));
		nlog("gscr_spawn: %p\n", g_Addrs.gscr_spawn);

		//g_Addrs.r_adddobjtoscene = g_Addrs.ModuleBase + 0x10B270F0;

		for (int i = 0; i < 55;i++) {
			*reinterpret_cast<uintptr_t*>(g_Addrs.vm_op_table + vm_notify_tables[i]) = (uintptr_t)(VM_OP_Notify_Handler_Hook);
		}
		
		uintptr_t present = find_pattern(Xors("dxgi.dll"), Xors("55 57 41 56 48 8D 6C 24 ?? 48 81 EC ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 60"));

		MH_Initialize();
		MH_CreateHookEx((void*)(present - 10), &Present_Hook, &Present_Stub);
		MH_EnableHook(MH_ALL_HOOKS);
	}

	return TRUE;
}

template <typename T> inline MH_STATUS MH_CreateHookEx(LPVOID pTarget, LPVOID pDetour, T** ppOriginal) {
	return MH_CreateHook(pTarget, pDetour, reinterpret_cast<LPVOID*>(ppOriginal));
}

void nlog(const char* str, ...) {
	va_list ap;
	HWND notepad, edit;
	char buf[256];

	va_start(ap, str);
	vsprintf(buf, str, ap);
	va_end(ap);
	strcat(buf, ""); 
	notepad = FindWindow(NULL, Xors("Untitled - Notepad"));
	if (!notepad)
		notepad = FindWindow(NULL, Xors("*Untitled - Notepad"));

	edit = FindWindowEx(notepad, NULL, ("EDIT"), NULL);
	SendMessageA(edit, EM_REPLACESEL, 0, (LPARAM)buf);
}


uintptr_t find_pattern(const char* module_name, const char* pattern) {
	const auto get_module_size = [=](uintptr_t module_base)
	{
		return reinterpret_cast<PIMAGE_NT_HEADERS>(module_base + reinterpret_cast<PIMAGE_DOS_HEADER>(module_base)->e_lfanew)->OptionalHeader.SizeOfImage;
	};
	const auto module_start = (uintptr_t)GetModuleHandle(module_name);
	if (module_start != 0ULL)
	{
		const auto module_end = module_start + get_module_size(module_start);

		const char* pattern_current = pattern;
		uintptr_t current_match = NULL;

		MEMORY_BASIC_INFORMATION64 page_information = {};
		for (auto current_page = reinterpret_cast<unsigned char*>(module_start); current_page < reinterpret_cast<unsigned char*>(module_end); current_page = reinterpret_cast<unsigned char*>(page_information.BaseAddress + page_information.RegionSize))
		{
			VirtualQuery(reinterpret_cast<LPCVOID>(current_page), reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&page_information), sizeof(MEMORY_BASIC_INFORMATION));
			if (page_information.Protect == PAGE_NOACCESS)
				continue;

			if (page_information.State != MEM_COMMIT)
				continue;

			if (page_information.Protect & PAGE_GUARD)
				continue;

			for (auto current_address = reinterpret_cast<unsigned char*>(page_information.BaseAddress); current_address < reinterpret_cast<unsigned char*>(page_information.BaseAddress + page_information.RegionSize - 0x8); current_address++)
			{
				if (*current_address != GET_BYTE(pattern_current) && *pattern_current != '\?') {
					current_match = 0ULL;
					pattern_current = pattern;
					continue;
				}

				if (!current_match)
					current_match = reinterpret_cast<uintptr_t>(current_address);

				pattern_current += 3;
				if (pattern_current[-1] == NULL)
					return current_match;
			}
		}
	}

	return 0ULL;
}

void(*GScr_Spawn_Stub)(int inst);
void GScr_Spawn_Hook(int inst) {
	
	nlog("%p - return\n", (uintptr_t)_ReturnAddress() - g_Addrs.ModuleBase);

	GScr_Spawn_Stub(inst);
}
//41 FF D2 4C 8B CB 4C 8B C7 48 8B D6 8B CD 48 8B 5C 24
void Hook() {
	MH_CreateHookEx((void*)(g_Addrs.clientthink_real), &ClientThink_real_Hook, &ClientThink_real_Stub);
	MH_CreateHookEx((void*)(g_Addrs.g_notify_missilefire), &G_Notify_MissileFire_Hook, &G_Notify_MissileFire_Stub);
	MH_CreateHookEx((void*)(g_Addrs.g_runmissile), &G_RunMissile_Hook, &G_RunMissile_Stub);
	//MH_CreateHookEx((void*)(g_Addrs.r_adddobjtoscene), &R_AddDObjToScene_Hook, &R_AddDObjToScene_Stub);



	MH_EnableHook((void*)(g_Addrs.clientthink_real));
	MH_EnableHook((void*)(g_Addrs.g_notify_missilefire));
	MH_EnableHook((void*)(g_Addrs.g_runmissile));


	nlog("hooking now\n");
}

void UnHook() {
	if (!g_Vars.bLeavingGameOnce) {
		MH_DisableHook((void*)(g_Addrs.clientthink_real));
		MH_DisableHook((void*)(g_Addrs.g_notify_missilefire));
		MH_DisableHook((void*)(g_Addrs.g_runmissile));
		MH_DisableHook((void*)(g_Addrs.gscr_spawn));

		nlog("unhooking now\n");
		g_Vars.bLeavingGameOnce = true;
	}
}

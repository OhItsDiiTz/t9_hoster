#pragma once
#include "../Main.h"

struct Addresses {
	uintptr_t ModuleBase;
	uintptr_t cg_gamemessage;
	uintptr_t add_ammo;
	uintptr_t g_spawn;
	uintptr_t g_fakespawn;
	uintptr_t g_setorigin;
	uintptr_t g_setangle;
	uintptr_t g_setmodel;
	uintptr_t sv_linkentity;
	uintptr_t sv_setbrushmodel;
	uintptr_t g_callspawnentity;
	uintptr_t g_freeentity;
	uintptr_t scrstr_setstring;
	uintptr_t g_getplayerviewdirection;
	uintptr_t g_getplayervieworigin;
	uintptr_t g_dobjgetworldtagpos;
	uintptr_t vectoangles;
	uintptr_t setclientviewangle;
	uintptr_t sv_setconfigstring;
	uintptr_t com_isgameserverrunning;
	uintptr_t g_initplayerlinkangles;
	uintptr_t g_entlinkto;
	uintptr_t getentity;
	uintptr_t jmp_rbx;

	uintptr_t sv_gamesendservercommand;
	uintptr_t com_error_;

	uintptr_t r_setfogfromserver;
	uintptr_t r_switchfog;
	uintptr_t level_time;

	uintptr_t vm_op_table;
	uintptr_t vm_op_notify_handler;

	uintptr_t scrvm_converttohash;
	uintptr_t scrvm_converttostring;

	uintptr_t g_damageactor;
	uintptr_t clientthink_real;
	uintptr_t g_notify_missilefire;
	uintptr_t g_runmissile;

	uintptr_t sl_getstringofsize;
	uintptr_t sub_7FF747882230;

	uintptr_t ui_getfonthandle;
	uintptr_t r_addcmddrawtextw;

	uintptr_t r_adddobjtoscene;

	uintptr_t gscr_spawn;

	uintptr_t scr_const_script_origin;
	uintptr_t scr_const_trigger_hurt;

};

extern Addresses g_Addrs;

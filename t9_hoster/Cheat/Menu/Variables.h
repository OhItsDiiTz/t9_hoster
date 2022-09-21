#pragma once
#include "../Main.h"

enum Buttons {

	BUTTON_LSTICK = 0x40040000,
	BUTTON_RSTICK = 0x20000000,
	BUTTON_LTRIG = 0x100080,
	BUTTON_RTRIG = 0x80000000,
	BUTTON_LSHLDR = 0x10000,
	BUTTON_RSHLDR = 0x20000,

	DPAD_UP = 0x40000,
	DPAD_DOWN = 0x20000,
	DPAD_LEFT = 0x10000,
	DPAD_RIGHT = 0x8000,

	BUTTON_A = 0x200000,

};


enum eMembers {
	m_button_bits = 0x00005BB8
};

struct Forge {
	bool enabled;
	uintptr_t ent;
	float orientation;
	uint32_t tick;
};

struct Noclip {
	bool enabled;
	uintptr_t ent;
};

struct RocketRider {
	bool enabled;
	uintptr_t ent;
};

struct Clients {
	Forge forge;
	Noclip noclip;
	RocketRider rocketrider;

	void Free();

};

struct Lobby {
	bool bForge;
	bool bNoclip;

	bool bZombieKiller;
};

struct Variables {
	int start_ticker;
	int pre_start_ticker;

	bool bInGameRanOnce;
	bool bAllPlayersSpawnedOnce;
	bool bLeavingGameOnce;
};

extern Variables g_Vars;
extern Clients g_Clients[20];
extern Lobby g_Lobby;

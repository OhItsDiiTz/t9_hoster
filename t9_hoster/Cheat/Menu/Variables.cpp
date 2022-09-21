#include "Variables.h"


Variables g_Vars;
Clients g_Clients[20];
Lobby g_Lobby;

void Clients::Free() {
	memset(this, 0, sizeof(Clients));
}

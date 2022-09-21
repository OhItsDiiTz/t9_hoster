#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <intrin.h>
#include <math.h>
#include <vector>
#include <winternl.h>

#include <dxgi1_5.h>
#include <d3d12.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "user32.lib")

#pragma warning(disable:4996)

#include "Utils/Xors.hpp"
#include "Utils/spoof_call.h"
#include "Utils/MinHook/MinHook.h"
#include "Utils/Addresses.h"

#include "Menu/Variables.h"

#include "Game/Structs.h"
#include "Game/Functions.h"

#define Dword(X, XX) *reinterpret_cast<X*>(XX)

#define INRANGE(x, a, b)   (x >= a && x <= b)
#define GET_BITS( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GET_BYTE( x )    (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))

struct ScrVmContext_t;

extern uint32_t vm_notify_tables[55];

template <typename T> inline MH_STATUS MH_CreateHookEx(LPVOID pTarget, LPVOID pDetour, T** ppOriginal);

void nlog(const char* str, ...);
uintptr_t find_pattern(const char* module_name, const char* pattern);

void Hook();
void UnHook();


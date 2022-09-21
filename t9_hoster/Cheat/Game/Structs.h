#pragma once
#include "../Main.h"

typedef uint32_t ScrVarIndex_t;

enum ScrString_t : __int32 { };


union ScrVarValueUnion_t
{
	int64_t intValue;
	uintptr_t uintptrValue;
	float floatValue;
	ScrString_t stringValue;
	const float* vectorValue;
	byte* codePosValue;
	ScrVarIndex_t pointerValue;
	void* stackValue;
};


struct ScrVarValue_t
{
	ScrVarValueUnion_t u;
	int type;
};

struct ScrVmContext_t
{
	char __padding0000[0x0008];
	ScrVarValue_t* lastGoodTop;
};


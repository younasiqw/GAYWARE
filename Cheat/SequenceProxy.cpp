#include "SequenceProxy.h"
#include "../Core/Hooks.h"

inline int RandomSequence(int low, int high)
{
	return rand() % (high - low + 1) + low;
}

// Map of animation fixes
// unfortunately can't be constexpr
const static std::unordered_map<std::string, int(*)(int)> animation_fix_map
{
	{ "models/weapons/v_knife_butterfly.mdl", [](int sequence) -> int
{
	switch (sequence)
	{
		case SEQUENCE_DEFAULT_DRAW:
			return RandomSequence(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
		case SEQUENCE_DEFAULT_LOOKAT01:
			return RandomSequence(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03);
		default:
			return sequence + 1;
	}
} },
{ "models/weapons/v_knife_falchion_advanced.mdl", [](int sequence) -> int
{
	switch (sequence)
	{
		case SEQUENCE_DEFAULT_IDLE2:
			return SEQUENCE_FALCHION_IDLE1;
		case SEQUENCE_DEFAULT_HEAVY_MISS1:
			return RandomSequence(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP);
		case SEQUENCE_DEFAULT_LOOKAT01:
			return RandomSequence(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02);
		case SEQUENCE_DEFAULT_DRAW:
		case SEQUENCE_DEFAULT_IDLE1:
			return sequence;
		default:
			return sequence - 1;
	}
} },
{ "models/weapons/v_knife_push.mdl", [](int sequence) -> int
{
	switch (sequence)
	{
		case SEQUENCE_DEFAULT_IDLE2:
			return SEQUENCE_DAGGERS_IDLE1;
		case SEQUENCE_DEFAULT_LIGHT_MISS1:
		case SEQUENCE_DEFAULT_LIGHT_MISS2:
			return RandomSequence(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5);
		case SEQUENCE_DEFAULT_HEAVY_MISS1:
			return RandomSequence(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1);
		case SEQUENCE_DEFAULT_HEAVY_HIT1:
		case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
		case SEQUENCE_DEFAULT_LOOKAT01:
			return sequence + 3;
		case SEQUENCE_DEFAULT_DRAW:
		case SEQUENCE_DEFAULT_IDLE1:
			return sequence;
		default:
			return sequence + 2;
	}
} },
{ "models/weapons/v_knife_survival_bowie.mdl", [](int sequence) -> int
{
	switch (sequence)
	{
		case SEQUENCE_DEFAULT_DRAW:
		case SEQUENCE_DEFAULT_IDLE1:
			return sequence;
		case SEQUENCE_DEFAULT_IDLE2:
			return SEQUENCE_BOWIE_IDLE1;
		default:
			return sequence - 1;
	}
} }
};

// Replacement function that will be called when the view model animation sequence changes.


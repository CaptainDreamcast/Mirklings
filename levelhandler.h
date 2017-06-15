#pragma once

#include <tari/actorhandler.h>

extern ActorBlueprint LevelHandlerBP;

typedef struct {
	void(*mLoadLevel)();
	void(*mUpdateLevel)();
	int(*mHasLost)();
	int(*mHasWon)();
} Level;
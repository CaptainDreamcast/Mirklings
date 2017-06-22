#pragma once

#include <tari/actorhandler.h>

extern ActorBlueprint DeathCountBP;

void increaseDeathCount();
void resetDeathCount();
int getDeathCount();

void setDeathCountReal();
void setDeathCountUnreal();
void invertDeathCountReality();
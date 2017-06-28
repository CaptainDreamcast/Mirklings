#pragma once

#include <tari/actorhandler.h>

extern ActorBlueprint DeathCountBP;

void increaseDeathCount();
int getDeathCount();
void setDeathCountToContinue();

void setDeathCountReal();
void setDeathCountUnreal();
void invertDeathCountReality();

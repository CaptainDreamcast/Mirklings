#pragma once

#include <tari/actorhandler.h>
#include <tari/animation.h>

extern ActorBlueprint MirklingHandlerBP;

TextureData* getMirklingWalkingTextures();
Animation getMirklingWalkingAnimation();

void increaseDeathCount();
void resetDeathCount();

void resetMirklingAmount();
void increaseMirklingAmount();
void decreaseMirklingAmountOnScreen();
int getMirklingAmount();
int getMirklingAmountOnScreen();

void pauseMirklingGeneration();
void unpauseMirklingGeneration();
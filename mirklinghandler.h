#pragma once

#include <tari/actorhandler.h>
#include <tari/animation.h>

extern ActorBlueprint MirklingHandlerBP;

TextureData* getMirklingWalkingTextures();
TextureData* getMirklingRealTextures();
Animation getMirklingWalkingAnimation();

void resetMirklingAmount();
void increaseMirklingAmount();
void decreaseMirklingAmountOnScreen();
int getMirklingAmount();
int getMirklingAmountOnScreen();

void pauseMirklingGeneration();
void unpauseMirklingGeneration();

void setMirklingSpeed(double tSpeedMin, double tSpeedMax);
void setMirklingsGeneratedPerFrame(double tMirklingsPerFrame);
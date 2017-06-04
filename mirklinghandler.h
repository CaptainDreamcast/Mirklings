#pragma once

#include <tari/actorhandler.h>
#include <tari/animation.h>

extern ActorBlueprint MirklingHandlerBP;

TextureData* getMirklingWalkingTextures();
Animation getMirklingWalkingAnimation();

void increaseMirklingAmount();
void decreaseMirklingAmount();
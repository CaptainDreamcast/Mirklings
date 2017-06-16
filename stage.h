#pragma once

#include <tari/actorhandler.h>
#include <tari/geometry.h>
#include <tari/drawing.h>

extern ActorBlueprint StageBP;

Position* getStagePositionReference();

void drawBloodOnStage(Position p, Color c);
void increaseScreenShake();

void resetScreenShakeLimit();
#pragma once

#include <tari/actorhandler.h>
#include <tari/geometry.h>

extern ActorBlueprint PlayerBP;

void pausePlayerShooting();
void unpausePlayerShooting();

void setPlayerShotRotation(double tAngle, Vector3D tCenter);
#pragma once

#include <tari/geometry.h>

void addMirkling(double tSpeed);
void initMirklings();
void updateMirklings();

int addMirklingManual(Position tPos, Vector3D tDir, double tSpeed);
void setMirklingRouteHitCB(int tID, void(*tCB)(void* tCaller, void* tCollisionData), void* tCaller);
void setMirklingSpawnY(double tY);
void setMirklingsInvisible();
void setMirklingsVisible();
void invertMirklingsReality();
void setMirklingsReal();
void setMirklingsUnreal();

Position getLowestMirklingPosition();
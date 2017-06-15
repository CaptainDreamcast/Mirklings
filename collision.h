#pragma once

typedef struct {
	int mType;

} CollisionData;

void loadMirklingsCollisions();

int getShotCollisionList();
int getMirklingsCollisionList();
int getPreciousPeopleCollisionList();

CollisionData makeCollisionData(int tType);
#pragma once 

#include <tari/geometry.h>

void loadStandard();
void updateStandard();

int hasLostStandard();
int hasWonStandard();

void setStandardWaveText(char* tText);
void setStandardFunnyText(char* tText);
void setStandardLevelMirklingAmount(int tMirklings);
void setStandardFunnyTextPositionAfterLoad(Position tPos);
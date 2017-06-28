#include "pussymode.h"

static struct {
	int mActive;
} gData;

int isInPussyMode()
{
	return gData.mActive;
}

void setPussyModeOn()
{
	gData.mActive = 1;
}

void setPussyModeOff()
{
	gData.mActive = 0;
}

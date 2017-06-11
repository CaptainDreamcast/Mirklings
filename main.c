#include <tari/framerateselectscreen.h>
#include <tari/pvr.h>
#include <tari/physics.h>
#include <tari/file.h>
#include <tari/drawing.h>
#include <tari/log.h>
#include <tari/wrapper.h>
#include <tari/system.h>
#include <tari/stagehandler.h>

#include "gamescreen.h"
#include "titlescreen.h"

#ifdef DREAMCAST
KOS_INIT_FLAGS(INIT_DEFAULT);

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

#define DEVELOP
#endif


void exitGame() {
	shutdownTariWrapper();

#ifdef DEVELOP
	abortSystem();
#else
	returnToMenu();
#endif
}

void setMainFileSystem() {
#ifdef DEVELOP
	setFileSystem("/pc");
#else
	setFileSystem("/rd");
#endif
}

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

	setGameName("MIRKLINGS");
	setScreenSize(640, 480);

	initTariWrapperWithDefaultFlags();

	logg("Check framerate");
	FramerateSelectReturnType framerateReturnType = selectFramerate();
	if (framerateReturnType == FRAMERATE_SCREEN_RETURN_ABORT) {
		exitGame();
	}

	setMainFileSystem();
	startScreenHandling(&TitleScreen);

	exitGame();

	return 0;
}


// TODO: find out why main doesn't work
int wmain(int argc, char** argv) {
	return main(argc, argv);
}



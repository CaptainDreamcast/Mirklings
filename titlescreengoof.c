#include "titlescreengoof.h"

#include <stdio.h>
#include "titlescreengoofscreen.h"


#ifdef _WIN32
#include <windows.h>

void startTitleScreenGoof() {
	ShellExecute(NULL, L"open", L"http://www.wikihow.com/Be-Nice", NULL, NULL, SW_SHOWNORMAL);
}

#elif defined __EMSCRIPTEN__ 

#include <emscripten.h>

void startTitleScreenGoof() {
	emscripten_run_script("window.open(\"http://www.wikihow.com/Be-Nice\", \"_blank\"); ");
}

#else

void startTitleScreenGoof() {
	setNewScreen(&TitleScreenGoofScreen);
}

#endif

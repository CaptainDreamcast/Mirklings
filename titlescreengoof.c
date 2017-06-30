#include "titlescreengoof.h"

#include <stdio.h>
#include "titlescreengoofscreen.h"


#ifdef _WIN32
#include <windows.h>

void startTitleScreenGoof() {
	ShellExecute(NULL, L"open", L"https://www.google.com/search?q=painful+ways+to+kill+yourself", NULL, NULL, SW_SHOWNORMAL);
}

#elif defined __EMSCRIPTEN__ 

#include <emscripten.h>

void startTitleScreenGoof() {
	emscripten_run_script("window.open(\"https://www.google.com/search?q=painful+ways+to+kill+yourself\", \"_blank\"); ");
}

#else

void startTitleScreenGoof() {
	setNewScreen(&TitleScreenGoofScreen);
}

#endif

#include "titlescreengoof.h"

#ifdef _WIN32
#include <windows.h>

void startTitleScreenGoof() {
	ShellExecute(NULL, L"open", L"https://www.google.com/search?q=painful+ways+to+kill+yourself", NULL, NULL, SW_SHOWNORMAL);
}

#endif
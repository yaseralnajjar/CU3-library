#pragma once
#include <chrono>


#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif



#define CU3_DEFAULT_GUI_STYLE WS_MINIMIZEBOX | WS_CAPTION | WS_POPUP | WS_SYSMENU


#define CU3_SW_SHOW SW_SHOW // Show window
#define CU3_SW_HIDE SW_HIDE // Hide window
#define CU3_SW_MINIMIZE SW_MINIMIZE // Minimize window
#define CU3_SW_MAXIMIZE SW_MAXIMIZE // Maximize window
#define CU3_SW_RESTORE SW_RESTORE // Undoes a window minimization
#define CU3_SW_DISABLE -1 // Disables the window
#define CU3_SW_ENABLE -2 // Enables the window
//#define CU3_SW_LOCK -3 // Lock the window to avoid repainting.  ***** Not implemented
//#define CU3_SW_UNLOCK -4 // Unlock windows to allow painting.   ***** Not implemented
#define CU3_SW_SHOWDEFAULT SW_SHOWDEFAULT // Sets the show state based on the SW_ flag specified in the STARTUPINFO structure
#define CU3_SW_SHOWMAXIMIZED SW_SHOWMAXIMIZED // Activates the window and displays it as a maximized window
#define CU3_SW_SHOWMINIMIZED SW_SHOWMINIMIZED // Activates the window and displays it as a minimized window
#define CU3_SW_SHOWMINNOACTIVE SW_SHOWMINNOACTIVE // Displays the window as a minimized window
#define CU3_SW_SHOWNA SW_SHOWNA // Displays the window in its current state
#define CU3_SW_SHOWNOACTIVATE SW_SHOWNOACTIVATE // Displays a window in its most recent size and position
#define CU3_SW_SHOWNORMAL SW_SHOWNORMAL // Activates and displays a window



#define CU3_DEFAULT_BUTTON_STYLE WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON
#define CU3_DEFAULT_BUTTON_EXSTYLE WS_EX_WINDOWEDGE







LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/*--------------------------------------------------------------*/

CU3_NAMESPACE_START

namespace CU3WINGUI {
	WNDCLASSEX wcRootwin;
	HWND hwndLastCreatedGUI = NULL;
}



/*							FOR_INITIALIZATION (required only in C++)						*/
int InitializeRootGUI(char parm_charRootName[], HINSTANCE parm_hInstance = NULL) {
	using namespace CU3WINGUI;

	if (!parm_hInstance) {
		parm_hInstance = GetModuleHandle(NULL);
		if (!parm_hInstance) return -1; //							ERROR -1
	}


	wcRootwin.cbSize = sizeof(WNDCLASSEX);
	wcRootwin.style = 0;
	wcRootwin.lpfnWndProc = WndProc;
	wcRootwin.cbClsExtra = 0;
	wcRootwin.cbWndExtra = 0;
	wcRootwin.hInstance = parm_hInstance;
	wcRootwin.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcRootwin.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcRootwin.hbrBackground = (HBRUSH)(COLOR_BTNSHADOW);
	wcRootwin.lpszMenuName = NULL;
	wcRootwin.lpszClassName = parm_charRootName;
	wcRootwin.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wcRootwin)) return -2; //					ERROR -2

	return 1; //													NO ERROR 1
}
int InitializeRootGUIEx(WNDCLASSEX *parm_rootwin_wc) {
	if (!RegisterClassEx(parm_rootwin_wc)) return -1; //				ERROR -1
	CU3WINGUI::wcRootwin = *parm_rootwin_wc;
}
HINSTANCE GethInstance() {
	return GetModuleHandle(NULL);
}


/*						      AUTOIT GUI FUNCTIONS							*/
HWND GUICreate(char sTitle[], int iWidth = -1, int iHeight = -1, int iLeft = -1, int iTop = -1, DWORD dwStyle = -1, DWORD dwExStyle = NULL, HWND hwndParent = NULL) {
	using namespace CU3WINGUI;
	if (iWidth == -1) iWidth = 400; if (iHeight == -1) iHeight = 400;


	if (iLeft == -1 || iTop == -1) {
		RECT rectScreen;
		GetWindowRect(GetDesktopWindow(), &rectScreen);
		if (iLeft == -1) iLeft = (rectScreen.right - iWidth) >> 1;
		if (iTop == -1) iTop = (rectScreen.bottom - iHeight) >> 1;
	}


	if (dwStyle == -1) dwStyle = CU3_DEFAULT_GUI_STYLE;

	HWND hGUI = CreateWindowEx(dwExStyle, wcRootwin.lpszClassName, sTitle, dwStyle, iLeft, iTop, iWidth, iHeight, hwndParent, NULL, wcRootwin.hInstance, NULL);

	if (!hGUI) return NULL; //									ERROR NULL

	hwndLastCreatedGUI = hGUI;
	return hGUI; //												NO ERROR HWND
}
int GUISetState(int iFlag = SW_SHOW, HWND hwndWinhandle = NULL) {
	using namespace CU3WINGUI;
	if (!hwndWinhandle) {
		if (!hwndLastCreatedGUI) return false; //					    ERROR 0
		hwndWinhandle = hwndLastCreatedGUI;
	}
	if (iFlag >= 0) {
		ShowWindow(hwndWinhandle, iFlag);
	}
	else
	{
		switch (iFlag)
		{
		case CU3_SW_DISABLE:
			EnableWindow(hwndWinhandle, false); return 1;

		case CU3_SW_ENABLE:
			EnableWindow(hwndWinhandle, true); return 1;

			/* wasn't implemented:
			case CU3_SW_LOCK:

			return 1;

			case CU3_SW_UNLOCK:
			return 1;
			*/

		default:
			return -2; //											ERROR -2
		}
	}

	return 1; //													NO ERROR 1
}
HWND GUICtrlCreateButton(char sText[], int iLeft, int iTop, int iWidth, int iHeight, DWORD dwStyle = -1, DWORD dwExStyle = -1) {
	using namespace CU3WINGUI;
	if (dwStyle == -1) dwStyle = CU3_DEFAULT_BUTTON_STYLE;
	if (dwExStyle == -1) dwExStyle = CU3_DEFAULT_BUTTON_EXSTYLE;
	return CreateWindowEx(dwExStyle, "BUTTON", sText, dwStyle, iLeft, iTop, iWidth, iHeight, hwndLastCreatedGUI, NULL,
		(HINSTANCE)(LONG)GetWindowLong(hwndLastCreatedGUI, GWLP_HINSTANCE), NULL);
}
int GUISetBkColor(COLORREF colorrefBackground, HWND hwndWinhandle = NULL) {

	if (!hwndWinhandle) hwndWinhandle = CU3WINGUI::hwndLastCreatedGUI;


	if (!SetClassLongPtr(hwndWinhandle, GCLP_HBRBACKGROUND,
		(LONG)CreateSolidBrush(RGB(GetBValue(colorrefBackground),
			GetGValue(colorrefBackground),
			GetRValue(colorrefBackground)))))
		return -1; //												ERROR -1

	if (!RedrawWindow(hwndWinhandle, NULL, NULL, WM_ERASEBKGND | RDW_INVALIDATE))
		return -2; //												ERROR -2

	return 1; //													NO ERROR 1
}


HWND GUICtrlCreateLabel(char sText[], int iLeft = -1, int iTop = -1, int iWidth = -1, int iHeight = -1, DWORD dwStyle = -1, DWORD dwExStyle = NULL) {
	using namespace CU3WINGUI;
	if (dwStyle == -1) dwStyle = NULL;
	if (dwExStyle == -1) dwExStyle = WS_EX_TRANSPARENT;
	HWND hwndLabel = CreateWindowEx(dwExStyle, "STATIC", "", WS_CHILD | WS_VISIBLE | SS_NOTIFY | dwStyle, iLeft, iTop, iWidth, iHeight, hwndLastCreatedGUI, (HMENU)1, (HINSTANCE)GetWindowLong(hwndLastCreatedGUI, GWLP_HINSTANCE), NULL);
	SendMessage(hwndLabel, WM_SETTEXT, NULL, (LPARAM)sText);

	SetLayeredWindowAttributes(hwndLabel, (COLORREF)0, (BYTE)255, (DWORD)0x02);








	return hwndLabel;
}

/*
HFONT hfFont = CreateFont(20, 0, 0, 0, fontWeight, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
DEFAULT_PITCH, "Verdana");
SendMessage(hwndLabel, WM_SETFONT, (WPARAM)hfFont, NULL);

*/

/*							C++ DEBUG FUNCTIONS								*/
void GUIWait(unsigned int iMsTime = 0) {
	MSG msg;
	if (!iMsTime) {
		while (1) {
			Sleep(1);
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == WM_QUIT) return;
			DispatchMessage(&msg);
		}
	}
	else
	{
		clock_t iStartTime = clock();
		do
		{
			Sleep(1);
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == WM_QUIT) return;
			DispatchMessage(&msg);
		} while (clock() - iStartTime <= iMsTime);
	}
}


CU3_NAMESPACE_END

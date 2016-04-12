/*
The MIT License (MIT)

Copyright (c) <2016> <gileli121@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/




#include <windows.h> // You also mut to include the windows.h before core.h
//#include <WinUser.h>

#include "CU3_Library\core.h" // You must to always include this core.h file once before including any file in CU3_Library



#include "CU3_Library\EasyCoding\easy_macros.h" // for pp , npp , ee , ww , ww2 , main_wingui
#include "CU3_Library\EasyCoding\init_console.h" // neded to use the standard console in Win32 project



//#include "CU3_Library\gui_64.h"
#include "CU3_Library\gui.h"

#include "CU3_Library\ColorConstants.h"




//Enter into the namespace of the CU3 Library
using namespace CU3_Library;


HWND hwnd;
HWND hwndButton;
#define WaitTime 1250
int main(){


	InitConsole(); // Create the standard console
	


	// Must call it before using any functions
	GUISetDefaultWindowClass("gui_root_name"); // Initialize the subsystem gui with the root name.
	 
	pp "Creating GUI" ee
	hwnd = GUICreate("My test GUI",600,600,-1,-1); // Create simple GUI
	
	
	pp "Creating button" ee
	hwndButton = GUICtrlCreateButton("Some button", 100, 100, 100, 100); // Create button

	
	GUISetBkColor(CU3_COLOR_BLUE); // Set BkColor to blue
	GUICtrlCreateLabel("abcdefg", 10, 10, 60, 60);

	pp "Show GUI" ee
	GUISetState(CU3_SW_SHOW); // Show the GUI
	
	
	GUIWait(WaitTime);


	pp "Hide GUI" ee
	GUISetState(CU3_SW_HIDE); // Hide the GUI

	GUIWait(WaitTime); 
	
	pp "Show GUI" ee
	GUISetState(CU3_SW_SHOW); // Show the GUI

	GUIWait(WaitTime);

	pp "Disable GUI" ee
	GUISetState(CU3_SW_DISABLE); // Disable GUI

	GUIWait(WaitTime);

	pp "Enable GUI" ee
	GUISetState(CU3_SW_ENABLE); // Enable GUI

	pp "Set BkColor to blue" ee
	GUISetBkColor(CU3_COLOR_BLUE); // Set BkColor to blue

	GUIWait(WaitTime);

	pp "Set BkColor to green" ee
	GUISetBkColor(CU3_COLOR_GREEN); // Set BkColor to green
	
	GUIWait(WaitTime);
	
	pp "Set BkColor to yellow" ee
	GUISetBkColor(CU3_COLOR_YELLOW); // Set BkColor to yellow


	GUIWait(); // Wait until user exit


	return 0;
}




// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

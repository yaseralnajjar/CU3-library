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

#include "CU3_Library\core.h" // You must to always include this core.h file once before including any file in CU3_Library



#include "CU3_Library\EasyCoding\easy_macros.h" // for pp , npp , ee , ww , ww2 , main_wingui
#include "CU3_Library\EasyCoding\init_console.h" // neded to use the standard console in Win32 project



#include "CU3_Library\gui.h"



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);






using namespace CU3_Library; //Enter into the namespace of the CU3 Library


HWND g_hwndGUI;
CU3_CTRL g_cu3ctrlListView,
		 g_cu3ctrButton;



int main(){
	using namespace std;
	
	

	// Initialize the subsystem gui with the root name.
	GUISetDefaultWindowClass_C(WndProc,"cu3_gui_test"); 
	

	// Create simple GUI
	g_hwndGUI = GUICreate("My test GUI",600,460);
	
	
	// Create ListView
	g_cu3ctrlListView = GUICtrlCreateListView("colum 1|Colum _____ 2|Co3|Colum     4   ", 10, 10,400,400);


	// Add Items to the listview
	GUICtrlCreateListViewItem("A|B|C|D", &g_cu3ctrlListView);
	GUICtrlCreateListViewItem("E|F|G|H", &g_cu3ctrlListView);
	GUICtrlCreateListViewItem("I|J|K|L", &g_cu3ctrlListView);
	GUICtrlCreateListViewItem("|N|O|P", &g_cu3ctrlListView);
	GUICtrlCreateListViewItem("Q||S|T", &g_cu3ctrlListView);
	GUICtrlCreateListViewItem("U|V||X", &g_cu3ctrlListView);
	GUICtrlCreateListViewItem("Y|Z", &g_cu3ctrlListView);

	g_cu3ctrButton = GUICtrlCreateButton("Add Item", 420, 10, 155, 90);

	

	// Show the GUI
	GUISetState();


	MSG msg;
	while (1) {
		
		Sleep(1);
		if (CU3_GUIGetMsg_C(&msg)){ // Get the msg (update it)
			
			

			CU3_GUIProcessMsg_C(&msg); // Send the msg to WndProc and process there
		}
		
		
	}
	return 0;
}





LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	

	switch (msg)
	{
	case WM_COMMAND:



		if (CU3_GetClickedCtrlID(wParam) == g_cu3ctrButton.intID1) {
			GUICtrlCreateListViewItem("NEW1|NEW2|NEW3|NEW4", &g_cu3ctrlListView);

			return DefWindowProc(hwnd, msg, wParam, lParam);
		}

		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_NOTIFY:
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
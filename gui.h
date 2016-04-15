#pragma once
#include <chrono>
#include <commctrl.h>
#pragma comment(lib,"comctl32.lib")
#include <sstream>      // std::stringstream
#include <vector>
#include <thread>

/* To remove the modern style (so it will look like windows 98), write the line:
	#undef CU3_MODERN_GUI_STYLE
	Before #include <gui.h>



*/

#define CU3_MODERN_GUI_STYLE

#if defined CU3_MODERN_GUI_STYLE
	#if defined _M_IX86
	#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#elif defined _M_IA64
	#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#elif defined _M_X64
	#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#else
	#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#endif
#endif






#include "gui.constants.h"





/*--------------------------------------------------------------*/




CU3_NAMESPACE_START


// Forward declarations
bool internal_use__InitCommonControl(DWORD dwICC);
void internal_use__String2StringArray(std::string* ptr_stringStr, std::vector<std::string>* ptr_vec_stringColumns);



class CU3_CTRL
{
public:
	HWND hwnd = NULL;
	int intID1 = 0,
		intID2 = 0;
};



namespace nameCU3WINGUI 
{
	WNDCLASSEX wcWinClassDefault;
	WNDCLASSEX* ptr_wcWinClass = &wcWinClassDefault;
	HWND hwndActiveGUI = NULL;
	HINSTANCE hinstanceActiveGUI = NULL;
	int iLastCtrlID = 0;
	CU3_CTRL cu3ctrlActive;


	INITCOMMONCONTROLSEX initcommoncontrolsex;
	bool initcommoncontrolsex_istinit = false;

	namespace nameCTRL
	{
		namespace nameLISTVIEW {int iLastWidth = CU3_LISTVIEW_AUTOIT_DEFAULT_SIZE, iLastHeight = CU3_LISTVIEW_AUTOIT_DEFAULT_SIZE;}

	}

	MSG msgCU3;
	std::thread threadMsgPoster;
}






/*							FOR_INITIALIZATION (required only in C++)						*/
int GUISetDefaultWindowClass_C(WNDPROC parm_WndProc, char parm_charRootName[] = "CU3L_GUI", HINSTANCE parm_hInstance = NULL) {
	using namespace nameCU3WINGUI;
	
	if (!parm_hInstance) {
		parm_hInstance = GetModuleHandle(NULL);
		if (!parm_hInstance) return -1; //							ERROR -1
	}


	wcWinClassDefault.cbSize = sizeof(WNDCLASSEX);
	wcWinClassDefault.style = 0;
	wcWinClassDefault.lpfnWndProc = parm_WndProc;
	wcWinClassDefault.cbClsExtra = 0;
	wcWinClassDefault.cbWndExtra = 0;
	wcWinClassDefault.hInstance = parm_hInstance;
	wcWinClassDefault.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcWinClassDefault.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcWinClassDefault.hbrBackground = (HBRUSH)(COLOR_BTNSHADOW);
	wcWinClassDefault.lpszMenuName = NULL;
	wcWinClassDefault.lpszClassName = parm_charRootName;
	wcWinClassDefault.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wcWinClassDefault)) return -2; //					ERROR -2


	return 1; //													NO ERROR 1
}
/*
	Use GUISelectWindowClass_C(&CU3WINGUI::wcRootwinDefault) with bRegisterClass = false to re-select the default class.
	If you select the default class, you first must to call to GUISetDefaultWindowClass *only once*.
	Then at any time you want to reselect the class, just call to this function in this way.
	Before this you must call once to GUISetDefaultWindowClass (If you need to use the default class)

	About non-default To select new Class, At first time that you use the class and if the class was not registered with
	RegisterClassEx, you must to call to this function with bRegisterClass = true *only once*
	(you register the class only once with bRegisterClass = true, then you may use this function to select the class
	again (If you are working with more then one class))

	The function returns the old class on success. On fail it return >0.
*/
WNDCLASSEX* GUISelectWindowClass_C(WNDCLASSEX* ptr_wndclassexNew,bool bRegisterClass = false) {
	if (bRegisterClass && !RegisterClassEx(ptr_wndclassexNew)) return NULL; //				ERROR -1
	WNDCLASSEX* ptr_wndclassexOld = nameCU3WINGUI::ptr_wcWinClass;
	nameCU3WINGUI::ptr_wcWinClass = ptr_wndclassexNew;
	return ptr_wndclassexOld;
}



/*######################################  C OPTIMIZED	 ( <autoit function name>_C )	################################ */	
// Degbug ...
void GUIWait_C(unsigned int iMsTime = 0) {
	MSG msg;
	if (!iMsTime) {
		while (1) {
			GetMessage(&msg, NULL, 0, 0);
			TranslateMessage(&msg); DispatchMessage(&msg);
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

//	GUI*...
#define CU3_GUIGetMsg_C(pMsg) PeekMessage(pMsg, NULL, 0, 0, PM_REMOVE)
#define CU3_GUIProcessMsg_C(pMsg) DispatchMessage(pMsg)

#define CU3_GetClickedCtrlID(wParam) LOWORD(wParam)

//	GUICtrl*...
//		GUICtrl -> ListView
CU3_CTRL GUICtrlCreateListView_C(std::string astringColumns[], int iColumns,int iLeft = 0, int iTop = 0, int iWidth = CU3_DEFAULT,
	int iHeight = CU3_DEFAULT,DWORD dwStyle = CU3_DEFAULT, DWORD dwExStyle = CU3_DEFAULT) {

	using namespace nameCU3WINGUI; using namespace std;


// init defults


	if (dwStyle == CU3_DEFAULT) dwStyle = CU3_LISTVIEW_AUTOIT_DEFAULT_STYLE;
	if (dwExStyle == CU3_DEFAULT) dwExStyle = CU3_LISTVIEW_AUTOIT_DEFAULT_EXSTYLE;
	
	if (iWidth == CU3_DEFAULT) 
	{
		iWidth = nameCTRL::nameLISTVIEW::iLastWidth;
	}
	else
	{
		nameCTRL::nameLISTVIEW::iLastWidth = iWidth;
	}


	if (iHeight == CU3_DEFAULT)
	{
		iHeight = nameCTRL::nameLISTVIEW::iLastHeight;
	}
	else
	{
		nameCTRL::nameLISTVIEW::iLastHeight = iHeight;
	}
	


// Create the ListView
	internal_use__InitCommonControl(ICC_LISTVIEW_CLASSES);
	CU3_CTRL cu3ctrlListview; iLastCtrlID++; 
	if (!
		(cu3ctrlListview.hwnd = CreateWindowEx(dwExStyle, WC_LISTVIEW, "",
			WS_VISIBLE | WS_CHILD | LVS_REPORT | dwStyle
			, iLeft, iTop, iWidth, iHeight, hwndActiveGUI, (HMENU)iLastCtrlID,
			hinstanceActiveGUI,
			NULL))
		) return cu3ctrlListview;
	cu3ctrlListview.intID1 = iLastCtrlID;


// Create the columns
	LVCOLUMN lvcolumn; ZeroMemory(&lvcolumn, sizeof(lvcolumn));
	lvcolumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvcolumn.fmt = LVCFMT_LEFT;
	
	ListView_SetExtendedListViewStyle(cu3ctrlListview.hwnd, dwExStyle);

	SIZE sizeString; HDC hdcGUI = GetDC(hwndActiveGUI);

	for (int a = 0; a < iColumns; a++)
	{
		lvcolumn.iSubItem = a;
		lvcolumn.pszText = &(astringColumns[a])[0];
		GetTextExtentPoint32(hdcGUI, lvcolumn.pszText, astringColumns[a].length() + 1, &sizeString);
		lvcolumn.cx = sizeString.cx;
		ListView_InsertColumn(cu3ctrlListview.hwnd, a, &lvcolumn);
	}

	ReleaseDC(hwndActiveGUI, hdcGUI);

	cu3ctrlActive = cu3ctrlListview;
	return cu3ctrlListview;
}

CU3_CTRL GUICtrlCreateListViewItem_C(std::string astringColumns[], int iColumns,
	CU3_CTRL* cu3ctrlListView = &nameCU3WINGUI::cu3ctrlActive) {
	
	CU3_CTRL cu3ctrlItem;

	LV_ITEM lv_item;
	lv_item.mask = LVIF_TEXT | LVIF_STATE;
	lv_item.state = 0;
	lv_item.stateMask = 0; 
	lv_item.iItem = ListView_GetItemCount(cu3ctrlListView->hwnd);
	lv_item.iSubItem = 0;

	lv_item.pszText = &(astringColumns[0])[0];
	
	if (ListView_InsertItem(cu3ctrlListView->hwnd, &lv_item) == -1) return cu3ctrlItem;

	cu3ctrlItem.hwnd = cu3ctrlListView->hwnd;
	cu3ctrlItem.intID1 = cu3ctrlListView->intID1;
	cu3ctrlItem.intID2 = lv_item.iItem;

	for (int iColum = 1; iColum < iColumns; iColum++)
	{
		ListView_SetItemText(cu3ctrlListView->hwnd,
			lv_item.iItem,
			iColum,
			&(astringColumns[iColum])[0]);
	}

	return cu3ctrlItem;
}




/*######################################  AUTOIT ( <autoit function name>)	###################################### */
//	GUI*...
HWND GUICreate(char sTitle[], int iWidth = -1, int iHeight = -1, int iLeft = -1, int iTop = -1, DWORD dwStyle = -1, DWORD dwExStyle = -1, HWND hwndParent = NULL) {
	using namespace nameCU3WINGUI;
	if (iWidth == -1) iWidth = 400; if (iHeight == -1) iHeight = 400;


	if (iLeft == -1 || iTop == -1) {
		RECT rectScreen;
		GetWindowRect(GetDesktopWindow(), &rectScreen);
		if (iLeft == -1) iLeft = (rectScreen.right - iWidth) >> 1;
		if (iTop == -1) iTop = (rectScreen.bottom - iHeight) >> 1;
	}


	if (dwStyle == -1) dwStyle = WS_MINIMIZEBOX | WS_CAPTION | WS_POPUP | WS_SYSMENU;//CU3_DEFAULT_GUI_STYLE;

	if (dwExStyle == -1) dwExStyle = NULL;

	HWND hGUI;
	if (!(
		hGUI = CreateWindowEx(dwExStyle, ptr_wcWinClass->lpszClassName, sTitle, dwStyle, iLeft, iTop, iWidth,
			iHeight, hwndParent, NULL, ptr_wcWinClass->hInstance, NULL)
		)) return NULL; //									ERROR NULL
	
	hwndActiveGUI = hGUI;
	hinstanceActiveGUI = (HINSTANCE)GetWindowLong(hwndActiveGUI, GWLP_HINSTANCE);

	return hGUI; //												NO ERROR HWND
}
int GUISetState(int iFlag = SW_SHOW, HWND hwndWinhandle = NULL) {
	using namespace nameCU3WINGUI;
	if (!hwndWinhandle) {
		if (!hwndActiveGUI) return false; //					    ERROR 0
		hwndWinhandle = hwndActiveGUI;
	}
	if (iFlag >= 0) {
		ShowWindow(hwndWinhandle, iFlag);
	}
	else
	{
		switch (iFlag)
		{
		case SW_DISABLE:
			EnableWindow(hwndWinhandle, false); return 1;

		case SW_ENABLE:
			EnableWindow(hwndWinhandle, true); return 1;

			/* wasn't implemented:
			case SW_LOCK:

			return 1;

			case SW_UNLOCK:
			return 1;
			*/

		default:
			return -2; //											ERROR -2
		}
	}

	return 1; //													NO ERROR 1
}
int GUISetBkColor(COLORREF colorrefBackground, HWND hwndWinhandle = NULL) {

	if (!hwndWinhandle) hwndWinhandle = nameCU3WINGUI::hwndActiveGUI;


	if (!SetClassLongPtr(hwndWinhandle, GCLP_HBRBACKGROUND,
		(LONG)CreateSolidBrush(RGB(GetBValue(colorrefBackground),
			GetGValue(colorrefBackground),
			GetRValue(colorrefBackground)))))
		return -1; //												ERROR -1

	if (!RedrawWindow(hwndWinhandle, NULL, NULL, WM_ERASEBKGND | RDW_INVALIDATE))
		return -2; //												ERROR -2

	return 1; //													NO ERROR 1
}



//	GUICtrl*...
CU3_CTRL GUICtrlCreateButton(char sText[], int iLeft, int iTop, int iWidth, int iHeight, DWORD dwStyle = -1, DWORD dwExStyle = -1) {
	using namespace nameCU3WINGUI;
	if (dwStyle == -1) dwStyle = CU3_DEFAULT_BUTTON_STYLE;
	if (dwExStyle == -1) dwExStyle = CU3_DEFAULT_BUTTON_EXSTYLE;
	
	CU3_CTRL cu3ctrlButton; iLastCtrlID++;

	if (! (cu3ctrlButton.hwnd = CreateWindowEx(dwExStyle, "BUTTON", sText, dwStyle, iLeft, iTop, iWidth, iHeight, hwndActiveGUI, (HMENU)iLastCtrlID,
		hinstanceActiveGUI, NULL))) return cu3ctrlButton;
	cu3ctrlButton.intID1 = iLastCtrlID;

	cu3ctrlActive = cu3ctrlButton;
	return cu3ctrlButton;
}
CU3_CTRL GUICtrlCreateLabel(char sText[], int iLeft = -1, int iTop = -1, int iWidth = -1, int iHeight = -1, DWORD dwStyle = -1, DWORD dwExStyle = NULL) {
	using namespace nameCU3WINGUI;
	if (dwStyle == -1) dwStyle = NULL;
	if (dwExStyle == -1) dwExStyle = WS_EX_TRANSPARENT;
	CU3_CTRL cu3ctrlLabel; iLastCtrlID++;
	if (!(
		cu3ctrlLabel.hwnd = CreateWindowEx(dwExStyle, "STATIC", "", WS_CHILD | WS_VISIBLE | SS_NOTIFY |
			dwStyle, iLeft, iTop, iWidth, iHeight, hwndActiveGUI, (HMENU)iLastCtrlID, hinstanceActiveGUI, NULL)
		)) return cu3ctrlLabel;
	cu3ctrlLabel.intID1 = iLastCtrlID;
	SendMessage(cu3ctrlLabel.hwnd, WM_SETTEXT, NULL, (LPARAM)sText);

	SetLayeredWindowAttributes(cu3ctrlLabel.hwnd, (COLORREF)0, (BYTE)255, (DWORD)0x02);

	cu3ctrlActive = cu3ctrlLabel;
	return cu3ctrlLabel;


	/*
	HFONT hfFont = CreateFont(20, 0, 0, 0, fontWeight, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
	DEFAULT_PITCH, "Verdana");
	SendMessage(hwndLabel, WM_SETFONT, (WPARAM)hfFont, NULL);

	*/
}

//		GUICtrl -> ListView
CU3_CTRL GUICtrlCreateListView(std::string stringColumns, int iLeft = 0, int iTop = 0,int iWidth = CU3_DEFAULT,
	int iHeight = CU3_DEFAULT, DWORD dwStyle = -1, DWORD dwExStyle = -1) {
	using namespace std;


	stringstream stringstreamTmp;
	int int_stringColumnsLength0 = stringColumns.length() - 1;


	vector<string> vec_stringColumns;
	
	internal_use__String2StringArray(&stringColumns, &vec_stringColumns);


	if (dwStyle == -1) dwStyle = CU3_LISTVIEW_AUTOIT_DEFAULT_STYLE;
	if (dwExStyle == -1) dwExStyle = CU3_LISTVIEW_AUTOIT_DEFAULT_EXSTYLE;



	return GUICtrlCreateListView_C(&vec_stringColumns[0], vec_stringColumns.size(),
		iLeft, iTop, iWidth, iHeight, dwStyle, dwExStyle);
}



CU3_CTRL GUICtrlCreateListViewItem(std::string stringColumns, CU3_CTRL* cu3ctrlListView) {
	
	std::vector<std::string> vec_stringColumns;

	internal_use__String2StringArray(&stringColumns, &vec_stringColumns);

	return GUICtrlCreateListViewItem_C(&vec_stringColumns[0], vec_stringColumns.size(),cu3ctrlListView);
}





/*##################################################  INTERNAL USE	############################################### */

void internal_use__String2StringArray(std::string* ptr_stringStr, std::vector<std::string>* ptr_vec_stringColumns) {
	using namespace std;
	stringstream stringstreamTmp;

	int int_stringColumnsLength0 = ptr_stringStr->length() - 1;


	


	for (int a = 0; a < ptr_stringStr->length(); a++)
	{
		if (ptr_stringStr->at(a) == '|')
		{
			ptr_vec_stringColumns->push_back(stringstreamTmp.str());
			stringstreamTmp.str("");
			continue;

		}
		else if (a == int_stringColumnsLength0)
		{
			stringstreamTmp << ptr_stringStr->at(a);
			ptr_vec_stringColumns->push_back(stringstreamTmp.str());
			stringstreamTmp.str("");
			continue;
		}
		stringstreamTmp << ptr_stringStr->at(a);
	}


	return;
}

bool internal_use__InitCommonControl(DWORD dwICC) {
	using namespace nameCU3WINGUI;
	if (!initcommoncontrolsex_istinit)
	{
		initcommoncontrolsex.dwSize = sizeof(initcommoncontrolsex);
		initcommoncontrolsex_istinit = 1;
	}
	if (initcommoncontrolsex.dwICC & dwICC) return true;

	initcommoncontrolsex.dwICC = initcommoncontrolsex.dwICC | dwICC;
	return InitCommonControlsEx(&initcommoncontrolsex);

	return true;
}

















































/*

	typedef struct _LV_ITEM {
		UINT   mask;        // attributes of this data structure
		int    iItem;       // index of the item to which this structure refers
		int    iSubItem;    // index of the subitem to which this structure refers
		UINT   state;       // Specifies the current state of the item
		UINT   stateMask;   // Specifies the bits of the state member that are valid. 
		LPTSTR  pszText;    // Pointer to a null-terminated string
							// that contains the item text 
		int    cchTextMax;  // Size of the buffer pointed to by the pszText member
		int    iImage;      // index of the list view item's icon 
		LPARAM lParam;      // 32-bit value to associate with item 
	} LV_ITEM;

	typedef struct _LV_COLUMN {
		UINT mask;       // which members of this structure contain valid information
		int fmt;         // alignment of the column heading and the subitem text 
		int cx;          // Specifies the width, in pixels, of the column.
		LPTSTR pszText;  // Pointer to a null-terminated string
						 // that contains the column heading 
		int cchTextMax;  // Specifies the size, in characters, of the buffer
		int iSubItem;    // index of subitem
	} LV_COLUMN;
	



	LVITEM lvitemListview;
	ZeroMemory(&lvitemListview, sizeof(lvitemListview));
	
	lvitemListview.mask = LVIF_TEXT;
	lvitemListview.cColumns = 20;


	ListView_InsertItem(hwndListview, &lvitemListview);


	char cText[] = "aaaa";
	ListView_SetItemText(hwndListview,0,1, cText);
*/
/*							C++ DEBUG FUNCTIONS								*/



CU3_NAMESPACE_END

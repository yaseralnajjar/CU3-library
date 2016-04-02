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


// For Main function (WinMain)
#define main_wingui WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)



// Easy print macros:
#define pp std::cout <<
#define npp << std::endl <<
#define ee << std::endl;




#define ww while(1){Sleep(100);} return 0;



#define ww2 \
MSG tmp_msg; \
while (1){ \
	Sleep(1); \
	if (PeekMessage(&tmp_msg, NULL, 0, 0, PM_REMOVE)) \
	{ \
		switch (tmp_msg.message) \
		{ \
		case WM_QUIT: \
			return 0; \
		default: \
			break; \
		} \
	} \
	TranslateMessage(&tmp_msg); DispatchMessage(&tmp_msg); \
} \
return tmp_msg.wParam; \



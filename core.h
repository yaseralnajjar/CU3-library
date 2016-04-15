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


/*
	Long name space: "CU3_Library"
	Short name space: "CU3"

	Use whatever you want.

	why short name space?
		In case that you dont want to use the line:
		using namespace CU3_Library;

		You have to use CU3_Library::<Function / Variable>
		In this case you can use CU3::<Function / Variable>
		instead and it will be the same.


	This desain allows you to easly change from here the namespace string to
	something else if you need.
*/




#define CU3_NAMESPACE CU3_Library
#define CU3 CU3_NAMESPACE

#define CU3_NAMESPACE_START namespace CU3_NAMESPACE {
#define CU3_NAMESPACE_END }




#define CU3_DEFAULT -1






